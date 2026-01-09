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
		/** 前方宣言 */
		class BasicEnemyStateMachine;


		/**
		 * 待機
		 */
		class BasicEnemyIdleState : public core::IState
		{
		public:
			BasicEnemyIdleState(BasicEnemyStateMachine* machine)
				: IState(machine) {
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
			BasicEnemyDashState(BasicEnemyStateMachine* machine)
				: IState(machine) {
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
			BasicEnemyCooldownState(BasicEnemyStateMachine* machine)
				: IState(machine) {
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
			BasicEnemyDieState(BasicEnemyStateMachine* machine)
				: IState(machine) {
			};
			~BasicEnemyDieState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};
	}
}