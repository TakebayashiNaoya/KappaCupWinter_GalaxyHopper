#include "stdafx.h"
#include "Player.h"
#include "PlayerIState.h"
#include "PlayerStateMachine.h"
#include "Source/Actor/ActorStatus.h"


namespace app
{
	namespace actor
	{
		/** 持ち主（Player）とステータス（PlayerStatus）をCharacterStateMachineに渡す */
		PlayerStateMachine::PlayerStateMachine(Player* owner)
			:CharacterStateMachine(owner)
		{
			/** ステートの生成 */
			AddState<PlayerIdleState>(enPlayerState_Idle);
			AddState<PlayerWalkState>(enPlayerState_Walk);
			AddState<PlayerDashState>(enPlayerState_Dash);
			AddState<PlayerJumpState>(enPlayerState_Jump);
			AddState<PlayerDamageState>(enPlayerState_Damage);
			AddState<PlayerDyingState>(enPlayerState_Dying);
			AddState<PlayerDeadState>(enPlayerState_Dead);
			K2_ASSERT(m_stateMap.size() == enPlayerState_Num, "AddStateを呼んでください");

			/** 初期ステート */
			m_currentState = m_stateMap[enPlayerState_Idle];
		}


		PlayerStateMachine::~PlayerStateMachine()
		{
		}


		core::IState* PlayerStateMachine::GetChangeState()
		{
			/** ダメージを受けたらダメージ状態へ */
			if (CanChangeDamage()) {
				return FindState(enPlayerState_Damage);
			}
			/** 条件が満たされるまでダメージ状態を維持 */
			if (IsEqualCurrentState(enPlayerState_Damage)) {
				if (!IsDamageStateFinished()) {
					return nullptr;
				}
			}

			/** 死亡中ならアニメーションが終わるまでステートを維持し、終わったら完全死亡状態へ */
			if (IsEqualCurrentState(enPlayerState_Dying)) {
				if (CanChangeDead()) {
					return FindState(enPlayerState_Dead);
				}
			}

			/** HPが0になっていたら死亡開始状態へ */
			if (CanChangeDying()) {
				return FindState(enPlayerState_Dying);
			}

			/** 足が着いていなければジャンプ状態へ */
			if (CanChangeJump()) {
				return FindState(enPlayerState_Jump);
			}

			/** ダッシュ入力があり、かつ移動入力があるならダッシュ状態へ */
			if (CanChangeDush()) {
				return FindState(enPlayerState_Dash);
			}

			/** 移動入力があるなら歩き状態へ */
			if (CanChangeWalk()) {
				return FindState(enPlayerState_Walk);
			}

			/** どれにも当てはまらなければ待機状態へ */
			return FindState(enPlayerState_Idle);
		}


		bool PlayerStateMachine::CanChangeJump()
		{
			if (IsOnGround() == false) {
				return true;
			}
			return false;
		}


		bool PlayerStateMachine::IsDamageStateFinished()
		{
			/** ノックバックによる移動速度が0以下になったらダメージ状態終了 */
			if (m_moveSpeed <= 0.0f) {
				return true;
			}
			return false;
		}
	}
}