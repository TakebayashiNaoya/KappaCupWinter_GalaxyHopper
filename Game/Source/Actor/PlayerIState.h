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
		class PlayerIdleState : public IState
		{
		public:
			PlayerIdleState(StateMachineBase* owner) : IState(owner) {};
			~PlayerIdleState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 歩く
		 */
		class PlayerWalkState : public app::actor::IState
		{
		public:
			PlayerWalkState(StateMachineBase* owner) : IState(owner) {};
			~PlayerWalkState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 走る
		 */
		class PlayerDashState : public app::actor::IState
		{
		public:
			PlayerDashState(StateMachineBase* owner) : IState(owner) {};
			~PlayerDashState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * ジャンプ
		 */
		class PlayerJumpState : public app::actor::IState
		{
		public:
			PlayerJumpState(StateMachineBase* owner) : IState(owner) {};
			~PlayerJumpState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * ダメージを受ける
		 */
		class PlayerDamageState : public app::actor::IState
		{
		public:
			PlayerDamageState(StateMachineBase* owner) : IState(owner) {};
			~PlayerDamageState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 死んでいる最中
		 */
		class PlayerDyingState : public app::actor::IState
		{
		public:
			PlayerDyingState(StateMachineBase* owner) : IState(owner) {};
			~PlayerDyingState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 死亡
		 */
		class PlayerDeadState : public app::actor::IState
		{
		public:
			PlayerDeadState(StateMachineBase* owner) : IState(owner) {};
			~PlayerDeadState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};
	}
}