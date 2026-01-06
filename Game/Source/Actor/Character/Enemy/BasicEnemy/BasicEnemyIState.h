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
		class BasicEnemy;
		class BasicEnemyStatus;


		/**
		 * ベーシックエネミー専用のステート基底クラス
		 */
		class BasicEnemyStateBase : public core::IState
		{
		protected:
			/** キャッシュ用ポインタ */
			BasicEnemyStateMachine* m_stateMachine = nullptr;
			BasicEnemy* m_enemy = nullptr;
			BasicEnemyStatus* m_status = nullptr;


		public:
			/** コンストラクタでステートマシン、エネミー、ステータスを受け取る */
			BasicEnemyStateBase(BasicEnemyStateMachine* machine, BasicEnemy* enemy, BasicEnemyStatus* status);
			virtual ~BasicEnemyStateBase() {}
		};




		/********************************/


		/**
		 * 待機
		 */
		class BasicEnemyIdleState : public BasicEnemyStateBase
		{
		public:
			BasicEnemyIdleState(BasicEnemyStateMachine* machine, BasicEnemy* enemy, BasicEnemyStatus* status)
				: BasicEnemyStateBase(machine, enemy, status) {
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
		class BasicEnemyDashState : public BasicEnemyStateBase
		{
		public:
			BasicEnemyDashState(BasicEnemyStateMachine* machine, BasicEnemy* enemy, BasicEnemyStatus* status)
				: BasicEnemyStateBase(machine, enemy, status) {
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
		class BasicEnemyCooldownState : public BasicEnemyStateBase
		{
		public:
			BasicEnemyCooldownState(BasicEnemyStateMachine* machine, BasicEnemy* enemy, BasicEnemyStatus* status)
				: BasicEnemyStateBase(machine, enemy, status) {
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
		class BasicEnemyDieState : public BasicEnemyStateBase
		{
		public:
			BasicEnemyDieState(BasicEnemyStateMachine* machine, BasicEnemy* enemy, BasicEnemyStatus* status)
				: BasicEnemyStateBase(machine, enemy, status) {
			};
			~BasicEnemyDieState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};
	}
}