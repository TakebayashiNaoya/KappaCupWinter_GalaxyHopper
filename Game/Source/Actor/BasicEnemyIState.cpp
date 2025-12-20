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
		BasicEnemyIdleState::BasicEnemyIdleState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		BasicEnemyIdleState::~BasicEnemyIdleState()
		{
		}


		void BasicEnemyIdleState::Enter()
		{
		}


		void BasicEnemyIdleState::Update()
		{
		}


		void BasicEnemyIdleState::Exit()
		{
		}




		/********************************/


		BasicEnemyDashState::BasicEnemyDashState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		BasicEnemyDashState::~BasicEnemyDashState()
		{
		}


		void BasicEnemyDashState::Enter()
		{
		}


		void BasicEnemyDashState::Update()
		{
		}


		void BasicEnemyDashState::Exit()
		{
		}




		/********************************/


		BasicEnemyWaitState::BasicEnemyWaitState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		BasicEnemyWaitState::~BasicEnemyWaitState()
		{
		}


		void BasicEnemyWaitState::Enter()
		{
		}


		void BasicEnemyWaitState::Update()
		{
		}


		void BasicEnemyWaitState::Exit()
		{
		}




		/********************************/


		BasicEnemyDeadState::BasicEnemyDeadState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		BasicEnemyDeadState::~BasicEnemyDeadState()
		{
		}


		void BasicEnemyDeadState::Enter()
		{
		}


		void BasicEnemyDeadState::Update()
		{
		}


		void BasicEnemyDeadState::Exit()
		{
		}
	}
}