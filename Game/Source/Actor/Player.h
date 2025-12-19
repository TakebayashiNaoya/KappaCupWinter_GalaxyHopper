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
			Player();
			~Player();


			/**
			 * アニメーションクリップ
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


			/** コントローラーから渡される移動ベクトルのセッター */
			void SetVelocity(const Vector3& velocity) { m_velocity = velocity; }

			/** プレイヤーステータスのゲッター */
			PlayerStatus* GetPlayerStatus() const { return m_status; }
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

			/// <summary>
			/// カメラの回転角度を計算
			/// </summary>
			void CalcCameraRotation();

			/// <summary>
			/// 移動更新（速度はJSONから、方向はControllerから受け取る）
			/// </summary>
			/// <param name="speed">移動速度</param>
			void MoveUpdate(const float speed);

			/// <summary>
			/// ノックバック方向を計算
			/// </summary>
			void ComputeKnockBackDirection(const Vector3& enemyPos);

			/// <summary>
			/// ノックバック処理
			/// </summary>
			void KnockedBack();

			/// <summary>
			/// 踏みつけジャンプ
			/// </summary>
			void StompJump();

			/// <summary>
			/// アニメーションイベント
			/// </summary>
			void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName) override final;

		protected:
			// ★削除: 入力処理（ComputeMoveDirection）はControllerに移譲したため不要

		protected:
			Quaternion	m_xzAdditionalRot;	// 毎フレームのXZ軸回転角度

		private:
			bool Start() override;
			void Update() override;
			void Render(RenderContext& rc) override;

			/// <summary>
			/// 無敵タイマー更新
			/// </summary>
			void InvincibleTimer();

		private:
			// ★追加: パラメータ管理クラス
			PlayerStatus* m_status = nullptr;

			// ★追加: コントローラーから渡される移動ベクトル
			Vector3 m_velocity = Vector3::Zero;

			// ステートマシン
			std::unique_ptr<PlayerStateMachine> m_stateMachine;

			// ダメージ関連
			Vector3 m_knockBackDirection = Vector3::Zero;
			float	m_knockBackTimer = 0.0f;
			bool	m_isBlinking = false;
			bool	m_isInvincible = false;
			float   m_invincibleTimer = 0.0f;

			// アニメーション設定
			static const Character::AnimationOption PLAYER_ANIMATION_OPTIONS[];
		};
	}
}