/**
 * BattleStageBase.cpp
 * バトルがあるステージの共通処理の実装
 */
#include "stdafx.h"
#include "BattleStageBase.h"
#include "Source/Actor/Character/Player/Player.h"
#include "Source/Actor/Character/Enemy/BossEnemy/BossEnemy.h"
#include "UI/UIGameOver.h"
#include "UI/UIGameClear.h"
#include "Camera/GameCamera.h"
#include "UI/UIFirstStage.h"
#include "Collision/CollisionManager.h"
#include "LoadingScreen.h"


namespace app
{
	namespace scene
	{
		BattleStageBase::BattleStageBase()
		{
			/** バトルマネージャーの戦闘終了フラグをfalseにしておく */
			battle::BattleManager::SetIsWinnerDecided(false);
			/** バトルマネージャーのゴールフラグをfalseにしておく */
			battle::BattleManager::SetIsGoalReached(false);
			/** ロードタスク登録 */
			RegisterLoadingTasks();
		}


		BattleStageBase::~BattleStageBase()
		{
			/** すべてのエネミーを破棄 */
			battle::BattleManager::GetInstance()->DestroyAllEnemies();
			/** プレイヤー登録解除・破棄 */
			battle::BattleManager::GetInstance()->Unregister(m_player);
			DeleteGO(m_player);
			/** 空の破棄 */
			DeleteGO(m_skyCube);
			/** ゲームカメラの破棄 */
			DeleteGO(m_gameCamera);
		}


		bool BattleStageBase::Start()
		{
			return true;
		}


		void BattleStageBase::Update()
		{
			/** RegisterLoadingTasksで登録されたタスクを処理 */
			InitObjects();

			/** 派生先の更新処理を呼び出す */
			OnUpdate();


			/**
			 * 勝敗判定処理
			 */
			switch (m_battlePhase)
			{
				// 1.プレイヤーかボスが死亡したら、勝敗のステートを設定する。
			case enBattlePhase_Battle:
				if (m_player && m_player->GetStatus<actor::PlayerStatus>()->GetHp() <= 0) {
					m_result = enResult_PlayerLose;
					m_battlePhase = enBattlePhase_WaitFinishAnimation;
				}
				else if (m_bossEnemy && m_bossEnemy->GetStatus<actor::BossEnemyStatus>()->GetHp() <= 0) {
					m_result = enResult_PlayerWin;
					m_battlePhase = enBattlePhase_WaitFinishAnimation;
				}
				break;


				// 3.プレイヤーの死亡アニメーションが終わったらゲームオーバーへ、
				//   ボスの死亡アニメーションが終わったらゲームクリアへ。
			case enBattlePhase_WaitFinishAnimation:
				if (m_result == enResult_PlayerLose) {
					if (m_player && m_player->GetModelRender()->IsPlayingAnimation() == false) {
						m_battlePhase = enBattlePhase_GameOver;
					}
				}
				else if (m_result == enResult_PlayerWin) {
					if (m_bossEnemy && m_bossEnemy->GetModelRender()->IsPlayingAnimation() == false) {
						m_battlePhase = enBattlePhase_GameClear;
					}
				}
				break;


				// 4.ゲームオーバー、またはゲームクリアUIを表示する。
			case enBattlePhase_GameOver:
				if (m_uiResult == nullptr) {
					m_uiResult = NewGO<ui::UIGameOver>(0, "UIGameOver");
				}
				m_battlePhase = enBattlePhase_WaitEnd;
				break;
			case enBattlePhase_GameClear:
				if (m_uiResult == nullptr) {
					m_uiResult = NewGO<ui::UIGameClear>(0, "UIGameClear");
				}
				m_battlePhase = enBattlePhase_WaitEnd;
				break;


				// 5.ゲームオーバー、またはゲームクリアUIの終了を待ってタイトルへ戻る。
			case enBattlePhase_WaitEnd:
				if (m_uiResult->GetIsEnd()) {
					// ロード画面へ移行。
					if (LoadingScreen::GetState() != LoadingScreen::enState_Loading) {
						LoadingScreen::ChangeState(LoadingScreen::enState_Loading);
					}

					if (LoadingScreen::GetState() == LoadingScreen::enState_Loading) {
						// 黒画像が残ってしまっているので破棄する。
						if (m_uiResult) {
							DeleteGO(m_uiResult);
							m_uiResult = nullptr;
						}
						m_battlePhase = enBattlePhase_End;
					}
				}
				break;

			case enBattlePhase_End:
				SceneManager::GetInstance()->ChangeScene(SceneID::Title);
				break;
			}
		}


		void BattleStageBase::InitObjects()
		{
			if (m_currentTaskIndex < m_loadingTasks.size()) {
				m_loadingTasks[m_currentTaskIndex]();
				m_currentTaskIndex++;
			}
		}


		void BattleStageBase::RegisterLoadingTasks()
		{
			m_loadingTasks.push_back([this]() {
				InitSky();
				});

			m_loadingTasks.push_back([this]() {
				InitLevel();
				});

			m_loadingTasks.push_back([this]() {
				m_gameCamera = NewGO<camera::GameCamera>(0, "GameCamera");
				});

			m_loadingTasks.push_back([this]() {
				LoadingScreen::FinishLoading();
				});
		}


		void BattleStageBase::InitSky()
		{
			// 現在の空を破棄。
			DeleteGO(m_skyCube);

			m_skyCube = NewGO<SkyCube>(0, "skycube");
			m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);

			// 環境光の計算のためのIBLテクスチャをセットする。
			g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);
		}
	}
}