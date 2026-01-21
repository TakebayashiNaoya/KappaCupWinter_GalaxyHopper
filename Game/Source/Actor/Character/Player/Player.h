/**
 * Player.h
 * プレイヤーを管理するクラス
 */
#pragma once
#include "Source/Actor/Character/Character.h"


namespace app
{
	namespace actor
	{
		class Player : public Character
		{
		public:
			/**
			 * プレイヤーのアニメーションクリップ
			 */
			enum class EnPlayerAnimClip : uint8_t
			{
				Idle = 0,	/** 待機	 */
				Walk,		/** 歩き	 */
				Dash,		/** 走り	 */
				Jump,		/** ジャンプ */
				Damage,		/** 被弾	 */
				Die,		/** 死亡	 */
				Num,
			};


		public:
			/**
			 * 無敵かを取得
			 */
			inline const bool IsInvincible() const { return m_isInvincible; }
			/**
			 * 無敵かを設定
			 */
			inline void SetIsInvincible(const bool isInvincible) { m_isInvincible = isInvincible; }


		public:
			Player();
			~Player();


		private:
			bool Start() override;
			void Update() override;
			void Render(RenderContext& rc) override;

			/** 無敵状態の更新処理 */
			void UpdateInvincible();


		private:
			/** 無敵か */
			bool m_isInvincible = false;
			/** 無敵タイマー */
			float m_invincibleTimer = 0.0f;
			/** 描画するか（点滅演出用） */
			bool m_isVisible = true;

			/** アニメーション設定 */
			static const AnimationOption PLAYER_ANIMATION_OPTIONS[];
		};
	}
}