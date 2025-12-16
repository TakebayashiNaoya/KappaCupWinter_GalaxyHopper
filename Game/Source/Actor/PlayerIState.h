/**
 * PlayerIState.h
 * プレイヤーの各ステート
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
		class WalkState : public app::actor::IState
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
		class DashState : public app::actor::IState
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
		 * ジャンプ
		 */
		class JumpState : public app::actor::IState
		{
		public:
			JumpState(StateMachineBase* owner);
			~JumpState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * ダメージを受ける
		 */
		class DamageState : public app::actor::IState
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
		class DyingState : public app::actor::IState
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
		class DeadState : public app::actor::IState
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