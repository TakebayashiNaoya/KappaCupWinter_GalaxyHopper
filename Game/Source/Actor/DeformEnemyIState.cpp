/**
 * DeformEnemyIState.cpp
 * デフォームエネミーの各ステート実装
 */
#include "stdafx.h"
#include "DeformEnemyIState.h"


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


		FlippingState::FlippingState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		FlippingState::~FlippingState()
		{
		}


		void FlippingState::Enter()
		{
		}


		void FlippingState::Update()
		{
		}


		void FlippingState::Exit()
		{
		}




		/********************************/


		FlippedState::FlippedState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		FlippedState::~FlippedState()
		{
		}


		void FlippedState::Enter()
		{
		}


		void FlippedState::Update()
		{
		}


		void FlippedState::Exit()
		{
		}




		/********************************/


		SlidingState::SlidingState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		SlidingState::~SlidingState()
		{
		}


		void SlidingState::Enter()
		{
		}


		void SlidingState::Update()
		{
		}


		void SlidingState::Exit()
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