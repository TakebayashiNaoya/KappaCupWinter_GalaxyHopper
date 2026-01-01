/**
 * DeformEnemyIState.h
 * デフォームエネミーの各ステート
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
		 * 歩く
		 */
		class DeformEnemyWalkState : public IState
		{
		public:
			DeformEnemyWalkState(StateMachineBase* owner) : IState(owner) {};
			~DeformEnemyWalkState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * ひっくり返る（アニメーションが入る）
		 * 最初の一回踏まれたときだけ
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
		 * ひっくり返った（アニメーションが入らない）
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
		class DeformEnemyDieState : public IState
		{
		public:
			DeformEnemyDieState(StateMachineBase* owner) : IState(owner) {};
			~DeformEnemyDieState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};
	}
}