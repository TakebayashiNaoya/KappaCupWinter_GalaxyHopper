/**
 * BattleManager.h
 * すべてのクラスの仲介を担うバトルマネージャー
 */
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
		class BattleManager
		{
		public:
			/**
			 * プレイヤーがゴールしたかを取得
			 */
			inline static bool IsGoalReached() { return m_isGoalReached; }
			/**
			 * プレイヤーがゴールしたフラグを設定
			 */
			inline static void SetIsGoalReached(const bool isReached) { m_isGoalReached = isReached; }
			/**
			 * リザルトのシーケンス中かを取得
			 */
			inline static bool IsResultSequence() { return m_isResultSequence; }
			/**
			 * リザルトのシーケンス中フラグを設定
			 */
			inline static void SetIsResultSequence(const bool isResultSequence) { m_isResultSequence = isResultSequence; }


		public:
			/** 勝敗 */
			enum class EnBattleResult : uint8_t
			{
				enBattleResult_None,   // 戦闘中
				enBattleResult_Win,    // 勝ち
				enBattleResult_Lose    // 負け
			};
			/** 勝敗を取得 */
			inline static EnBattleResult GetBattleResult() { return m_battleResult; }

		private:
			/** 勝敗を格納する変数 */
			static EnBattleResult m_battleResult;



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
				K2_ASSERT(false, "処理追加忘れ");
			}
			template<typename T>
			void Unregister(T* object)
			{
				K2_ASSERT(false, "処理追加忘れ");
			}


		private:
			/** プレイヤーがゴールしたか */
			static bool m_isGoalReached;
			/** UIを非表示にすべきか */
			static bool m_isResultSequence;

			/** ギア取得数 */
			int m_gotGearCount = 0;
			/** 出現ギア数 */
			int m_maxGearCount = 0;

			/** プレイヤー */
			actor::Player* m_player = nullptr;
			/** ボスエネミー */
			actor::BossEnemy* m_bossEnemy = nullptr;
			/** 基本エネミーリスト */
			std::vector<actor::BasicEnemy*> m_basicEnemies;
			/** 変形エネミーリスト */
			std::vector<actor::DeformEnemy*> m_deformEnemies;
			/** ロケット */
			actor::Rocket* m_rocket = nullptr;
			/** 宝箱リスト */
			std::vector<actor::Treasure*> m_treasures;
			///** その他汎用オブジェクトリスト */
			//std::vector<IGameObject*> m_objects;

			/** ギアUI */
			ui::UIGear* m_uiGear = nullptr;
			/** プレイヤーHPUI */
			ui::UIPlayerHp* m_uiPlayerHp = nullptr;
			/** ダメージフラッシュUI */
			ui::UIDamageFlash* m_uiDamageFlash = nullptr;
			/** ボスHPUI */
			ui::UIBossHp* m_uiBossHp = nullptr;


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
		};




		/********************************/


		/// <summary>
		/// 当たり判定管理クラスを更新したりするためのゲームオブジェクト。
		/// </summary>
		class BattleManagerObject : public IGameObject
		{
		public:
			BattleManagerObject();
			~BattleManagerObject();
			bool Start() override final;
			void Update() override final;
			/** Renderは使用しない */
			void Render(RenderContext& renderContext) override final {}


		private:
			BattleManager* m_battleManager = nullptr;
		};
	}
}