/**
 * Player.h
 * プレイヤーを管理するクラス
 */
#pragma once
#include "Character.h"
#include "ActorStatus.h" 
#include "PlayerStateMachine.h"

namespace app
{
	namespace actor
	{
		class Player : public Character
		{
		public:
			/**
			 * アニメーションクリップ
			 * 初期化時とIStateでアニメ再生に使用するのでpublicにしています。
			 */
			enum EnAnimationClip : uint8_t
			{
				enAnimationClip_Idle,		/** 待機		*/
				enAnimationClip_Walk,		/** 歩き		*/
				enAnimationClip_Dash,		/** 走り		*/
				enAnimationClip_Jump,		/** ジャンプ	*/
				enAnimationClip_Damage,		/** 被弾		*/
				enAnimationClip_Die,		/** 死亡		*/
				enAnimationClip_Num,
			};


			/** プレイヤーステートマシンのゲッター */
			PlayerStateMachine* GetStateMachine() const { return m_stateMachine.get(); }


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
			// ★削除: 入力処理（ComputeMoveDirection）はControllerに移譲したため不要

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
			/** ステータス */
			std::unique_ptr<PlayerStatus> m_status;

			// ステートマシン
			std::unique_ptr<PlayerStateMachine> m_stateMachine;

			// ダメージ関連
			Vector3 m_knockBackDirection = Vector3::Zero;
			float	m_knockBackTimer = 0.0f;
			bool	m_isBlinking = false;
			bool	m_isInvincible = false;
			float   m_invincibleTimer = 0.0f;

			// アニメーション設定
			static const AnimationOption PLAYER_ANIMATION_OPTIONS[enAnimationClip_Num];
		};
	}
}