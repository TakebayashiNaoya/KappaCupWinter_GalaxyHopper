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