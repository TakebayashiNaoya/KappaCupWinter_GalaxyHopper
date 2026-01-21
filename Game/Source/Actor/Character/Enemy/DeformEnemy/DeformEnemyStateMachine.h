/**
 * DeformEnemyStateMachine.h
 * 変形エネミーの状態遷移を管理するクラス群
 */
#pragma once
#include "Source/Actor/ActorStatus.h"
#include "Source/Actor/Character/CharacterStateMachine.h"
#include "Source/Actor/Character/Enemy/DeformEnemy/DeformEnemy.h"


namespace app
{
	namespace actor
	{
		/**
		 * 変形エネミーのステートマシン
		 */
		class DeformEnemyStateMachine : public CharacterStateMachine
		{
			/**
			 * IState用の関数群
			 * NOTE: 共変戻り値のため、前方宣言ではなくインクルードが必要
			 */
		public:
			/**
			 * オーナーを取得
			 */
			DeformEnemy* GetOwner() const override final;
			/**
			 * オーナーのステータスを取得
			 */
			DeformEnemyStatus* GetStatus() const override final;


		public:
			DeformEnemyStateMachine(DeformEnemy* owner);
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
		};
	}
}