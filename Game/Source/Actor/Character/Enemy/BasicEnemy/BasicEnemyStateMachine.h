/**
 * BasicEnemyStateMachine.h
 * 基本エネミーの状態遷移を管理するクラス群
 */
#pragma once
#include "Source/Actor/ActorStatus.h"
#include "Source/Actor/Character/CharacterStateMachine.h"
#include "Source/Actor/Character/Enemy/BasicEnemy/BasicEnemy.h"


namespace app
{
	namespace actor
	{
		/**
		 * 基本エネミーのステートマシン
		 */
		class BasicEnemyStateMachine : public CharacterStateMachine
		{
			/**
			 * IState用の関数群
			 * ※共変戻り値のため、前方宣言ではなくインクルードが必要
			 */
		public:
			/**
			 * オーナーを取得
			 */
			BasicEnemy* GetOwner() const override final;
			/**
			 * オーナーのステータスを取得
			 */
			BasicEnemyStatus* GetStatus() const override final;


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