/**
 * BasicEnemyIState.h
 * ベーシックエネミーの各ステート
 */
#pragma once
#include "StateMachine.h"


namespace app
{
	namespace actor
	{
		/**
		 * 止まってる
		 */
		class IdleState : public IState
		{
		public:
			IdleState(StateMachineBase* owner);
			~IdleState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 走る
		 */
		class DashState : public IState
		{
		public:
			DashState(StateMachineBase* owner);
			~DashState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 待機
		 */
		class WaitState : public IState
		{
		public:
			WaitState(StateMachineBase* owner);
			~WaitState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 死亡
		 */
		class DeadState : public IState
		{
		public:
			DeadState(StateMachineBase* owner);
			~DeadState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};
	}
}