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

			/// <summary>
			/// プレイヤーがエネミーに近づいたら、エネミーにプレイヤーの座標を伝え、発見フラグを立てる。
			/// </summary>
			/// <typeparam name="T"> 敵オブジェクトの型（vector）。</typeparam>
			/// <param name="player"> プレイヤーのポインタ。</param>
			/// <param name="enemys"> エネミーのvector型の変数。</param>
			/// <param name="searchRadius">敵を検出するための半径。</param>
			template <class T>
			void CheckEnemyDetection(actor::Player* player, std::vector<T*>& enemys, float searchRadius)
			{
				if (player == nullptr) {
					return;
				}

				for (auto* enemy : enemys) {

					if (enemy == nullptr) {
						continue;
					}

					Vector3 distance = enemy->GetTransform().m_position - player->GetTransform().m_position;
					if (distance.Length() < searchRadius) {
						enemy->SetIsFoundPlayer(true, player->GetTransform().m_position);
					}
					else {
						enemy->SetIsFoundPlayer(false, Vector3::Zero);
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

					// ここで「死んでいますか？」と聞いて、死んでいたらトドメ（DeleteGO）を刺す
					if (enemy && enemy->ShouldDestroy()) {
						DeleteGO(enemy);        // ここで初めてDeleteGOする
						it = enemies.erase(it); // リストからも削除
					}
					else {
						++it;
					}
				}
			}
		}


		BattleManager* BattleManager::m_instance = nullptr;
		bool BattleManager::m_isBattleFinish = false;
		bool BattleManager::m_isStopCollisionManager = false;


		void BattleManager::Update()
		{
			// シーン切り替えリクエストがある場合、バトル処理を全てスキップ。
			if (scene::SceneManager::GetInstance()->GetIsSceneChangeRequested()) {
				return;
			}

			// 死亡しているエネミーをDeleteGOし、リストからも削除。
			UpdateAndRemoveDeadEnemies<actor::BasicEnemy, actor::BasicEnemyStatus>(m_basicEnemies);
			UpdateAndRemoveDeadEnemies<actor::DeformEnemy, actor::DeformEnemyStatus>(m_deformEnemies);

			// ボスエネミーにプレイヤーの座標を伝える。
			if (m_bossEnemy && m_player) {
				m_bossEnemy->SetIsFoundPlayer(true, m_player->GetTransform().m_position);
			}

			// プレイヤーがベーシックエネミーに近づいたら、ベーシックエネミーにプレイヤーの座標を伝える。
			CheckEnemyDetection<actor::BasicEnemy>(m_player, m_basicEnemies, ENEMY_SEARCH_RADIUS);

			// プレイヤーが変形エネミーに近づいたら、変形エネミーにプレイヤーの座標を伝える。
			CheckEnemyDetection<actor::DeformEnemy>(m_player, m_deformEnemies, ENEMY_SEARCH_RADIUS);

			// プレイヤーのライフをUIに反映。
			if (m_uiPlayerLife && m_player) {
				m_uiPlayerLife->SetPlayerHp(m_player->GetStatus<actor::PlayerStatus>()->GetHp());
			}

			// ダメージフラッシュUIにプレイヤーのダメージ状態を反映。
			if (m_uiDamageFlash && m_player) {
				m_uiDamageFlash->SetPlayerHp(m_player->GetStatus<actor::PlayerStatus>()->GetHp());
			}

			// ボスのライフをUIに反映。
			if (m_uiBossLife && m_bossEnemy) {
				uint8_t currentHp = m_bossEnemy->GetStatus<actor::BossEnemyStatus>()->GetHp();
				uint8_t maxHp = m_bossEnemy->GetStatus<actor::BossEnemyStatus>()->GetMaxHp();
				m_uiBossLife->UpdateHp(currentHp, maxHp);
			}

			// プレイヤーが宝箱に近づいたら、宝箱を開ける。
			if (m_player) {
				for (auto* treasure : m_treasures) {
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

			// ギアの取得数をUIに反映。
			if (m_uiGear) {
				m_uiGear->SetCount(m_gotGearCount, m_maxGearCount);
			}

			// ギアを全て集めたらロケットを発射可能にする。
			if (m_maxGearCount > 0 && m_gotGearCount == m_maxGearCount) {
				m_canLaunch = true;
			}
			else {
				m_canLaunch = false;
			}

			// プレイヤーがロケットに近づいたら、ロケットをゴール状態にする。
			if (m_rocket && m_player && m_canLaunch) {
				Vector3 lengthVec = m_rocket->GetTransform().m_position - m_player->GetTransform().m_position;
				if (lengthVec.Length() < ROCKET_SEARCH_RADIUS) {
					if (m_rocket != nullptr) {
						m_rocket->SetIsGooled(true);
						m_maxGearCount = 0;
						m_gotGearCount = 0;
						m_canLaunch = false;
					}
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
			m_uiPlayerLife = uiPlayerLife;
		}

		void BattleManager::Unregister(ui::UIPlayerHp* uiPlayerLife)
		{
			m_uiPlayerLife = nullptr;
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
			m_uiBossLife = uiBossLife;
		}

		void BattleManager::Unregister(ui::UIBossHp* uiBossLife)
		{
			m_uiBossLife = nullptr;
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