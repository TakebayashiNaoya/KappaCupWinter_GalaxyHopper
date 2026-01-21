/**
 * BasicEnemyIState.h
 * ベーシックエネミーの各ステート
 */
#pragma once
#include "Core/StateMachineBase.h"


namespace app
{
	namespace actor
	{
		/**
		 * 待機
		 */
		class BasicEnemyIdleState : public core::IState
		{
		public:
			BasicEnemyIdleState(core::StateMachineBase* owner)
				: core::IState(owner) {
			};
			~BasicEnemyIdleState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 走る
		 */
		class BasicEnemyDashState : public core::IState
		{
		public:
			BasicEnemyDashState(core::StateMachineBase* owner)
				: core::IState(owner) {
			};
			~BasicEnemyDashState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * クールダウン
		 */
		class BasicEnemyCooldownState : public core::IState
		{
		public:
			BasicEnemyCooldownState(core::StateMachineBase* owner)
				: core::IState(owner) {
			};
			~BasicEnemyCooldownState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 死亡
		 */
		class BasicEnemyDieState : public core::IState
		{
		public:
			BasicEnemyDieState(core::StateMachineBase* owner)
				: core::IState(owner) {
			};
			~BasicEnemyDieState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};
	}
}