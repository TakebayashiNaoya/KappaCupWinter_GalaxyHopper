/**
 * Enemy.h
 * エネミーの基底クラス
 */
#pragma once
#include "Source/Actor/Character/Character.h"


namespace app
{
	namespace actor
	{
		class Enemy : public Character
		{
		public:
			/**
			 * 削除すべきかを取得
			 * バトルマネージャーがこれを見てDeleteGOする
			 */
			const bool ShouldDestroy() const { return m_shouldDestroy; }
			/**
			 * 削除すべきかを設定
			 * ステートで削除が決まったらこれをtrueにする
			 */
			void SetShouldDestroy(const bool shouldDestroy) { m_shouldDestroy = shouldDestroy; }


		public:
			Enemy();
			virtual ~Enemy();


		private:
			/** 削除すべきか */
			bool m_shouldDestroy = false;
		};
	}
}