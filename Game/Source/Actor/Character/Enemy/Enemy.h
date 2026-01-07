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
		class Player;


		class Enemy : public Character
		{
		public:
			/**
			 * 削除すべきかを取得
			 * バトルマネージャーがこれを見てDeleteGOする
			 */
			inline const bool ShouldDestroy() const { return m_shouldDestroy; }
			/**
			 * 削除すべきかを設定
			 * ステートで削除が決まったらこれをtrueにする
			 */
			inline void SetShouldDestroy(const bool shouldDestroy) { m_shouldDestroy = shouldDestroy; }
			/**
			 * ターゲットのプレイヤーを設定
			 */
			inline void SetTargetPlayer(Player* player) { m_targetPlayer = player; }


		public:
			Enemy();
			virtual ~Enemy();


		protected:
			bool Start() override { return true; };
			void Update() override {};
			void Render(RenderContext& rc) override {};


		protected:
			/** 削除すべきか */
			bool m_shouldDestroy = false;
			/** プレイヤーの座標 */
			Player* m_targetPlayer = nullptr;
		};
	}
}