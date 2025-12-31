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
		/**
		 * 基本エネミーのステートマシン
		 */
		class BasicEnemyStateMachine : public StateMachineBase
		{
		public:
			enum EnBasicEnemyState
			{
				enBasicEnemyState_Idle,
				enBasicEnemyState_Run,
				enBasicEnemyState_Dead
			};


		public:
			BasicEnemyStateMachine(IGameObject* owner) : StateMachineBase(owner) {};
			virtual ~BasicEnemyStateMachine();
		};




		/********************************/


		/**
		 * 変形エネミーのステートマシン
		 */
		class DeformEnemyStateMachine : public StateMachineBase
		{
		public:
			enum EnDeformEnemyState
			{
				enDeformEnemyState_Idle,
				enDeformEnemyState_Transform,
				enDeformEnemyState_Run,
				enDeformEnemyState_Dead
			};


		public:
			DeformEnemyStateMachine(IGameObject* owner) : StateMachineBase(owner) {};
			virtual ~DeformEnemyStateMachine();
		};




		/********************************/


		/**
		 * ボスエネミーのステートマシン
		 */
		class BossEnemyStateMachine : public StateMachineBase
		{
		public:
			enum EnBossEnemyState
			{
				enBossEnemyState_Idle,
				enBossEnemyState_Chase,
				enBossEnemyState_Attack,
				enBossEnemyState_Damage,
				enBossEnemyState_Dead
			};


		public:
			BossEnemyStateMachine(IGameObject* owner) : StateMachineBase(owner) {};
			virtual ~BossEnemyStateMachine();
		};
	}
}