/**
 * BossEnemyIState.cpp
 * ボスエネミーの各ステート実装
 */
#include "stdafx.h"
#include "BossEnemyIState.h"


namespace app
{
	namespace actor
	{
		BossEnemyIdleState::BossEnemyIdleState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		BossEnemyIdleState::~BossEnemyIdleState()
		{
		}


		void BossEnemyIdleState::Enter()
		{
		}


		void BossEnemyIdleState::Update()
		{
		}


		void BossEnemyIdleState::Exit()
		{
		}




		/********************************/


		BossEnemyWalkState::BossEnemyWalkState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		BossEnemyWalkState::~BossEnemyWalkState()
		{
		}


		void BossEnemyWalkState::Enter()
		{
		}


		void BossEnemyWalkState::Update()
		{
		}


		void BossEnemyWalkState::Exit()
		{
		}




		/********************************/


		BossEnemyDashState::BossEnemyDashState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		BossEnemyDashState::~BossEnemyDashState()
		{
		}


		void BossEnemyDashState::Enter()
		{
		}


		void BossEnemyDashState::Update()
		{
		}


		void BossEnemyDashState::Exit()
		{
		}




		/********************************/


		BossEnemyAttackState::BossEnemyAttackState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		BossEnemyAttackState::~BossEnemyAttackState()
		{
		}


		void BossEnemyAttackState::Enter()
		{
		}


		void BossEnemyAttackState::Update()
		{
		}


		void BossEnemyAttackState::Exit()
		{
		}




		/********************************/


		BossEnemyCoolDownState::BossEnemyCoolDownState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		BossEnemyCoolDownState::~BossEnemyCoolDownState()
		{
		}


		void BossEnemyCoolDownState::Enter()
		{
		}


		void BossEnemyCoolDownState::Update()
		{
		}


		void BossEnemyCoolDownState::Exit()
		{
		}




		/********************************/


		BossEnemyDamageState::BossEnemyDamageState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		BossEnemyDamageState::~BossEnemyDamageState()
		{
		}


		void BossEnemyDamageState::Enter()
		{
		}


		void BossEnemyDamageState::Update()
		{
		}


		void BossEnemyDamageState::Exit()
		{
		}




		/********************************/


		BossEnemyDyingState::BossEnemyDyingState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		BossEnemyDyingState::~BossEnemyDyingState()
		{
		}


		void BossEnemyDyingState::Enter()
		{
		}


		void BossEnemyDyingState::Update()
		{
		}


		void BossEnemyDyingState::Exit()
		{
		}




		/********************************/


		BossEnemyDeadState::BossEnemyDeadState(StateMachineBase* owner)
			: IState(owner)
		{
		}


		BossEnemyDeadState::~BossEnemyDeadState()
		{
		}


		void BossEnemyDeadState::Enter()
		{
		}


		void BossEnemyDeadState::Update()
		{
		}


		void BossEnemyDeadState::Exit()
		{
		}
	}
}