#include "stdafx.h"
#include "PlayerStateMachine.h"
#include "Player.h"
#include "PlayerIState.h"


namespace app
{
	namespace actor
	{
		/** PlayerStateMachineの持ち主（Player）をStateMachineBaseに渡してください */
		PlayerStateMachine::PlayerStateMachine(Player* owner, PlayerStatus* status)
			: CharacterStateMachine(owner, status)
		{
			/** オーナーをキャッシュ */
			m_myPlayer = owner;
			/** オーナーのステータスをキャッシュ */
			m_myStatus = status;

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


		//void PlayerStateMachine::PlayAnimation(EnPlayerAnimClip animId)
		//{
		//	m_myPlayer->GetModelRender()->PlayAnimation(static_cast<uint8_t>(animId));
		//}


		IState* PlayerStateMachine::GetChangeState()
		{
			/** ダメージを受けたらダメージ状態へ */
			if (CanChangeDamage()) {
				return FindState(enPlayerState_Damage);
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
	}
}