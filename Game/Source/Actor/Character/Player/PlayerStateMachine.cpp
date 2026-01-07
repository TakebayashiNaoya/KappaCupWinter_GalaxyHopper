#include "stdafx.h"
#include "PlayerStateMachine.h"
#include "Player.h"
#include "Source/Actor/ActorStatus.h"
#include "PlayerIState.h"


namespace app
{
	namespace actor
	{
		/** 持ち主（Player）とステータス（PlayerStatus）をCharacterStateMachineに渡す */
		PlayerStateMachine::PlayerStateMachine(Player* owner, PlayerStatus* status)
			: CharacterStateMachine(owner, status)
			, m_myPlayer(owner)
			, m_myStatus(status)
		{
			/** ステートの生成 */
			AddState<PlayerIdleState>(Idle);
			AddState<PlayerWalkState>(Walk);
			AddState<PlayerDashState>(Dash);
			AddState<PlayerJumpState>(Jump);
			AddState<PlayerDamageState>(Damage);
			AddState<PlayerDyingState>(Dying);
			AddState<PlayerDeadState>(Dead);
			K2_ASSERT(m_stateMap.size() == Num, "AddStateを呼んでください");

			/** 初期ステート */
			m_currentState = m_stateMap[Idle];
		}


		PlayerStateMachine::~PlayerStateMachine()
		{
		}


		core::IState* PlayerStateMachine::GetChangeState()
		{
			/** ダメージを受けたらダメージ状態へ */
			if (CanChangeDamage()) {
				return FindState(Damage);
			}
			/** 条件が満たされるまでダメージ状態を維持 */
			if (IsEqualCurrentState(Damage)) {
				if (!IsDamageStateFinished()) {
					return nullptr;
				}
			}

			/** 死亡中ならアニメーションが終わるまでステートを維持し、終わったら完全死亡状態へ */
			if (IsEqualCurrentState(Dying)) {
				if (CanChangeDead()) {
					return FindState(Dead);
				}
			}

			/** HPが0になっていたら死亡開始状態へ */
			if (CanChangeDying()) {
				return FindState(Dying);
			}

			/** 足が着いていなければジャンプ状態へ */
			if (CanChangeJump()) {
				return FindState(Jump);
			}

			/** ダッシュ入力があり、かつ移動入力があるならダッシュ状態へ */
			if (CanChangeDush()) {
				return FindState(Dash);
			}

			/** 移動入力があるなら歩き状態へ */
			if (CanChangeWalk()) {
				return FindState(Walk);
			}

			/** どれにも当てはまらなければ待機状態へ */
			return FindState(Idle);
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