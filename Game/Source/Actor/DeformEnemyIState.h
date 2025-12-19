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
		 * ひっくり返る
		 */
		class FlippingState : public IState
		{
		public:
			FlippingState(StateMachineBase* owner);
			~FlippingState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * ひっくり返った
		 */
		class FlippedState : public IState
		{
		public:
			FlippedState(StateMachineBase* owner);
			~FlippedState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 滑走
		 */
		class SlidingState : public IState
		{
		public:
			SlidingState(StateMachineBase* owner);
			~SlidingState();

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