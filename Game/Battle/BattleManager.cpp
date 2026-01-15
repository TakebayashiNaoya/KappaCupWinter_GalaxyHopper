/**
 * BattleManager.cpp
 * バトルマネージャークラスの実装
 */
#include "stdafx.h"
#include "BattleManager.h"
#include "Source/Actor/ActorStatus.h"
#include "Source/Actor/Character/Enemy/BasicEnemy/BasicEnemy.h"
#include "Source/Actor/Character/Enemy/BossEnemy/BossEnemy.h"
#include "Source/Actor/Character/Enemy/DeformEnemy/DeformEnemy.h"
#include "Source/Actor/Character/Enemy/EnemyController.h"
#include "Source/Actor/Character/Player/Player.h"
#include "Source/Actor/Object/Rocket.h"
#include "Source/Actor/Object/Treasure.h"
#include "Source/Scene/SceneManager.h"
#include "UI/UIBossStage.h"
#include "UI/UIFirstStage.h"
#include "Ui/UIInGameBase.h"


namespace app
{
	namespace battle
	{
		namespace
		{
			/** 死亡しているエネミーをDeleteGOし、リストからも削除するテンプレート関数 */
			template <class T>
			void UpdateAndRemoveDeadEnemies(std::vector<T*>& enemies)
			{
				auto it = enemies.begin();
				while (it != enemies.end())
				{
					auto* enemy = *it;
					/** 死亡しているエネミーをDeleteGOし、リストからも削除 */
					if (enemy && enemy->ShouldDestroy()) {
						DeleteGO(enemy);
						it = enemies.erase(it);
					}
					else {
						++it;
					}
				}
			}
		}


		BattleManager* BattleManager::m_instance = nullptr;
		bool BattleManager::m_isGoalReached = false;
		bool BattleManager::m_isResultSequence = false;
		BattleManager::EnBattleResult BattleManager::m_battleResult = EnBattleResult::Fighting;


		bool BattleManager::Enter()
		{
			return false;
		}


		void BattleManager::Update()
		{
			/** シーン切り替えリクエストがある場合、バトル処理を全てスキップ */
			if (scene::SceneManager::GetInstance()->GetIsSceneChangeRequested()) {
				return;
			}

			/** エネミーの更新と削除 */
			UpdateEnemies();
			/** ギアの最大取得数を更新 */
			int maxGearCount = static_cast<int>(m_treasures.size());
			/** 宝箱やロケットなどのギミック処理 */
			UpdateInteractions();
			/** 各種UIの表示更新 */
			UpdateUI();
			/** 勝敗判定やリザルト移行判定 */
			UpdateBattleState();
		}


		void BattleManager::CleanUp()
		{
			/** 雑魚エネミーの削除 */
			DestroyManagedEnemies();
			/** シーンが削除する物のポインタクリア */
			ResetReferences();
			/** ギア取得数リセット */
			m_gotGearCount = 0;
			m_maxGearCount = 0;
			/** 戦闘結果リセット */
			m_battleResult = EnBattleResult::Fighting;
			/** ゴールフラグリセット */
			m_isGoalReached = false;
			/** リザルトシーケンスフラグリセット */
			m_isResultSequence = false;
		}


		void BattleManager::DestroyManagedEnemies()
		{
			/** 基本エネミーの削除 */
			for (auto* enemy : m_basicEnemies) {
				if (enemy) {
					DeleteGO(enemy);
				}
			}
			m_basicEnemies.clear();
			/** 変形エネミーの削除 */
			for (auto* enemy : m_deformEnemies) {
				if (enemy) {
					DeleteGO(enemy);
				}
			}
			m_deformEnemies.clear();
		}


		void BattleManager::ResetReferences()
		{
			m_player = nullptr;
			m_bossEnemy = nullptr;
			m_rocket = nullptr;
			m_treasures.clear();
			m_uiBossHp = nullptr;
			m_uiDamageFlash = nullptr;
			m_uiPlayerHp = nullptr;
			m_uiGear = nullptr;
		}


		void BattleManager::UpdateEnemies()
		{
			/** 死亡しているエネミーをDeleteGOし、リストから削除 */
			UpdateAndRemoveDeadEnemies(m_basicEnemies);
			UpdateAndRemoveDeadEnemies(m_deformEnemies);

			/** エネミーコントローラーのターゲットにプレイヤーを設定 */
			for (auto* controller : m_enemyControllers) {
				if (controller && m_player) {
					controller->SetTarget(m_player);
				}
			}
		}


		void BattleManager::UpdateInteractions()
		{
			/** プレイヤーが宝箱に近づいたら、宝箱を開ける */
			if (m_player)
			{
				for (auto* treasure : m_treasures)
				{
					if (treasure == nullptr) {
						continue;
					}
					else if (treasure->GetIsOpened()) {
						continue;
					}

					Vector3 lengthVec = treasure->GetTransform().m_position - m_player->GetTransform().m_position;
					float range = treasure->GetStatus<actor::TreasureStatus>()->GetInteractRange();
					if (lengthVec.Length() < range) {
						treasure->SetIsOpened(true);
						m_gotGearCount++;
					}
				}
			}

			/** ギアを全て集めたらロケットがゴールとして機能するようにする */
			if (m_maxGearCount > 0 && m_gotGearCount == m_maxGearCount)
			{
				/** プレイヤーがロケットに近づいたらゴールフラグを立てる */
				if (m_rocket && m_player)
				{
					Vector3 lengthVec = m_rocket->GetTransform().m_position - m_player->GetTransform().m_position;
					float range = m_rocket->GetStatus<actor::RocketStatus>()->GetInteractRange();
					if (lengthVec.Length() < range)
					{
						if (m_rocket != nullptr) {
							m_isGoalReached = true;
							m_gotGearCount = 0;
						}
					}
				}
			}
			else
			{
				m_isGoalReached = false;
			}
		}


		void BattleManager::UpdateUI()
		{
			/** プレイヤーのHPUIにプレイヤーのHPを渡す */
			if (m_uiPlayerHp && m_player) {
				m_uiPlayerHp->SetPlayerHp(m_player->GetStatus<actor::PlayerStatus>()->GetHp());
			}

			/** ダメージフラッシュUIにプレイヤーのHPを渡す */
			if (m_uiDamageFlash && m_player) {
				m_uiDamageFlash->SetPlayerHp(m_player->GetStatus<actor::PlayerStatus>()->GetHp());
			}

			/** ボスのHPUIにボスのHPを渡す */
			if (m_uiBossHp && m_bossEnemy) {
				int currentHp = m_bossEnemy->GetStatus<actor::BossEnemyStatus>()->GetHp();
				int maxHp = m_bossEnemy->GetStatus<actor::BossEnemyStatus>()->GetMaxHp();
				m_uiBossHp->UpdateHp(currentHp, maxHp);
			}

			/** ギアの取得数をUIに反映 */
			if (m_uiGear) {
				m_uiGear->SetCount(m_gotGearCount, m_maxGearCount);
			}
		}


		void BattleManager::UpdateBattleState()
		{
			/** 戦闘終了判定 */
			if (m_player && m_player->GetStatus<actor::PlayerStatus>()->GetHp() <= 0) {
				m_battleResult = EnBattleResult::Lose;
			}
			else if (m_bossEnemy && m_bossEnemy->GetStatus<actor::BossEnemyStatus>()->GetHp() <= 0) {
				m_battleResult = EnBattleResult::Win;
			}

			/** 戦闘終了後、敗者の死亡アニメーションが終わったらUIを非表示にする合図を出す */
			if (m_battleResult == EnBattleResult::Lose) {
				if (m_player && m_player->GetModelRender()->IsPlayingAnimation() == false) {
					m_isResultSequence = true;
				}
			}
			else if (m_battleResult == EnBattleResult::Win) {
				if (m_bossEnemy && m_bossEnemy->GetModelRender()->IsPlayingAnimation() == false) {
					m_isResultSequence = true;
				}
			}
		}




		/********************************/


		BattleManagerObject::BattleManagerObject()
		{
			m_battleManager = BattleManager::Create();
		}


		BattleManagerObject::~BattleManagerObject()
		{
			BattleManager::Delete();
			m_battleManager = nullptr;
		}


		bool BattleManagerObject::Start()
		{
			m_battleManager->Enter();
			return true;
		}


		void BattleManagerObject::Update()
		{
			m_battleManager->Update();
		}
	}
}