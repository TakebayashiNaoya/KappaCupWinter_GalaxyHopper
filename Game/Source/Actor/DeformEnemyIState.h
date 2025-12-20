/**
 * DeformEnemyIState.h
 * デフォームエネミーの各ステート
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
		class DeformEnemyIdleState : public IState
		{
		public:
			DeformEnemyIdleState(StateMachineBase* owner);
			~DeformEnemyIdleState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 走る
		 */
		class DeformEnemyDashState : public IState
		{
		public:
			DeformEnemyDashState(StateMachineBase* owner);
			~DeformEnemyDashState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * ひっくり返る
		 */
		class DeformEnemyFlippingState : public IState
		{
		public:
			DeformEnemyFlippingState(StateMachineBase* owner);
			~DeformEnemyFlippingState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * ひっくり返った
		 */
		class DeformEnemyFlippedState : public IState
		{
		public:
			DeformEnemyFlippedState(StateMachineBase* owner);
			~DeformEnemyFlippedState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 滑走
		 */
		class DeformEnemySlidingState : public IState
		{
		public:
			DeformEnemySlidingState(StateMachineBase* owner);
			~DeformEnemySlidingState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 死亡
		 */
		class DeformEnemyDeadState : public IState
		{
		public:
			DeformEnemyDeadState(StateMachineBase* owner);
			~DeformEnemyDeadState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};
	}
}