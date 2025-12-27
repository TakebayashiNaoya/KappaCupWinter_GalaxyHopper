/**
 * BossEnemyIState.h
 * ボスエネミーの各ステート
 */
#pragma once
#include "StateMachineBase.h"


namespace app
{
	namespace actor
	{
		/**
		 * 止まってる
		 */
		class BossEnemyIdleState : public IState
		{
		public:
			BossEnemyIdleState(StateMachineBase* owner) : IState(owner) {};
			~BossEnemyIdleState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/

		/**
		 * 歩く
		 */
		class BossEnemyWalkState : public IState
		{
		public:
			BossEnemyWalkState(StateMachineBase* owner) : IState(owner) {};
			~BossEnemyWalkState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 走る
		 */
		class BossEnemyDashState : public IState
		{
		public:
			BossEnemyDashState(StateMachineBase* owner) : IState(owner) {};
			~BossEnemyDashState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 攻撃
		 */
		class BossEnemyAttackState : public IState
		{
		public:
			BossEnemyAttackState(StateMachineBase* owner) : IState(owner) {};
			~BossEnemyAttackState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * クールダウン
		 */
		class BossEnemyCoolDownState : public IState
		{
		public:
			BossEnemyCoolDownState(StateMachineBase* owner) : IState(owner) {};
			~BossEnemyCoolDownState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * ダメージを受ける
		 */
		class BossEnemyDamageState : public IState
		{
		public:
			BossEnemyDamageState(StateMachineBase* owner) : IState(owner) {};
			~BossEnemyDamageState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 死んでいる最中
		 */
		class BossEnemyDyingState : public IState
		{
		public:
			BossEnemyDyingState(StateMachineBase* owner) : IState(owner) {};
			~BossEnemyDyingState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};




		/********************************/


		/**
		 * 死亡
		 */
		class BossEnemyDeadState : public IState
		{
		public:
			BossEnemyDeadState(StateMachineBase* owner) : IState(owner) {};
			~BossEnemyDeadState() {};

			void Enter() override;
			void Update() override;
			void Exit() override;
		};
	}
}