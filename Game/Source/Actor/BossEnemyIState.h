/**
 * PlayerIState.h
 * プレイヤーの各ステート
 */
#pragma once
#include "StateMachine.h"

class StateMachine;


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
			IdleState(StateMachine* owner);
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
			WalkState(StateMachine* owner);
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
			DashState(StateMachine* owner);
			~DashState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * ジャンプ
		 */
		class JumpState : public IState
		{
		public:
			JumpState(StateMachine* owner);
			~JumpState();

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
			DamageState(StateMachine* owner);
			~DamageState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 死に始める
		 */
		class DieState : public IState
		{
		public:
			DieState(StateMachine* owner);
			~DieState();

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
			DeadState(StateMachine* owner);
			~DeadState();

			void Enter() override;
			void Update() override;
			void Exit() override;
		};
	}
}