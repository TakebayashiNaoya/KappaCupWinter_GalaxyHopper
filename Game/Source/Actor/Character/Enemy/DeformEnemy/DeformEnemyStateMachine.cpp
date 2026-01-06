/**
 * DeformEnemyStateMachine.cpp
 * 変形エネミーのステートマシンの実装
 */
#include "stdafx.h"
#include "DeformEnemyStateMachine.h"
#include "DeformEnemy.h"
#include "Source/Actor/ActorStatus.h"
#include "DeformEnemyIState.h"


namespace app
{
	namespace actor
	{
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


		core::IState* DeformEnemyStateMachine::GetChangeState()
		{
			return nullptr;
		}
	}
}