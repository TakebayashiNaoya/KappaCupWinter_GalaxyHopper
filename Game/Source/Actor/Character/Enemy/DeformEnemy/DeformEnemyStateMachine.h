/**
 * DeformEnemyStateMachine.h
 * 変形エネミーの状態遷移を管理するクラス群
 */
#pragma once
#include "Source/Actor/Character/CharacterStateMachine.h"


namespace app
{
	namespace actor
	{
		/** 前方宣言 */
		class DeformEnemy;
		class DeformEnemyStatus;


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
	}
}