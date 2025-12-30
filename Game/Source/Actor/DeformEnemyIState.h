/**
 * DeformEnemyIState.h
 * デフォームエネミーの各ステート
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
		class DeformEnemyIdleState : public IState
		{
		public:
			DeformEnemyIdleState(StateMachineBase* owner) : IState(owner) {};
			~DeformEnemyIdleState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 走る
		 */
		class DeformEnemyDashState : public IState
		{
		public:
			DeformEnemyDashState(StateMachineBase* owner) : IState(owner) {};
			~DeformEnemyDashState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * ひっくり返る
		 */
		class DeformEnemyFlippingState : public IState
		{
		public:
			DeformEnemyFlippingState(StateMachineBase* owner) : IState(owner) {};
			~DeformEnemyFlippingState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * ひっくり返った
		 */
		class DeformEnemyFlippedState : public IState
		{
		public:
			DeformEnemyFlippedState(StateMachineBase* owner) : IState(owner) {};
			~DeformEnemyFlippedState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 滑走
		 */
		class DeformEnemySlidingState : public IState
		{
		public:
			DeformEnemySlidingState(StateMachineBase* owner) : IState(owner) {};
			~DeformEnemySlidingState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 死亡
		 */
		class DeformEnemyDeadState : public IState
		{
		public:
			DeformEnemyDeadState(StateMachineBase* owner) : IState(owner) {};
			~DeformEnemyDeadState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};
	}
}