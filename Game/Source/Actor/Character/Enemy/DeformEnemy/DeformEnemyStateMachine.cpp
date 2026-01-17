/**
 * DeformEnemyStateMachine.cpp
 * 変形エネミーのステートマシンの実装
 */
#include "stdafx.h"
#include "DeformEnemy.h"
#include "DeformEnemyIState.h"
#include "DeformEnemyStateMachine.h"
#include "Source/Actor/ActorStatus.h"


namespace app
{
	namespace actor
	{
		DeformEnemy* DeformEnemyStateMachine::GetOwner() const
		{
			return static_cast<DeformEnemy*>(m_ownerActor);
		}


		DeformEnemyStatus* DeformEnemyStateMachine::GetStatus() const
		{
			return GetOwner()->GetStatus<DeformEnemyStatus>();
		}


		DeformEnemyStateMachine::DeformEnemyStateMachine(DeformEnemy* owner)
			: CharacterStateMachine(owner)
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