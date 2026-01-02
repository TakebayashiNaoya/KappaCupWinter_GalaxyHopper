/**
 * PlayerIState.cpp
 * プレイヤーの各ステート実装
 */
#include "stdafx.h"
#include "PlayerIState.h"
#include "Player.h"


namespace app
{
	namespace actor
	{
		PlayerStateBase::PlayerStateBase(PlayerStateMachine* machine, Player* player, PlayerStatus* status)
			: IState(machine)
		{
			m_stateMachine = machine;
			m_player = player;
			m_status = status;
		}




		/********************************/


		void PlayerIdleState::Enter()
		{
			/** 待機アニメーション */
			m_stateMachine->PlayAnimation(EnPlayerAnimClip::Idle);
		}


		void PlayerIdleState::Update()
		{
		}


		void PlayerIdleState::Exit()
		{
		}




		/********************************/


		void PlayerWalkState::Enter()
		{
			/** 歩きアニメーション */
			GetOwnerStateMachine<PlayerStateMachine>()->PlayAnimation(EnPlayerAnimClip::Walk);
		}


		void PlayerWalkState::Update()
		{
		}


		void PlayerWalkState::Exit()
		{
		}




		/********************************/


		void PlayerDashState::Enter()
		{
			/** 走りアニメーション */
			GetOwnerStateMachine<PlayerStateMachine>()->PlayAnimation(EnPlayerAnimClip::Dash);
		}


		void PlayerDashState::Update()
		{
		}


		void PlayerDashState::Exit()
		{
		}




		/********************************/


		void PlayerJumpState::Enter()
		{
			/** ジャンプアニメーション */
			GetOwnerStateMachine<PlayerStateMachine>()->PlayAnimation(EnPlayerAnimClip::Jump);
		}


		void PlayerJumpState::Update()
		{
		}


		void PlayerJumpState::Exit()
		{
		}




		/********************************/


		void PlayerDamageState::Enter()
		{
			/** 被弾アニメーション */
			GetOwnerStateMachine<PlayerStateMachine>()->PlayAnimation(EnPlayerAnimClip::Damage);
		}


		void PlayerDamageState::Update()
		{
		}


		void PlayerDamageState::Exit()
		{
			GetOwnerStateMachine<PlayerStateMachine>()->GetOwnerChara<Player>()->ResetKnockBackTimer();
		}




		/********************************/


		void PlayerDyingState::Enter()
		{
			/** 死亡アニメーション */
			GetOwnerStateMachine<PlayerStateMachine>()->PlayAnimation(EnPlayerAnimClip::Die);
		}


		void PlayerDyingState::Update()
		{
		}


		void PlayerDyingState::Exit()
		{
		}




		/********************************/


		void PlayerDeadState::Enter()
		{
		}


		void PlayerDeadState::Update()
		{
		}


		void PlayerDeadState::Exit()
		{
		}
	}
}