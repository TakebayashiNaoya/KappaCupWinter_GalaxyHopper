/**
 * BossEnemyIState.h
 * ボスエネミーの各ステート
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
		 * 歩く
		 */
		class WalkState : public IState
		{
		public:
			WalkState(StateMachineBase* owner);
			~WalkState();

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
		 * 攻撃
		 */
		class AttackState : public IState
		{
		public:
			AttackState(StateMachineBase* owner);
			~AttackState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * クールダウン
		 */
		class CoolDownState : public IState
		{
		public:
			CoolDownState(StateMachineBase* owner);
			~CoolDownState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * ダメージを受ける
		 */
		class DamageState : public IState
		{
		public:
			DamageState(StateMachineBase* owner);
			~DamageState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 死んでいる最中
		 */
		class DyingState : public IState
		{
		public:
			DyingState(StateMachineBase* owner);
			~DyingState();

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