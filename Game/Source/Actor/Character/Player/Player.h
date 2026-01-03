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
				Idle,	/** 待機	 */
				Walk,	/** 歩き	 */
				Dash,	/** 走り	 */
				Jump,	/** ジャンプ */
				Damage,	/** 被弾	 */
				Die,	/** 死亡	 */
				Num,
			};


		public:
			/// <summary>
			/// 毎フレームのXZ軸回転角度を取得
			/// </summary>
			const Quaternion& GetAdditionalRot() const { return m_xzAdditionalRot; }

			/// <summary>
			/// 無敵中かどうかを取得・設定
			/// </summary>
			const bool GetIsInvincible() const { return m_isInvincible; }
			void SetIsInvincible(const bool isInvincible) { m_isInvincible = isInvincible; }

			/// <summary>
			/// ノックバックタイマーをリセット
			/// </summary>
			void ResetKnockBackTimer() { m_knockBackTimer = 0.0f; }


		protected:
			Quaternion	m_xzAdditionalRot;	// 毎フレームのXZ軸回転角度


		public:
			Player();
			~Player();


		private:
			bool Start() override;
			void Update() override;
			void Render(RenderContext& rc) override;


		private:
			// ダメージ関連
			Vector3 m_knockBackDirection = Vector3::Zero;
			float	m_knockBackTimer = 0.0f;
			bool	m_isBlinking = false;
			bool	m_isInvincible = false;
			float   m_invincibleTimer = 0.0f;

			// アニメーション設定
			static const AnimationOption PLAYER_ANIMATION_OPTIONS[];
		};
	}
}