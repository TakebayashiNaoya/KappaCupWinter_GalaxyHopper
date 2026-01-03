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
		/** ステートマシン、デフォームエネミー、ステータスをキャッシュ */
		DeformEnemyStateBase::DeformEnemyStateBase(DeformEnemyStateMachine* machine, DeformEnemy* deformEnemy, DeformEnemyStatus* status)
			: m_stateMachine(machine)
			, m_deformEnemy(deformEnemy)
			, m_status(status)
		{
		}




		/********************************/


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


		void DeformEnemyWalkState::Enter()
		{
		}


		void DeformEnemyWalkState::Update()
		{
		}


		void DeformEnemyWalkState::Exit()
		{
		}




		/********************************/


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


		void DeformEnemyDieState::Enter()
		{
		}


		void DeformEnemyDieState::Update()
		{
		}


		void DeformEnemyDieState::Exit()
		{
		}
	}
}