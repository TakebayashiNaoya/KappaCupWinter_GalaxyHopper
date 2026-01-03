/**
 * EnemyStateMachine.h
 * エネミーの状態遷移を管理するクラス群
 */
#pragma once
#include "Source/Actor/Character/CharacterStateMachine.h"


namespace app
{
	namespace actor
	{
		/** 前方宣言 */
		class BasicEnemy;
		class BasicEnemyStatus;
		class DeformEnemy;
		class DeformEnemyStatus;
		class BossEnemy;
		class BossEnemyStatus;


		/**
		 * 基本エネミーのステートマシン
		 */
		class BasicEnemyStateMachine : public CharacterStateMachine
		{
		public:
			BasicEnemyStateMachine(BasicEnemy* owner, BasicEnemyStatus* status);
			virtual ~BasicEnemyStateMachine();


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
			core::IState* GetChangeState() override final;


		private:
			/** ステートを追加するテンプレート関数 */
			template <typename TState>
			void AddState(EnBasicEnemyState stateId)
			{
				StateMachineBase::AddState<TState>(stateId, this, m_basicEnemy, m_basicEnemyStatus);
			}


		private:
			/** キャッシュ用ポインタ */
			BasicEnemy* m_basicEnemy = nullptr;
			BasicEnemyStatus* m_basicEnemyStatus = nullptr;
		};




		/********************************/


		/**
		 * 変形エネミーのステートマシン
		 */
		class DeformEnemyStateMachine : public CharacterStateMachine
		{
		public:
			DeformEnemyStateMachine(DeformEnemy* owner, DeformEnemyStatus* status);
			virtual ~DeformEnemyStateMachine();


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
			core::IState* GetChangeState() override final;


		private:
			/** ステートを追加するテンプレート関数 */
			template <typename TState>
			void AddState(EnDeformEnemyState stateId)
			{
				StateMachineBase::AddState<TState>(stateId, this, m_deformEnemy, m_deformEnemyStatus);
			}


		private:
			/** キャッシュ用ポインタ */
			DeformEnemy* m_deformEnemy = nullptr;
			DeformEnemyStatus* m_deformEnemyStatus = nullptr;
		};




		/********************************/


		/**
		 * ボスエネミーのステートマシン
		 */
		class BossEnemyStateMachine : public CharacterStateMachine
		{
		public:
			BossEnemyStateMachine(BossEnemy* owner, BossEnemyStatus* status);
			virtual ~BossEnemyStateMachine();


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
			core::IState* GetChangeState() override final;


		private:
			/** ステートを追加するテンプレート関数 */
			template <typename TState>
			void AddState(EnBossEnemyState stateId)
			{
				StateMachineBase::AddState<TState>(stateId, this, m_bossEnemy, m_bossEnemyStatus);
			}


		private:
			/** キャッシュ用ポインタ */
			BossEnemy* m_bossEnemy = nullptr;
			BossEnemyStatus* m_bossEnemyStatus = nullptr;
		};
	}
}