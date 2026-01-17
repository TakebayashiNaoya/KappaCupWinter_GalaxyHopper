/**
 * BossEnemyIState.h
 * ボスエネミーの各ステート
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
		class BossEnemyIdleState : public core::IState
		{
		public:
			BossEnemyIdleState(core::StateMachineBase* owner)
				: core::IState(owner) {
			};
			~BossEnemyIdleState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/

		/**
		 * 歩く
		 */
		class BossEnemyWalkState : public core::IState
		{
		public:
			BossEnemyWalkState(core::StateMachineBase* owner)
				: core::IState(owner) {
			};
			~BossEnemyWalkState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 走る
		 */
		class BossEnemyDashState : public core::IState
		{
		public:
			BossEnemyDashState(core::StateMachineBase* owner)
				: core::IState(owner) {
			};
			~BossEnemyDashState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 攻撃
		 */
		class BossEnemyAttackState : public core::IState
		{
		public:
			BossEnemyAttackState(core::StateMachineBase* owner)
				: core::IState(owner) {
			};
			~BossEnemyAttackState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * クールダウン
		 */
		class BossEnemyCooldownState : public core::IState
		{
		public:
			BossEnemyCooldownState(core::StateMachineBase* owner)
				: core::IState(owner) {
			};
			~BossEnemyCooldownState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * ダメージを受ける
		 */
		class BossEnemyDamageState : public core::IState
		{
		public:
			BossEnemyDamageState(core::StateMachineBase* owner)
				: core::IState(owner) {
			};
			~BossEnemyDamageState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 死んでいる最中
		 */
		class BossEnemyDyingState : public core::IState
		{
		public:
			BossEnemyDyingState(core::StateMachineBase* owner)
				: core::IState(owner) {
			};
			~BossEnemyDyingState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 死亡
		 */
		class BossEnemyDeadState : public core::IState
		{
		public:
			BossEnemyDeadState(core::StateMachineBase* owner)
				: core::IState(owner) {
			};
			~BossEnemyDeadState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};
	}
}