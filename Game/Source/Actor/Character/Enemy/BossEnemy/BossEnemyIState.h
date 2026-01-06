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
		/** 前方宣言 */
		class BossEnemyStateMachine;
		class BossEnemy;
		class BossEnemyStatus;


		/**
		 * ボスエネミー専用のステート基底クラス
		 */
		class BossEnemyStateBase : public core::IState
		{
		protected:
			/** キャッシュ用ポインタ */
			BossEnemyStateMachine* m_stateMachine = nullptr;
			BossEnemy* m_bossEnemy = nullptr;
			BossEnemyStatus* m_status = nullptr;


		public:
			/** コンストラクタでステートマシン、ボスエネミー、ステータスを受け取る */
			BossEnemyStateBase(BossEnemyStateMachine* machine, BossEnemy* bossEnemy, BossEnemyStatus* status);
			virtual ~BossEnemyStateBase() {}
		};




		/********************************/


		/**
		 * 待機
		 */
		class BossEnemyIdleState : public BossEnemyStateBase
		{
		public:
			BossEnemyIdleState(BossEnemyStateMachine* machine, BossEnemy* bossEnemy, BossEnemyStatus* status)
				: BossEnemyStateBase(machine, bossEnemy, status) {
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
		class BossEnemyWalkState : public BossEnemyStateBase
		{
		public:
			BossEnemyWalkState(BossEnemyStateMachine* machine, BossEnemy* bossEnemy, BossEnemyStatus* status)
				: BossEnemyStateBase(machine, bossEnemy, status) {
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
		class BossEnemyDashState : public BossEnemyStateBase
		{
		public:
			BossEnemyDashState(BossEnemyStateMachine* machine, BossEnemy* bossEnemy, BossEnemyStatus* status)
				: BossEnemyStateBase(machine, bossEnemy, status) {
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
		class BossEnemyAttackState : public BossEnemyStateBase
		{
		public:
			BossEnemyAttackState(BossEnemyStateMachine* machine, BossEnemy* bossEnemy, BossEnemyStatus* status)
				: BossEnemyStateBase(machine, bossEnemy, status) {
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
		class BossEnemyCooldownState : public BossEnemyStateBase
		{
		public:
			BossEnemyCooldownState(BossEnemyStateMachine* machine, BossEnemy* bossEnemy, BossEnemyStatus* status)
				: BossEnemyStateBase(machine, bossEnemy, status) {
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
		class BossEnemyDamageState : public BossEnemyStateBase
		{
		public:
			BossEnemyDamageState(BossEnemyStateMachine* machine, BossEnemy* bossEnemy, BossEnemyStatus* status)
				: BossEnemyStateBase(machine, bossEnemy, status) {
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
		class BossEnemyDyingState : public BossEnemyStateBase
		{
		public:
			BossEnemyDyingState(BossEnemyStateMachine* machine, BossEnemy* bossEnemy, BossEnemyStatus* status)
				: BossEnemyStateBase(machine, bossEnemy, status) {
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
		class BossEnemyDeadState : public BossEnemyStateBase
		{
		public:
			BossEnemyDeadState(BossEnemyStateMachine* machine, BossEnemy* bossEnemy, BossEnemyStatus* status)
				: BossEnemyStateBase(machine, bossEnemy, status) {
			};
			~BossEnemyDeadState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};
	}
}