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


		/**
		 * ボスエネミーのステートマシン
		 */
		class BossEnemyStateMachine : public CharacterStateMachine
		{
			/**
			 * IState用の関数群
			 */
		public:
			/**
			 * オーナーを取得
			 */
			BossEnemy* GetOwner() const override final;
			/**
			 * オーナーのステータスを取得
			 */
			BossEnemyStatus* GetStatus() const override final;


		public:
			BossEnemyStateMachine(BossEnemy* owner);
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
		};
	}
}