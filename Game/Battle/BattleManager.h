/**
 * BattleManager.h
 * すべてのクラスの仲介を担うバトルマネージャー
 */
#pragma once
#include <algorithm>

namespace app
{
	namespace actor
	{
		class Player;
		class BossEnemy;
		class BasicEnemy;
		class DeformEnemy;
		class EnemyController;
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
				Fighting,   // 戦闘中
				Win,		// 勝ち
				Lose		// 負け
			};
			/** 勝敗を取得 */
			inline static EnBattleResult GetBattleResult() { return m_battleResult; }

		private:
			/** 勝敗を格納する変数 */
			static EnBattleResult m_battleResult;


			/**
			 * 登録・登録解除関数群の自動生成マクロ
			 */
		public:
			/** 単体(actor名前空間用) */
#define		REG_ACTOR_SINGLE(Type, Var) \
			void Register(actor::Type* obj) { Var = obj; } \
			void Unregister(actor::Type* obj) { if (Var == obj) Var = nullptr; }

			/** リスト(actor名前空間用) */
#define		REG_ACTOR_LIST(Type, List) \
			void Register(actor::Type* obj) { List.push_back(obj); } \
			void Unregister(actor::Type* obj) { \
				auto it = std::remove(List.begin(), List.end(), obj); \
				List.erase(it, List.end()); \
			}

			/** 単体(ui名前空間用) */
#define		REG_UI_SINGLE(Type, Var) \
			void Register(ui::Type* obj) { Var = obj; } \
			void Unregister(ui::Type* obj) { if (Var == obj) Var = nullptr; }


			/**
			 * 登録・登録解除関数群の自動生成の実装
			 */
		public:
			/** 単体系 */
			REG_ACTOR_SINGLE(Player, m_player);
			REG_ACTOR_SINGLE(BossEnemy, m_bossEnemy);
			REG_ACTOR_SINGLE(Rocket, m_rocket);

			/** リスト系 */
			REG_ACTOR_LIST(BasicEnemy, m_basicEnemies);
			REG_ACTOR_LIST(DeformEnemy, m_deformEnemies);
			REG_ACTOR_LIST(EnemyController, m_enemyControllers);
			REG_ACTOR_LIST(Treasure, m_treasures);

			/** UI系 */
			REG_UI_SINGLE(UIGear, m_uiGear);
			REG_UI_SINGLE(UIPlayerHp, m_uiPlayerHp);
			REG_UI_SINGLE(UIDamageFlash, m_uiDamageFlash);
			REG_UI_SINGLE(UIBossHp, m_uiBossHp);

			/** その他汎用 */
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

#undef REG_ACTOR_SINGLE
#undef REG_UI_SINGLE
#undef REG_ACTOR_LIST


		public:
			/**
			 * シーンのデストラクタで呼び出す
			 * 雑魚エネミーの削除やシーンが削除する物のポインタクリアを行う
			 */
			void CleanUp();
		private:
			/**
			 * 雑魚エネミーを全てDeleteGOする関数
			 * 雑魚エネミーはシーン中で増減するため、バトルマネージャーで削除を行う
			 */
			void DestroyManagedEnemies();
			/** シーンが削除する物のポインタをクリアする */
			void ResetReferences();


		private:
			/**
			 * 内部処理用関数群
			 */
			 /** エネミーの削除やターゲット更新 */
			void UpdateEnemies();
			/** 宝箱やロケットなどのギミック処理 */
			void UpdateInteractions();
			/** 各種UIの表示更新 */
			void UpdateUI();
			/** 勝敗判定やリザルト移行判定 */
			void UpdateBattleState();


		private:
			/** プレイヤーがゴールしたか */
			static bool m_isGoalReached;
			/** UIを非表示にすべきか */
			static bool m_isResultSequence;

			/** ギア取得数 */
			int m_gotGearCount = 0;
			/** ギアの出現数 */
			int m_maxGearCount = 0;

			/** プレイヤー */
			actor::Player* m_player = nullptr;
			/** ボスエネミー */
			actor::BossEnemy* m_bossEnemy = nullptr;
			/** 基本エネミーリスト */
			std::vector<actor::BasicEnemy*> m_basicEnemies;
			/** 変形エネミーリスト */
			std::vector<actor::DeformEnemy*> m_deformEnemies;
			/** エネミーコントローラーリスト */
			std::vector<actor::EnemyController*> m_enemyControllers;
			/** ロケット */
			actor::Rocket* m_rocket = nullptr;
			/** 宝箱リスト */
			std::vector<actor::Treasure*> m_treasures;
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
			bool Enter();
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


		/**
		 * 当たり判定管理クラスを更新したりするためのゲームオブジェクト
		 */
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