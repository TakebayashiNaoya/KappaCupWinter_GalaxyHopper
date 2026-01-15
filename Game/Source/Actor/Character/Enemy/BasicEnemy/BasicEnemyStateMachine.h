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
		/**
		 * 基本エネミーのステートマシン
		 */
		class BasicEnemyStateMachine : public CharacterStateMachine
		{
		public:
			BasicEnemyStateMachine(BasicEnemy* owner);
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
		};
	}
}