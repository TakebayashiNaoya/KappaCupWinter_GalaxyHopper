/**
 * PlayerIState.cpp
 * プレイヤーの各ステート実装
 */
#include "stdafx.h"
#include "PlayerIState.h"
#include "Player.h"
#include "PlayerStateMachine.h"


namespace app
{
	namespace actor
	{
		/** ステートマシン、プレイヤー、ステータスをキャッシュ */
		PlayerStateBase::PlayerStateBase(PlayerStateMachine* machine, Player* player, PlayerStatus* status)
			: m_stateMachine(machine)
			, m_player(player)
			, m_status(status)
		{
		}




		/********************************/


		void PlayerIdleState::Enter()
		{
			/** 待機アニメーション */
			m_stateMachine->PlayAnimation(Player::EnPlayerAnimClip::Idle);
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
			m_stateMachine->PlayAnimation(Player::EnPlayerAnimClip::Walk);
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
			m_stateMachine->PlayAnimation(Player::EnPlayerAnimClip::Dash);
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
			m_stateMachine->PlayAnimation(Player::EnPlayerAnimClip::Jump);
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
			m_stateMachine->PlayAnimation(Player::EnPlayerAnimClip::Damage);
			/** 入力をはじく */
			m_stateMachine->SetIsInputBlocked(true);
		}


		void PlayerDamageState::Update()
		{
		}


		void PlayerDamageState::Exit()
		{
			/** 入力を受け付ける */
			m_stateMachine->SetIsInputBlocked(false);
		}




		/********************************/


		void PlayerDyingState::Enter()
		{
			/** 死亡アニメーション */
			m_stateMachine->PlayAnimation(Player::EnPlayerAnimClip::Die);
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