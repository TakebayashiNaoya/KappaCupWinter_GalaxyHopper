/**
 * BasicEnemyIState.h
 * ベーシックエネミーの各ステート
 */
#pragma once
#include "Source/Actor/StateMachineBase.h"


namespace app
{
	namespace actor
	{
		/**
		 * 待機
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
		 * クールダウン
		 */
		class BasicEnemyCooldownState : public IState
		{
		public:
			BasicEnemyCooldownState(StateMachineBase* owner) : IState(owner) {};
			~BasicEnemyCooldownState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 死亡
		 */
		class BasicEnemyDieState : public IState
		{
		public:
			BasicEnemyDieState(StateMachineBase* owner) : IState(owner) {};
			~BasicEnemyDieState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};
	}
}