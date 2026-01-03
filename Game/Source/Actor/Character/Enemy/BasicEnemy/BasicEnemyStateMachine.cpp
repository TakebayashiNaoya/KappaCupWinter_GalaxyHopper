/**
 * BasicEnemyStateMachine.cpp
 * 基本エネミーのステートマシンの実装
 */
#include "stdafx.h"
#include "BasicEnemyStateMachine.h"
#include "BasicEnemy.h"
#include "Source/Actor/ActorStatus.h"
#include "BasicEnemyIState.h"


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


		core::IState* BasicEnemyStateMachine::GetChangeState()
		{
			return nullptr;
		}
	}
}