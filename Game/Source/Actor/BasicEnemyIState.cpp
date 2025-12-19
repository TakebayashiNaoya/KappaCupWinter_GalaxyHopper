/**
 * BasicEnemyIState.cpp
 * ベーシックエネミーの各ステート実装
 */
#include "stdafx.h"
#include "BasicEnemyIState.h"


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


		WaitState::WaitState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		WaitState::~WaitState()
		{
		}


		void WaitState::Enter()
		{
		}


		void WaitState::Update()
		{
		}


		void WaitState::Exit()
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