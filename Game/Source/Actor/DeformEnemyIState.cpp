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
		DeformEnemyIdleState::DeformEnemyIdleState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		DeformEnemyIdleState::~DeformEnemyIdleState()
		{
		}


		void DeformEnemyIdleState::Enter()
		{
		}


		void DeformEnemyIdleState::Update()
		{
		}


		void DeformEnemyIdleState::Exit()
		{
		}




		/********************************/


		DeformEnemyDashState::DeformEnemyDashState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		DeformEnemyDashState::~DeformEnemyDashState()
		{
		}


		void DeformEnemyDashState::Enter()
		{
		}


		void DeformEnemyDashState::Update()
		{
		}


		void DeformEnemyDashState::Exit()
		{
		}




		/********************************/


		DeformEnemyFlippingState::DeformEnemyFlippingState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		DeformEnemyFlippingState::~DeformEnemyFlippingState()
		{
		}


		void DeformEnemyFlippingState::Enter()
		{
		}


		void DeformEnemyFlippingState::Update()
		{
		}


		void DeformEnemyFlippingState::Exit()
		{
		}




		/********************************/


		DeformEnemyFlippedState::DeformEnemyFlippedState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		DeformEnemyFlippedState::~DeformEnemyFlippedState()
		{
		}


		void DeformEnemyFlippedState::Enter()
		{
		}


		void DeformEnemyFlippedState::Update()
		{
		}


		void DeformEnemyFlippedState::Exit()
		{
		}




		/********************************/


		DeformEnemySlidingState::DeformEnemySlidingState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		DeformEnemySlidingState::~DeformEnemySlidingState()
		{
		}


		void DeformEnemySlidingState::Enter()
		{
		}


		void DeformEnemySlidingState::Update()
		{
		}


		void DeformEnemySlidingState::Exit()
		{
		}




		/********************************/


		DeformEnemyDeadState::DeformEnemyDeadState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		DeformEnemyDeadState::~DeformEnemyDeadState()
		{
		}


		void DeformEnemyDeadState::Enter()
		{
		}


		void DeformEnemyDeadState::Update()
		{
		}


		void DeformEnemyDeadState::Exit()
		{
		}
	}
}