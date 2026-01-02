/**
 * CharacterStateMachine.h
 * キャラクター用の物理・ステータス機能付きステートマシン
 */
#pragma once
#include "Source/Actor/StateMachineBase.h"


namespace app
{
	namespace actor
	{
		/** 前方宣言 */
		class Character;
		class CharacterStatus;


		/**
		 * キャラクター用の基底ステートマシン
		 */
		class CharacterStateMachine : public StateMachineBase
		{
		public:
			/**
			 * トランスフォームを取得
			 */
			inline Transform& GetTransform() { return m_transform; }
			/**
			 * 座標を設定
			 */
			inline void SetPosition(const Vector3& position) { m_transform.m_position = position; }
			/**
			 * 回転を設定
			 */
			inline void SetRotation(const Quaternion& rotation) { m_transform.m_rotation = rotation; }
			/**
			 * 拡縮を設定
			 */
			inline void SetScale(const Vector3& scale) { m_transform.m_scale = scale; }

			/**
			 * 上方向ベクトルの取得
			 */
			inline const Vector3& GetUpDirection() const { return m_upDirection; }
			/**
			 * 上方向ベクトルの設定
			 */
			inline void SetUpDirection(const Vector3& upDir) { m_upDirection = upDir; }

			/**
			 * 移動方向の取得
			 */
			inline const Vector3& GetMoveDirection() const { return m_moveDirection; }
			/**
			 * 移動方向の設定
			 */
			inline void SetMoveDirection(const Vector3 moveDir) { m_moveDirection = moveDir; }

			/**
			 * 移動速度の取得
			 */
			inline float GetMoveSpeed() const { return m_moveSpeed; }
			/**
			 * 移動速度の設定
			 */
			inline void SetMoveSpeed(const float moveSpeed) { m_moveSpeed = moveSpeed; }

			/**
			 * 初速ジャンプ速度の取得
			 */
			inline float GetInitialJumpSpeed() const { return m_initialJumpSpeed; }
			/**
			 * 初速ジャンプ速度の設定
			 */
			inline void SetInitialJumpSpeed(const float initialJumpSpeed) { m_initialJumpSpeed = initialJumpSpeed; }

			/**
			 * ダッシュできるかの取得
			 */
			inline bool IsDash() const { return m_isDash; }
			/**
			 * ダッシュできるかの設定
			 */
			inline void SetIsDash(const bool isDash) { m_isDash = isDash; }

			/**
			 * 攻撃できるかの取得
			 */
			inline bool IsAttack() const { return m_isAttack; }
			/**
			 * 攻撃できるかの設定
			 */
			inline void SetIsAttack(const bool isAttack) { m_isAttack = isAttack; }


		public:
			CharacterStateMachine(Character* owner, CharacterStatus* status);
			virtual ~CharacterStateMachine();


		protected:
			/** 歩く状態に変更できるか */
			bool CanChangeWalk() const;
			/** 走る状態に変更できるか */
			bool CanChangeDush() const;
			/** ダメージ状態に変更できるか */
			bool CanChangeDamage();
			/** 死に始める状態に変更できるか */
			bool CanChangeDying();
			/** 完全に死んだ状態に変更できるか */
			bool CanChangeDead();


		public:
			/** 地面に接地しているか */
			bool IsOnGround();

			/**
			 * 移動処理
			 * ※呼び出す前に必ずm_upDirection、m_moveDirection、m_moveSpeedを設定すること
			 * なお、m_initialJumpSpeedを設定したら、ジャンプ処理も行われます。
			 */
			void ProcessMovement();


		protected:
			/** キャラクター */
			Character* m_character = nullptr;
			/** キャラクターのステータス */
			CharacterStatus* m_status = nullptr;

			/** トランスフォーム */
			Transform m_transform;
			/** 上方向ベクトル */
			Vector3 m_upDirection = Vector3::Up;
			/** 移動方向 */
			Vector3 m_moveDirection = Vector3::Zero;
			/** 移動速度 */
			float m_moveSpeed = 0.0f;
			/** 初速ジャンプ速度 */
			float m_initialJumpSpeed = 0.0f;
			/** 落下している時間 */
			float m_fallTimer = 0.0f;
			/** ダッシュできるか */
			bool m_isDash = false;
			/** 攻撃できるか */
			bool m_isAttack = false;
		};
	}
}