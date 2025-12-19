#include "stdafx.h"
#include "PlayerStateMachine.h"
#include "Player.h"
#include "PlayerIState.h"


namespace app
{
	namespace actor
	{
		/** PlayerStateMachineの持ち主（Player）をStateMachineBaseに渡してください */
		PlayerStateMachine::PlayerStateMachine(Player* owner)
			: StateMachineBase(owner)
		{
			/** ステートの生成 */
			AddState<IdleState>(enPlayerState_Idle);
			AddState<WalkState>(enPlayerState_Walk);
			AddState<DashState>(enPlayerState_Dash);
			AddState<JumpState>(enPlayerState_Jump);
			AddState<DamageState>(enPlayerState_Damage);
			AddState<DyingState>(enPlayerState_Dying);
			AddState<DeadState>(enPlayerState_Dead);
			K2_ASSERT(m_stateMap.size() == enPlayerState_Num, "AddStateを呼んでください");

			/** 初期ステート */
			m_currentState = m_stateMap[enPlayerState_Idle];
		}


		PlayerStateMachine::~PlayerStateMachine()
		{
			/** ステートの破棄は~StateMachineBase()で行っているので、ここでは必要ありません */
		}


		IState* PlayerStateMachine::GetChangeState()
		{
			/** ダメージ状態に変更できるか */
			if (CanChangeDamage()) {
				return FindState(enPlayerState_Damage);
			}

			/** 死亡中状態なら */
			if (IsEqualCurrentState(enPlayerState_Dying)) {
				/** 死亡完了状態に変更できるか */
				if (CanChangeDead()) {
					return FindState(enPlayerState_Dead);
				}
			}

			/** 死亡開始状態に変更できるか */
			if (CanChangeDying()) {
				return FindState(enPlayerState_Dying);
			}
			/** ジャンプ状態に変更できるか */
			if (CanChangeJump()) {
				return FindState(enPlayerState_Jump);
			}
			/** 走る状態に変更できるか */
			if (CanChangeDush()) {
				return FindState(enPlayerState_Dash);
			}
			/** 歩く状態に変更できるか */
			if (CanChangeWalk()) {
				return FindState(enPlayerState_Walk);
			}
			/** どの状態にも変更できなければ、待機状態に戻る */
			return FindState(enPlayerState_Idle);
		}


		bool PlayerStateMachine::CanChangeJump()
		{
			if (IsOnGround() == false) {
				return true;
			}
			return false;
		}
	}
}