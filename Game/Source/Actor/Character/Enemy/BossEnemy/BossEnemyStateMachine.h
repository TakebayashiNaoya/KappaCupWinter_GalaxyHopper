/**
 * BossEnemyStateMachine.h
 * ボスエネミーの状態遷移を管理するクラス群
 */
#pragma once
#include "Source/Actor/Character/CharacterStateMachine.h"


namespace app
{
	namespace actor
	{
		/** 前方宣言 */
		class BossEnemy;
		class BossEnemyStatus;


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