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
		IdleState::IdleState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		IdleState::~IdleState()
		{
		}


		void IdleState::Enter()
		{
			/** 待機アニメーション */
			GetOwner<PlayerStateMachine>()->PlayAnimation(Player::enAnimationClip_Idle);
		}


		void IdleState::Update()
		{
		}


		void IdleState::Exit()
		{
		}




		/********************************/


		WalkState::WalkState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		WalkState::~WalkState()
		{
		}


		void WalkState::Enter()
		{
			/** 歩きアニメーション */
			GetOwner<PlayerStateMachine>()->PlayAnimation(Player::enAnimationClip_Walk);
		}


		void WalkState::Update()
		{
		}


		void WalkState::Exit()
		{
		}




		/********************************/


		DashState::DashState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		DashState::~DashState()
		{
		}


		void DashState::Enter()
		{
			/** 走りアニメーション */
			GetOwner<PlayerStateMachine>()->PlayAnimation(Player::enAnimationClip_Dash);
		}


		void DashState::Update()
		{
		}


		void DashState::Exit()
		{
		}




		/********************************/


		JumpState::JumpState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		JumpState::~JumpState()
		{
		}


		void JumpState::Enter()
		{
			/** ジャンプアニメーション */
			GetOwner<PlayerStateMachine>()->PlayAnimation(Player::enAnimationClip_Jump);
		}


		void JumpState::Update()
		{
		}


		void JumpState::Exit()
		{
		}




		/********************************/


		DamageState::DamageState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		DamageState::~DamageState()
		{
		}


		void DamageState::Enter()
		{
			/** 被弾アニメーション */
			GetOwner<PlayerStateMachine>()->PlayAnimation(Player::enAnimationClip_Damage);
			/** ダメージ処理 */
			GetOwner<Player>()->GetStatus<PlayerStatus>()->Damage();
		}


		void DamageState::Update()
		{
		}


		void DamageState::Exit()
		{
		}




		/********************************/


		DyingState::DyingState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		DyingState::~DyingState()
		{
		}


		void DyingState::Enter()
		{
			/** 死亡アニメーション */
			GetOwner<PlayerStateMachine>()->PlayAnimation(Player::enAnimationClip_Die);
		}


		void DyingState::Update()
		{
		}


		void DyingState::Exit()
		{
		}




		/********************************/


		DeadState::DeadState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		DeadState::~DeadState()
		{
		}


		void DeadState::Enter()
		{
		}


		void DeadState::Update()
		{
		}


		void DeadState::Exit()
		{
		}
	}
}