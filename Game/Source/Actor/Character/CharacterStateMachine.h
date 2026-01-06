/**
 * CharacterStateMachine.h
 * キャラクター用のステートマシン
 */
#pragma once
#include "Source/Actor/ActorStateMachine.h"


namespace app
{
	namespace actor
	{
		/** 前方宣言 */
		class Character;
		class CharacterStatus;


		/**
		 * キャラクター用ステートマシン
		 */
		class CharacterStateMachine : public ActorStateMachine
		{
		public:
			/**
			 * 移動方向を取得
			 */
			inline const Vector3& GetMoveDirection() const { return m_moveDirection; }
			/**
			 * 移動方向を設定
			 */
			inline void SetMoveDirection(const Vector3 moveDir) { m_moveDirection = moveDir; }

			/**
			 * 移動速度を取得
			 */
			inline float GetMoveSpeed() const { return m_moveSpeed; }
			/**
			 * 移動速度を設定
			 */
			inline void SetMoveSpeed(const float moveSpeed) { m_moveSpeed = moveSpeed; }

			/**
			 * ジャンプ初速を取得
			 */
			inline float GetInitialJumpSpeed() const { return m_initialJumpSpeed; }
			/**
			 * ジャンプ初速を設定
			 */
			inline void SetInitialJumpSpeed(const float initialJumpSpeed) { m_initialJumpSpeed = initialJumpSpeed; }

			/**
			 * ダッシュできるかを取得
			 */
			inline bool IsDash() const { return m_isDash; }
			/**
			 * ダッシュできるかを設定
			 */
			inline void SetIsDash(const bool isDash) { m_isDash = isDash; }

			/**
			 * 攻撃中かを取得
			 */
			inline bool IsAttack() const { return m_isAttack; }
			/**
			 * 攻撃中かを設定
			 */
			inline void SetIsAttack(const bool isAttack) { m_isAttack = isAttack; }


		public:
			/** 地面に接地しているか */
			bool IsOnGround();

			/** 移動処理 */
			void ProcessMovement();


		public:
			/** 派生先のステートマシンが生成されたとき、その持ち主と持ち主のステータスをキャッシュする */
			CharacterStateMachine(Character* character, CharacterStatus* status);
			virtual ~CharacterStateMachine();


		protected:
			/** 歩き状態に変更できるか */
			bool CanChangeWalk() const;
			/** ダッシュ状態に変更できるか */
			bool CanChangeDush() const;
			/** ダメージ状態に変更できるか */
			bool CanChangeDamage();
			/** 死亡開始状態に変更できるか */
			bool CanChangeDying();
			/** 完全死亡状態に変更できるか */
			bool CanChangeDead();

			/**
			 * ダメージ状態が終了したか
			 * ダメージ状態の終了条件はキャラクターによって異なるため、派生先で実装する
			 */
			virtual bool IsDamageStateFinished() { return false; }


		protected:
			/** 持ち主となるキャラクター */
			Character* m_ownerChara = nullptr;
			/** キャラクターのステータス */
			CharacterStatus* m_charaStatus = nullptr;

			/** 移動方向 */
			Vector3 m_moveDirection = Vector3::Zero;
			/** 移動速度 */
			float m_moveSpeed = 0.0f;
			/** ジャンプ初速 */
			float m_initialJumpSpeed = 0.0f;
			/** 落下タイマー */
			float m_fallTimer = 0.0f;
			/** 現在のHP */
			int m_currentHp = 0;
			/** ダッシュできるか */
			bool m_isDash = false;
			/** 攻撃中か */
			bool m_isAttack = false;
		};
	}
}