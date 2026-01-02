/**
 * EnemyStateMachine.cpp
 * エネミーのステートマシンの実装
 */
#include "stdafx.h"
#include "EnemyStateMachine.h"
#include "BasicEnemy/BasicEnemy.h"
#include "DeformEnemy/DeformEnemy.h"
#include "BossEnemy/BossEnemy.h"
#include "Source/Actor/Character/Enemy/BasicEnemy/BasicEnemyIState.h"
#include "Source/Actor/Character/Enemy/DeformEnemy/DeformEnemyIState.h"
#include "Source/Actor/Character/Enemy/BossEnemy/BossEnemyIState.h"


namespace app
{
	namespace actor
	{
		BasicEnemyStateMachine::BasicEnemyStateMachine(BasicEnemy* owner, BasicEnemyStatus* status)
			: CharacterStateMachine(owner, status)
			, m_basicEnemy(owner)
			, m_basicEnemyStatus(status)
		{
			/** ステートの生成 */
			AddState<BasicEnemyIdleState>(enBasicEnemyState_Idle);
			AddState<BasicEnemyDashState>(enBasicEnemyState_Dash);
			AddState<BasicEnemyCooldownState>(enBasicEnemyState_Cooldown);
			AddState<BasicEnemyDieState>(enBasicEnemyState_Die);
			K2_ASSERT(m_stateMap.size() == enBasicEnemyState_Num, "AddStateを呼んでください");

			/** 初期ステート */
			m_currentState = m_stateMap[enBasicEnemyState_Idle];
		}


		BasicEnemyStateMachine::~BasicEnemyStateMachine()
		{
		}


		IState* BasicEnemyStateMachine::GetChangeState()
		{
			return nullptr;
		}




		/********************************/


		DeformEnemyStateMachine::DeformEnemyStateMachine(DeformEnemy* owner, DeformEnemyStatus* status)
			: CharacterStateMachine(owner, status)
			, m_deformEnemy(owner)
			, m_deformEnemyStatus(status)
		{
			/** ステートの生成 */
			AddState<DeformEnemyIdleState>(enDeformEnemyState_Idle);
			AddState<DeformEnemyWalkState>(enDeformEnemyState_Walk);
			AddState<DeformEnemyFlippingState>(enDeformEnemyState_Flipping);
			AddState<DeformEnemyFlippedState>(enDeformEnemyState_Flipped);
			AddState<DeformEnemySlidingState>(enDeformEnemyState_Sliding);
			AddState<DeformEnemyDieState>(enDeformEnemyState_Die);
			K2_ASSERT(m_stateMap.size() == enDeformEnemyState_Num, "AddStateを呼んでください");

			/** 初期ステート */
			m_currentState = m_stateMap[enDeformEnemyState_Idle];
		}


		DeformEnemyStateMachine::~DeformEnemyStateMachine()
		{
		}


		IState* DeformEnemyStateMachine::GetChangeState()
		{
			return nullptr;
		}




		/********************************/


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


		IState* BossEnemyStateMachine::GetChangeState()
		{
			return nullptr;
		}
	}
}