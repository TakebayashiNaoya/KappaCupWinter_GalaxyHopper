/**
 * DeformEnemyIState.h
 * デフォームエネミーの各ステート
 */
#pragma once
#include "Core/StateMachineBase.h"


namespace app
{
	namespace actor
	{
		/** 前方宣言 */
		class DeformEnemyStateMachine;
		class DeformEnemy;
		class DeformEnemyStatus;


		/**
		 * デフォームエネミー専用のステート基底クラス
		 */
		class DeformEnemyStateBase : public core::IState
		{
		protected:
			/** キャッシュ用ポインタ */
			DeformEnemyStateMachine* m_stateMachine = nullptr;
			DeformEnemy* m_deformEnemy = nullptr;
			DeformEnemyStatus* m_status = nullptr;


		public:
			/** コンストラクタでステートマシン、デフォームエネミー、ステータスを受け取る */
			DeformEnemyStateBase(DeformEnemyStateMachine* machine, DeformEnemy* deformEnemy, DeformEnemyStatus* status);
			virtual ~DeformEnemyStateBase() {}
		};




		/********************************/


		/**
		 * 待機
		 */
		class DeformEnemyIdleState : public DeformEnemyStateBase
		{
		public:
			DeformEnemyIdleState(DeformEnemyStateMachine* machine, DeformEnemy* deformEnemy, DeformEnemyStatus* status)
				: DeformEnemyStateBase(machine, deformEnemy, status) {
			};
			~DeformEnemyIdleState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 歩く
		 */
		class DeformEnemyWalkState : public DeformEnemyStateBase
		{
		public:
			DeformEnemyWalkState(DeformEnemyStateMachine* machine, DeformEnemy* deformEnemy, DeformEnemyStatus* status)
				: DeformEnemyStateBase(machine, deformEnemy, status) {
			};
			~DeformEnemyWalkState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * ひっくり返る（アニメーションが入る）
		 * 最初の一回踏まれたときだけ
		 */
		class DeformEnemyFlippingState : public DeformEnemyStateBase
		{
		public:
			DeformEnemyFlippingState(DeformEnemyStateMachine* machine, DeformEnemy* deformEnemy, DeformEnemyStatus* status)
				: DeformEnemyStateBase(machine, deformEnemy, status) {
			};
			~DeformEnemyFlippingState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * ひっくり返った（アニメーションが入らない）
		 */
		class DeformEnemyFlippedState : public DeformEnemyStateBase
		{
		public:
			DeformEnemyFlippedState(DeformEnemyStateMachine* machine, DeformEnemy* deformEnemy, DeformEnemyStatus* status)
				: DeformEnemyStateBase(machine, deformEnemy, status) {
			};
			~DeformEnemyFlippedState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 滑走
		 */
		class DeformEnemySlidingState : public DeformEnemyStateBase
		{
		public:
			DeformEnemySlidingState(DeformEnemyStateMachine* machine, DeformEnemy* deformEnemy, DeformEnemyStatus* status)
				: DeformEnemyStateBase(machine, deformEnemy, status) {
			};
			~DeformEnemySlidingState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 死亡
		 */
		class DeformEnemyDieState : public DeformEnemyStateBase
		{
		public:
			DeformEnemyDieState(DeformEnemyStateMachine* machine, DeformEnemy* deformEnemy, DeformEnemyStatus* status)
				: DeformEnemyStateBase(machine, deformEnemy, status) {
			};
			~DeformEnemyDieState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};
	}
}