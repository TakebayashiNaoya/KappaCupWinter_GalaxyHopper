/**
 * Spawner.h
 * エネミーをリスポーンさせるスポナークラス
 */
#pragma once
#include "Source/Actor/Actor.h"


namespace app
{
	namespace actor
	{
		class DeformEnemy;


		class Spawner : public Actor
		{
		public:
			Spawner();
			~Spawner();


		private:
			virtual bool Start() override final;
			virtual void Update() override final;


		private:
			/**	リスポーンさせるエネミー */
			DeformEnemy* m_deformEnemy = nullptr;
			/**	リスポーンタイマー */
			float m_respawnTimer = 0.0f;
		};
	}
}