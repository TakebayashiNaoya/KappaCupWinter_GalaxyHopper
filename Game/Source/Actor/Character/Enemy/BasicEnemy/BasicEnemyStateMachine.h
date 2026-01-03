/**
 * BasicEnemyStateMachine.h
 * 基本エネミーの状態遷移を管理するクラス群
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
	}
}