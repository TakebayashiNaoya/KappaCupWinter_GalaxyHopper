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
		void PlayerIdleState::Enter()
		{
			/** 待機アニメーション */
			GetOwner<PlayerStateMachine>()->PlayAnimation(Player::enAnimationClip_Idle);
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
			GetOwner<PlayerStateMachine>()->PlayAnimation(Player::enAnimationClip_Walk);
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
			GetOwner<PlayerStateMachine>()->PlayAnimation(Player::enAnimationClip_Dash);
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
			GetOwner<PlayerStateMachine>()->PlayAnimation(Player::enAnimationClip_Jump);
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
			GetOwner<PlayerStateMachine>()->PlayAnimation(Player::enAnimationClip_Damage);
			/** ダメージ処理 */
			GetOwner<PlayerStateMachine>()->GetOwner<Player>()->GetStatus<PlayerStatus>()->Damage();
		}


		void PlayerDamageState::Update()
		{
		}


		void PlayerDamageState::Exit()
		{
			GetOwner<Player>()->GetPlayerStatus()->Damage();
		}




		/********************************/


		void PlayerDyingState::Enter()
		{
			/** 死亡アニメーション */
			GetOwner<PlayerStateMachine>()->PlayAnimation(Player::enAnimationClip_Die);
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