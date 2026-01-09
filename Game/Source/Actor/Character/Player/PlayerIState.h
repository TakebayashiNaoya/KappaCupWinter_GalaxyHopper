/**
 * PlayerIState.h
 * プレイヤーの各ステート
 */
#pragma once
#include "Core/StateMachineBase.h"


namespace app
{
	namespace actor
	{
		/** 前方宣言 */
		class PlayerStateMachine;


		/**
		 * 止まってる
		 */
		class PlayerIdleState : public core::IState
		{
		public:
			PlayerIdleState(PlayerStateMachine* owner)
				: core::IState(owner) {
			};
			~PlayerIdleState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 歩く
		 */
		class PlayerWalkState : public core::IState
		{
		public:
			PlayerWalkState(PlayerStateMachine* owner)
				: core::IState(owner) {
			};
			~PlayerWalkState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 走る
		 */
		class PlayerDashState : public core::IState
		{
		public:
			PlayerDashState(PlayerStateMachine* owner)
				: core::IState(owner) {
			};
			~PlayerDashState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * ジャンプ
		 */
		class PlayerJumpState : public core::IState
		{
		public:
			PlayerJumpState(PlayerStateMachine* owner)
				: core::IState(owner) {
			};
			~PlayerJumpState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * ダメージを受ける
		 */
		class PlayerDamageState : public core::IState
		{
		public:
			PlayerDamageState(PlayerStateMachine* owner)
				: core::IState(owner) {
			};
			~PlayerDamageState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;


		private:
			/** ダメージ状態の経過時間計測タイマー */
			float m_damageTimer = 0.0f;
		};




		/********************************/


		/**
		 * 死んでいる最中
		 */
		class PlayerDyingState : public core::IState
		{
		public:
			PlayerDyingState(PlayerStateMachine* owner)
				: core::IState(owner) {
			};
			~PlayerDyingState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 死亡
		 */
		class PlayerDeadState : public core::IState
		{
		public:
			PlayerDeadState(PlayerStateMachine* owner)
				: core::IState(owner) {
			};
			~PlayerDeadState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};
	}
}