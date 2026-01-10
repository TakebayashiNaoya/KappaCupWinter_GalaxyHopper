/**
 * EnemyController.h
 * エネミーを操作する「頭脳」クラス
 */
#pragma once


 /** 思考パターンのリストマクロ定義 */
#define ENEMY_STATE_LIST(V) \
	V(Idle) \


namespace app
{
	namespace actor
	{
		class EnemyController : public IGameObject
		{
			/** 前方宣言 */
			class Player;


		public:
			/**
			 * 操作対象の設定
			 */
			void SetTarget(Player* target)
			{
				m_target = target;
			}

			/**
			 * 初期化
			 */
			static void Initialize();


		public:
			EnemyController();
			~EnemyController();


		private:
			/** 思考パターンのID */
			enum EnAIState : uint8_t
			{
				/** 思考パターンの列挙体定義(自動生成) */
#define			MAKE_ENUM(Name) enAIState_##Name,
				ENEMY_STATE_LIST(MAKE_ENUM)
#undef			MAKE_ENUM

				enAIState_Max,			/** 最大数 */
				enAIState_Invalid = -1,	/** 無効値 */
			};


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;


		private:
			/** 操作対象のプレイヤー */
			Player* m_target = nullptr;
			/** 現在の思考パターンID */
			EnAIState m_currentState = enAIStateID_Idle;
			/** 初期化済みフラグ */
			bool m_isInitialized = false;




			/********************************/


		private:
			/** 関数ポインタの型定義（記述を楽にするため） */
			using EnterFunc = void (*)(EnemyController*);
			using UpdateFunc = void (*)(EnemyController*);
			using ExitFunc = void (*)(EnemyController*);
			using CheckFunc = int (*)(EnemyController*);


		private:
			/** AI思考処理 */
			struct AIState
			{
				/**
				 * 初期化
				 * この思考に入った瞬間に1回呼ばれる
				 */
				EnterFunc enter;
				/**
				 * 更新
				 * この思考中、毎フレーム呼ばれる（入力生成など）
				 */
				UpdateFunc update;
				/**
				 * 後片付け
				 * この思考から抜ける瞬間に1回呼ばれる
				 */
				ExitFunc exit;
				/**
				 * 遷移判定
				 * 次の思考IDを返す（遷移しない場合は -1 を返す）
				 */
				CheckFunc check;
			};


		private:
			/** ステートを遷移させる処理 */
			void ChangeState(EnAIState nextState);


		private:
			/** ステートのマップ */
			static std::map<EnAIState, AIState> m_stateMap;


		private:
			/** ステートを登録する関数 */
			static void RegisterState(const EnAIState id, EnterFunc enter, UpdateFunc update, ExitFunc exit, CheckFunc check);
			/** AIStateを探す */
			AIState* FindAIState(const EnAIState id);
			/** 何もしないダミー関数 */
			static void DoNothing(EnemyController*) {}
			/** 遷移なし */
			static int CheckNothing(EnemyController*) { return -1; }




			/********************************/


			/**
			 * 各ステート関数の宣言(自動生成)
			 * ※処理はcppに記述すること
			 */
#define		DECLARE_AI_FUNCS(Name) \
			static void Enter##Name(EnemyController* npc); \
			static void Update##Name(EnemyController* npc); \
			static void Exit##Name(EnemyController* npc); \
			static int Check##Name(EnemyController* npc);

			ENEMY_STATE_LIST(DECLARE_AI_FUNCS)
#undef		DECLARE_AI_FUNCS
		};
	}
}