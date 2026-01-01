/**
 * BattleManager.cpp
 * バトルマネージャークラスの実装
 */
#include "stdafx.h"
#include "BattleManager.h"
#include "Source/Scene/SceneManager.h"
#include "Source/Actor/Character/Player/Player.h"
#include "Source/Actor/Character/Enemy/BasicEnemy/BasicEnemy.h"
#include "Source/Actor/Character/Enemy/DeformEnemy/DeformEnemy.h"
#include "Source/Actor/Character/Enemy/BossEnemy/BossEnemy.h"
#include "Source/Actor/ActorStatus.h"
#include "Ui/UIInGameBase.h"
#include "UI/UIFirstStage.h"
#include "UI/UIBossStage.h"
#include "Source/Actor/Object/Rocket.h"
#include "Source/Actor/Object/Treasure.h"


namespace app
{
	namespace battle
	{
		namespace
		{
			constexpr float ENEMY_SEARCH_RADIUS = 500.0f;	// プレイヤー検出半径
			constexpr float ROCKET_SEARCH_RADIUS = 500.0f;	// ロケットのプレイヤー検出半径
			constexpr float TREASURE_SEARCH_RADIUS = 200.0f;	// 宝箱のプレイヤー検出半径


			/** プレイヤーのアドレスをエネミーに伝えるテンプレート関数 */
			template <class T>
			void SetTargetPlayerToEnemies(actor::Player* player, std::vector<T*>& enemys)
			{
				for (auto* enemy : enemys) {
					if (enemy) {
						enemy->SetTargetPlayer(player);
					}
				}
			}

			/// <summary>
			/// 死亡しているエネミーをDeleteGOし、リストからも削除するテンプレート関数
			/// </summary>
			template <class T>
			void UpdateAndRemoveDeadEnemies(std::vector<T*>& enemies)
			{
				auto it = enemies.begin();
				while (it != enemies.end()) {
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


		void BattleManager::Update()
		{
			/** シーン切り替えリクエストがある場合、バトル処理を全てスキップ */
			if (scene::SceneManager::GetInstance()->GetIsSceneChangeRequested()) {
				return;
			}

			/** 死亡しているエネミーをDeleteGOし、リストから削除 */
			UpdateAndRemoveDeadEnemies(m_basicEnemies);
			UpdateAndRemoveDeadEnemies(m_deformEnemies);

			/** ボスエネミーにプレイヤーのアドレスを伝える */
			if (m_bossEnemy && m_player) {
				m_bossEnemy->SetTargetPlayer(m_player);
			}

			/** 基本エネミーにプレイヤーのアドレスを伝える */
			SetTargetPlayerToEnemies<actor::BasicEnemy>(m_player, m_basicEnemies);

			/** 変形エネミーにプレイヤーのアドレスを伝える */
			SetTargetPlayerToEnemies<actor::DeformEnemy>(m_player, m_deformEnemies);

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
					if (lengthVec.Length() < TREASURE_SEARCH_RADIUS) {
						treasure->SetIsOpened(true);
						m_gotGearCount++;
					}
				}
			}

			/** ギアの取得数をUIに反映 */
			if (m_uiGear) {
				m_uiGear->SetCount(m_gotGearCount, m_maxGearCount);
			}

			/** ギアを全て集めたらロケットがゴールとして機能するようにする */
			if (m_maxGearCount > 0 && m_gotGearCount == m_maxGearCount)
			{
				/** プレイヤーがロケットに近づいたらゴールフラグを立てる */
				if (m_rocket && m_player)
				{
					Vector3 lengthVec = m_rocket->GetTransform().m_position - m_player->GetTransform().m_position;
					if (lengthVec.Length() < ROCKET_SEARCH_RADIUS)
					{
						if (m_rocket != nullptr) {
							m_isGoalReached = true;
							m_maxGearCount = 0;
							m_gotGearCount = 0;
						}
					}
				}
			}
			else
			{
				m_isGoalReached = false;
			}

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


		void BattleManager::DestroyAllEnemies()
		{
			// 基本エネミーの削除
			for (auto* enemy : m_basicEnemies) {
				if (enemy) {
					DeleteGO(enemy);
				}
			}
			m_basicEnemies.clear();

			// 変形エネミーの削除
			for (auto* enemy : m_deformEnemies) {
				if (enemy) {
					DeleteGO(enemy);
				}
			}
			m_deformEnemies.clear();

			// ※ボスなどはステージ個別の管理でよければそのままでもOKですが、
			// ここでまとめて消す設計にしても構いません。
		}


		void BattleManager::Register(actor::Player* player)
		{
			m_player = player;
		}

		void BattleManager::Unregister(actor::Player* player)
		{
			m_player = nullptr;
		}


		void BattleManager::Register(actor::BossEnemy* boss)
		{
			m_bossEnemy = boss;
		}

		void BattleManager::Unregister(actor::BossEnemy* boss)
		{
			m_bossEnemy = nullptr;
		}

		void BattleManager::Register(actor::BasicEnemy* enemy)
		{
			m_basicEnemies.push_back(enemy);
		}

		void BattleManager::Unregister(actor::BasicEnemy* enemy)
		{
			auto it = std::remove(m_basicEnemies.begin(), m_basicEnemies.end(), enemy);
			m_basicEnemies.erase(it, m_basicEnemies.end());
		}


		void BattleManager::Register(actor::DeformEnemy* enemy)
		{
			m_deformEnemies.push_back(enemy);
		}

		void BattleManager::Unregister(actor::DeformEnemy* enemy)
		{
			auto it = std::remove(m_deformEnemies.begin(), m_deformEnemies.end(), enemy);
			m_deformEnemies.erase(it, m_deformEnemies.end());
		}

		void BattleManager::Register(ui::UIGear* uiGear)
		{
			m_uiGear = uiGear;
		}

		void BattleManager::Unregister(ui::UIGear* uiGear)
		{
			m_uiGear = nullptr;
		}


		void BattleManager::Register(ui::UIPlayerHp* uiPlayerLife)
		{
			m_uiPlayerHp = uiPlayerLife;
		}

		void BattleManager::Unregister(ui::UIPlayerHp* uiPlayerLife)
		{
			m_uiPlayerHp = nullptr;
		}


		void BattleManager::Register(ui::UIDamageFlash* uiDamageFlash)
		{
			m_uiDamageFlash = uiDamageFlash;
		}

		void BattleManager::Unregister(ui::UIDamageFlash* uiDamageFlash)
		{
			m_uiDamageFlash = nullptr;
		}


		void BattleManager::Register(ui::UIBossHp* uiBossLife)
		{
			m_uiBossHp = uiBossLife;
		}

		void BattleManager::Unregister(ui::UIBossHp* uiBossLife)
		{
			m_uiBossHp = nullptr;
		}

		void BattleManager::Register(actor::Rocket* rocket)
		{
			m_rocket = rocket;
		}

		void BattleManager::Unregister(actor::Rocket* rocket)
		{
			m_rocket = nullptr;
		}


		void BattleManager::Register(actor::Treasure* treasure)
		{
			m_treasures.push_back(treasure);
			m_maxGearCount++;
		}

		void BattleManager::Unregister(actor::Treasure* treasure)
		{
			auto it = std::remove(m_treasures.begin(), m_treasures.end(), treasure);
			m_treasures.erase(it, m_treasures.end());
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
			return true;
		}


		void BattleManagerObject::Update()
		{
			m_battleManager->Update();
		}
	}
}