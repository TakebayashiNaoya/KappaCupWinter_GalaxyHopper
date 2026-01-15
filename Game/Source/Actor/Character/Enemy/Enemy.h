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
			 * クールダウン中かを取得
			 * EnemyControllerがこれを見てクールダウンの待機処理に入る
			 */
			inline const bool IsCooldown() const { return m_isCooldown; }
			/**
			 * クールダウン中かを設定
			 * CollisionManagerで攻撃がヒットしたらこれをtrueにする
			 */
			inline void SetIsCooldown(const bool isCooldown) { m_isCooldown = isCooldown; }


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
			/** クールダウン中か */
			bool m_isCooldown = false;
		};
	}
}