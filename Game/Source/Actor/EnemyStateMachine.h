/**
 * EnemyStateMachine.h
 * エネミーの状態遷移を管理するクラス群
 */
#pragma once
#include "StateMachine.h"


namespace app
{
	namespace actor
	{
		class EnemyStateMachine : public StateMachineBase
		{
		public:
			EnemyStateMachine(IGameObject* owner) : StateMachineBase(owner) {}
			virtual ~EnemyStateMachine() {}
		};




		/********************************/


		enum EnBasicEnemyState
		{
			enBasicEnemyState_Idle,
			enBasicEnemyState_Run,
			enBasicEnemyState_Dead
		};

		/**
		 * 基本エネミーのステートマシン
		 */
		class BasicEnemyStateMachine : public EnemyStateMachine
		{
		public:
			BasicEnemyStateMachine(IGameObject* owner) : EnemyStateMachine(owner) {};
			virtual ~BasicEnemyStateMachine();
		};
	}
}