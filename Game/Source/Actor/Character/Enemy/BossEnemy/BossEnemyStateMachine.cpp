/**
 * BossEnemyStateMachine.cpp
 * ボスエネミーのステートマシンの実装
 */
#include "stdafx.h"
#include "BossEnemy.h"
#include "BossEnemyIState.h"
#include "BossEnemyStateMachine.h"
#include "Source/Actor/ActorStatus.h"


namespace app
{
	namespace actor
	{
		BossEnemy* BossEnemyStateMachine::GetOwner() const
		{
			return static_cast<BossEnemy*>(m_ownerActor);
		}


		BossEnemyStatus* BossEnemyStateMachine::GetStatus() const
		{
			return GetOwner()->GetStatus<BossEnemyStatus>();
		}


		BossEnemyStateMachine::BossEnemyStateMachine(BossEnemy* owner)
			: CharacterStateMachine(owner)
		{
			/** ステートの生成 */
			AddState<BossEnemyIdleState>(enBossEnemyState_Idle);
			AddState<BossEnemyWalkState>(enBossEnemyState_Walk);
			AddState<BossEnemyDashState>(enBossEnemyState_Dash);
			AddState<BossEnemyAttackState>(enBossEnemyState_Attack);
			AddState<BossEnemyCooldownState>(enBossEnemyState_Cooldown);
			AddState<BossEnemyDamageState>(enBossEnemyState_Damage);
			AddState<BossEnemyDyingState>(enBossEnemyState_Dying);
			AddState<BossEnemyDeadState>(enBossEnemyState_Dead);
			K2_ASSERT(m_stateMap.size() == enBossEnemyState_Num, "AddStateを呼んでください");

			/** 初期ステート */
			m_currentState = m_stateMap[enBossEnemyState_Idle];
		}


		BossEnemyStateMachine::~BossEnemyStateMachine()
		{
		}


		core::IState* BossEnemyStateMachine::GetChangeState()
		{
			return nullptr;
		}
	}
}