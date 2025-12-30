/**
 * BasicEnemyIState.h
 * ベーシックエネミーの各ステート
 */
#pragma once
#include "StateMachineBase.h"


namespace app
{
	namespace actor
	{
		/**
		 * 止まってる
		 */
		class BasicEnemyIdleState : public IState
		{
		public:
			BasicEnemyIdleState(StateMachineBase* owner) : IState(owner) {};
			~BasicEnemyIdleState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 走る
		 */
		class BasicEnemyDashState : public IState
		{
		public:
			BasicEnemyDashState(StateMachineBase* owner) : IState(owner) {};
			~BasicEnemyDashState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 待機
		 */
		class BasicEnemyWaitState : public IState
		{
		public:
			BasicEnemyWaitState(StateMachineBase* owner) : IState(owner) {};
			~BasicEnemyWaitState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 死亡
		 */
		class BasicEnemyDeadState : public IState
		{
		public:
			BasicEnemyDeadState(StateMachineBase* owner) : IState(owner) {};
			~BasicEnemyDeadState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};
	}
}