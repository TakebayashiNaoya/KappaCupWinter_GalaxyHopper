/**
 * EnemyStateMachine.h
 * エネミーの状態遷移を管理するクラス群
 */
#pragma once
#include "Source/Actor/StateMachineBase.h"


namespace app
{
	namespace actor
	{
		class BasicEnemy;
		class DeformEnemy;
		class BossEnemy;


		/**
		 * 基本エネミーのステートマシン
		 */
		class BasicEnemyStateMachine : public StateMachineBase
		{
		public:
			BasicEnemyStateMachine(BasicEnemy* owner);
			virtual ~BasicEnemyStateMachine();

			/** アニメーション再生 */
			void PlayAnimation(const uint8_t animationIndex) override final;


		private:
			/** ステート */
			enum EnBasicEnemyState : uint8_t
			{
				enBasicEnemyState_Idle,
				enBasicEnemyState_Dash,
				enBasicEnemyState_Cooldown,
				enBasicEnemyState_Die,
				enBasicEnemyState_Num
			};

			/** 変更するステートを取得します。 */
			IState* GetChangeState() override final;
		};




		/********************************/


		/**
		 * 変形エネミーのステートマシン
		 */
		class DeformEnemyStateMachine : public StateMachineBase
		{
		public:
			DeformEnemyStateMachine(DeformEnemy* owner);
			virtual ~DeformEnemyStateMachine();

			/** アニメーション再生 */
			void PlayAnimation(const uint8_t animationIndex) override final;


		private:
			/** ステート */
			enum EnDeformEnemyState : uint8_t
			{
				enDeformEnemyState_Idle,
				enDeformEnemyState_Walk,
				enDeformEnemyState_Flipping,
				enDeformEnemyState_Flipped,
				enDeformEnemyState_Sliding,
				enDeformEnemyState_Die,
				enDeformEnemyState_Num
			};

			/** 変更するステートを取得します。 */
			IState* GetChangeState() override final;
		};




		/********************************/


		/**
		 * ボスエネミーのステートマシン
		 */
		class BossEnemyStateMachine : public StateMachineBase
		{
		public:
			BossEnemyStateMachine(BossEnemy* owner);
			virtual ~BossEnemyStateMachine();

			/** アニメーション再生 */
			void PlayAnimation(const uint8_t animationIndex) override final;


		private:
			/** ステート */
			enum EnBossEnemyState : uint8_t
			{
				enBossEnemyState_Idle,
				enBossEnemyState_Walk,
				enBossEnemyState_Dash,
				enBossEnemyState_Attack,
				enBossEnemyState_Cooldown,
				enBossEnemyState_Damage,
				enBossEnemyState_Dying,
				enBossEnemyState_Dead,
				enBossEnemyState_Num
			};

			/** 変更するステートを取得します。 */
			IState* GetChangeState() override final;
		};
	}
}