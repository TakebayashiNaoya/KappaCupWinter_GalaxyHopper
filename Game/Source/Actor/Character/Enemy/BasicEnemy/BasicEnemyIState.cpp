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
		/** ステートマシン、エネミー、ステータスをキャッシュ */
		BasicEnemyStateBase::BasicEnemyStateBase(BasicEnemyStateMachine* machine, BasicEnemy* enemy, BasicEnemyStatus* status)
			: m_stateMachine(machine)
			, m_enemy(enemy)
			, m_status(status)
		{
		}




		/********************************/


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


		void BasicEnemyCooldownState::Enter()
		{
		}


		void BasicEnemyCooldownState::Update()
		{
		}


		void BasicEnemyCooldownState::Exit()
		{
		}




		/********************************/


		void BasicEnemyDieState::Enter()
		{
		}


		void BasicEnemyDieState::Update()
		{
		}


		void BasicEnemyDieState::Exit()
		{
		}
	}
}