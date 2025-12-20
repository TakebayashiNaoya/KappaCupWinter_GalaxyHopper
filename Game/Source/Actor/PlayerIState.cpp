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