/**
 * BossEnemyStateMachine.cpp
 * ボスエネミーのステートマシンの実装
 */
#include "stdafx.h"
#include "BossEnemyStateMachine.h"
#include "BossEnemy.h"
#include "Source/Actor/ActorStatus.h"
#include "BossEnemyIState.h"


namespace app
{
	namespace actor
	{
		BossEnemyStateMachine::BossEnemyStateMachine(BossEnemy* owner, BossEnemyStatus* status)
			: CharacterStateMachine(owner, status)
			, m_bossEnemy(owner)
			, m_bossEnemyStatus(status)
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