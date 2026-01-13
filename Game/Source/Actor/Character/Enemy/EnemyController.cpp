/**
 * EnemyController.cpp
 * エネミーを操作する「頭脳」クラスの実装
 */
#include "stdafx.h"
 //#include "actor/StateMachine.h"
#include "EnemyController.h"
#include "Source/Actor/Character/Player/Player.h"
#include "Source/Actor/Character/Enemy/Enemy.h"


namespace app
{
	namespace actor
	{
		/** Static変数の初期化 */
		std::map<EnemyController::EnAIState, EnemyController::AIState> EnemyController::m_stateMap;


		void EnemyController::Initialize()
		{
			/** 引数に入れた文字列をNameの場所に置き換えるルールを作成 */
#define		REGISTER_AI_STATE(Name) \
			RegisterState(enAIState_##Name, Enter##Name, Update##Name, Exit##Name, Check##Name);
			/** ヘッダーで定義したNPC_STATE_LIST(V)のVの部分に、さっき作ったREGISTER_AI_STATEを当てはめる */
			ENEMY_STATE_LIST(REGISTER_AI_STATE);
			/** マクロ解放 */
#undef		REGISTER_AI_STATE
		}


		EnemyController::EnemyController()
		{
		}


		EnemyController::~EnemyController()
		{
		}


		bool EnemyController::Start()
		{
			return true;
		}


		void EnemyController::Update()
		{
			/** 前フレームの位置を保存 */
			auto* currentState = FindAIState(m_currentState);
			if (currentState == nullptr) {
				K2_ASSERT(false, "対象の処理が見つかりません\n");
				return;
			}

			/** 初回起動時のEnter処理 */
			if (!m_isInitialized) {
				currentState->enter(this);
				m_isInitialized = true;
			}

			/** 遷移判定 */
			const int nextState = currentState->check(this);
			/** 遷移が必要な場合の処理 */
			if (nextState != -1 && nextState != m_currentState) {
				ChangeState((EnAIState)nextState);
				currentState = FindAIState(m_currentState);
			}

			/** 現在のステートの更新処理 */
			currentState->update(this);

			//prePosition = m_target->m_transform.m_position;
		}


		void EnemyController::Render(RenderContext& rc)
		{
		}




		/********************************/


		void EnemyController::ChangeState(EnAIState nextState)
		{
			/** 不正なステートIDなら何もしない */
			if (nextState < enAIState_Invalid || nextState >= enAIState_Max) {
				return;
			}

			/** 現在のステートの終了処理→次のステートの開始処理 */
			auto* currentState = FindAIState(m_currentState);
			currentState->exit(this);
			m_currentState = nextState;
			currentState = FindAIState(m_currentState);
			currentState->enter(this);
		}


		void EnemyController::RegisterState(const EnAIState id, EnterFunc enter, UpdateFunc update, ExitFunc exit, CheckFunc check)
		{
			AIState state;
			/** 引数が nullptr ならダミー関数を入れる（これで呼び出し側でのnullptrチェックが不要になる） */
			state.enter = (enter != nullptr) ? enter : DoNothing;
			state.update = (update != nullptr) ? update : DoNothing;
			state.exit = (exit != nullptr) ? exit : DoNothing;
			state.check = (check != nullptr) ? check : CheckNothing;
			/** mapに登録 */
			m_stateMap.emplace(id, state);
		}

		EnemyController::AIState* EnemyController::FindAIState(const EnAIState id)
		{
			auto it = m_stateMap.find(id);
			if (it != m_stateMap.end()) {
				return &it->second;
			}
			return nullptr;
		}




		/********************************/


		void EnemyController::EnterIdle(EnemyController* npc)
		{
		}


		void EnemyController::UpdateIdle(EnemyController* npc)
		{
			/** ターゲットが未設定ならプレイヤーを探す */
			if (npc->m_target == nullptr) {
				npc->m_target = FindGO<Player>("Player");
			};
			/** ターゲットが見つからなかったら何もしない */
			if (npc->m_target == nullptr) return;
			/** ターゲットが死んでいたらターゲットから解除する */
			if (npc->m_target->GetStatus<PlayerStatus>()->GetHp() <= 0) {
				npc->m_target = nullptr;
				npc->m_isFoundTarget = false;
				return;
			}
			/** ターゲットまでのベクトルを算出 */
			Vector3 targetPosition = npc->m_target->GetTransform().m_position;
			Vector3 ownerPosition = npc->m_owner->GetTransform().m_position;
			Vector3 targetDistance = targetPosition - ownerPosition;
			/** ターゲットとの距離が一定以下ならターゲット発見のフラグを立てる */
			float searchRange = npc->m_target->GetStatus<EnemyStatus>()->GetSearchRange();
			if (targetDistance.Length() < searchRange) {
				npc->m_isFoundTarget = true;
			}
			/** ボスであれば問答無用で発見フラグを立てる */
			else if (npc->m_aiType == EnAIType::BossEnemy) {
				npc->m_isFoundTarget = true;
			}
			else {
				npc->m_isFoundTarget = false;
			}
		}


		void EnemyController::ExitIdle(EnemyController* npc)
		{
		}


		int EnemyController::CheckIdle(EnemyController* npc)
		{
			/** ターゲットを発見していたら追跡状態へ移行 */
			if (npc->m_isFoundTarget == false) {
				return enAIState_Invalid;
			}

			/** エネミーのタイプ別に遷移先を変える */
			switch (npc->m_aiType)
			{
				/** ベーシックエネミーとボスエネミーはターゲットを追いかける */
			case EnAIType::BasicEnemy:
			case EnAIType::BossEnemy:
				return enAIState_Chase;

				/** 変形エネミーは逃げる */
			case EnAIType::DeformEnemy:
				return enAIState_Flee;

				/** それ以外は無効 */
			default:
				return enAIState_Invalid;
			}
		}




		/********************************/


		void EnemyController::EnterChase(EnemyController* npc)
		{
		}


		void EnemyController::UpdateChase(EnemyController* npc)
		{
			/** ターゲットが死んでいたらターゲットから解除する */
			if (npc->m_target->GetStatus<PlayerStatus>()->GetHp() <= 0) {
				npc->m_target = nullptr;
				npc->m_isFoundTarget = false;
				return;
			}
		}


		void EnemyController::ExitChase(EnemyController* npc)
		{
		}


		int EnemyController::CheckChase(EnemyController* npc)
		{
		}




		/********************************/


		void EnemyController::EnterFlee(EnemyController* npc)
		{
		}


		void EnemyController::UpdateFlee(EnemyController* npc)
		{
		}


		void EnemyController::ExitFlee(EnemyController* npc)
		{
		}


		int EnemyController::CheckFlee(EnemyController* npc)
		{
		}
	}