#pragma once


namespace app
{
	namespace actor
	{
		class Player;
		class BossEnemy;
		class BasicEnemy;
		class DeformEnemy;
		class Rocket;
		class Treasure;
	}
	namespace ui
	{
		class UIPlayerHp;
		class UIDamageFlash;
		class UIBossHp;
		class UIGear;
	}


	namespace battle
	{
		// 当たり判定を管理するクラス
		// 当たったという処理をまとめたい
		class BattleManager
		{
		private:
			BattleManager() {};
			~BattleManager() {};


		public:
			void Update();




		private:
			static BattleManager* m_instance;


		public:
			static BattleManager* Create()
			{
				if (m_instance == nullptr) {
					m_instance = new BattleManager();
				}
				return m_instance;
			}
			static void Delete()
			{
				if (m_instance != nullptr) {
					delete m_instance;
					m_instance = nullptr;
				}
			}
			static BattleManager* GetInstance()
			{
				return m_instance;
			}


			/// <summary>
			/// フラグの取得・設定
			/// </summary>
		public:
			static bool GetIsBattleFinish()
			{
				return m_isBattleFinish;
			}
			static void SetIsBattleFinish(bool isFinish)
			{
				m_isBattleFinish = isFinish;
			}
			static bool GetIsStopCollisionManager()
			{
				return m_isStopCollisionManager;
			}
			static void SetIsStopCollisionManager(bool isStop)
			{
				m_isStopCollisionManager = isStop;
			}


			/// <summary>
			/// 登録・解除関数群
			/// </summary>
		public:
			// エネミー全削除用
			void DestroyAllEnemies();

			// プレイヤー用
			void Register(actor::Player* player);
			void Unregister(actor::Player* player);

			// ボス用
			void Register(actor::BossEnemy* boss);
			void Unregister(actor::BossEnemy* boss);

			// 基本エネミー用
			void Register(actor::BasicEnemy* enemy);
			void Unregister(actor::BasicEnemy* enemy);

			// 変形エネミー用
			void Register(actor::DeformEnemy* enemy);
			void Unregister(actor::DeformEnemy* enemy);

			// ギアUI用
			void Register(ui::UIGear* uiGear);
			void Unregister(ui::UIGear* uiGear);

			// プレイヤーライフUI用
			void Register(ui::UIPlayerHp* uiPlayerLife);
			void Unregister(ui::UIPlayerHp* uiPlayerLife);

			// ダメージフラッシュUI用
			void Register(ui::UIDamageFlash* uiDamageFlash);
			void Unregister(ui::UIDamageFlash* uiDamageFlash);

			// ボスライフUI用
			void Register(ui::UIBossHp* uiBossLife);
			void Unregister(ui::UIBossHp* uiBossLife);

			// ロケット用
			void Register(actor::Rocket* rocket);
			void Unregister(actor::Rocket* rocket);

			// 宝箱用
			void Register(actor::Treasure* treasure);
			void Unregister(actor::Treasure* treasure);

			// その他汎用
			template<typename T>
			void Register(T* object)
			{
				K2_ASSERT(false, "しょりついかわすれ");
			}
			template<typename T>
			void Unregister(T* object)
			{
				K2_ASSERT(false, "しょりついかわすれ");
			}


		private:
			static bool m_isBattleFinish;
			static bool m_isStopCollisionManager;

			actor::Player* m_player = nullptr;
			actor::BossEnemy* m_bossEnemy = nullptr;
			std::vector<actor::BasicEnemy*> m_basicEnemies;
			std::vector<actor::DeformEnemy*> m_deformEnemies;

			ui::UIGear* m_uiGear = nullptr;
			ui::UIPlayerHp* m_uiPlayerLife = nullptr;
			ui::UIDamageFlash* m_uiDamageFlash = nullptr;
			ui::UIBossHp* m_uiBossLife = nullptr;
			int m_gotGearCount = 0;
			int m_maxGearCount = 0;
			bool m_canLaunch = false;

			actor::Rocket* m_rocket = nullptr;
			std::vector<actor::Treasure*> m_treasures;

			std::vector<IGameObject*> m_objects;
		};



		/// <summary>
		/// 当たり判定管理クラスを更新したりするためのゲームオブジェクト。
		/// </summary>
		class BattleManagerObject : public IGameObject
		{
		public:
			BattleManagerObject();
			~BattleManagerObject();
			bool Start() override;
			void Update() override;
			void Render(RenderContext& renderContext) override {}	// Renderはない


		private:
			BattleManager* m_battleManager = nullptr;
		};
	}
}