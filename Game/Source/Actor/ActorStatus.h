/**
 * ActorStatus.h
 * ステータス関連をまとめるファイル
 */
#pragma once
#include <cstdint>


namespace app
{
	namespace actor
	{
		/**
		 * アクターステータス
		 */
		class ActorStatus
		{
		public:
			ActorStatus() {}
			~ActorStatus() {}

			/** ステータスのセットアップを必ず作ってください */
			virtual void Setup() = 0;
		};




		/**********************/


		/**
		 * キャラクターステータス
		 */
		class CharacterStatus : public ActorStatus
		{
		public:
			/** 現在のHPの取得 */
			inline const int GetHp() const { return m_hp; }
			/** 最大HPの取得*/
			inline const int GetMaxHp() const { return m_maxHp; }
			/** スピードの取得*/
			inline const float GetWalkSpeed() const { return m_walkSpeed; }
			/** 半径の取得*/
			inline const float GetHurtRadius() const { return m_hurtRadius; }
			/** モデルの拡大率の取得*/
			inline const float GetModelScale() const { return m_modelScale; }
			/** コライダーのオフセット値の取得*/
			inline const float GetColliderOffset() const { return m_colliderOffset; }


		public:
			CharacterStatus() {}
			~CharacterStatus() {}

			/** 初期設定 */
			virtual void Setup() override {}

			/** ダメージを与える */
			void TakeDamage()
			{
				m_hp--;
			}


		protected:
			/** 現在のHP */
			int m_hp = 0;
			/** 最大HP */
			int m_maxHp = 0;
			/** 歩く移動速度 */
			float m_walkSpeed = 0.0f;
			/** ダメージを受ける当たり判定の半径 */
			float m_hurtRadius = 0.0f;
			/** モデルの拡大率 */
			float m_modelScale = 0.0f;
			/** コライダーのオフセット値 */
			float m_colliderOffset = 0.0f;
		};




		/**********************/


		/**
		 * プレイヤーステータス
		 */
		class PlayerStatus : public CharacterStatus
		{
		public:
			/** ダッシュスピードの取得*/
			inline const float GetDashSpeed() const { return m_dashSpeed; }
			/** ジャンプ力の取得*/
			inline const float GetJumpPower() const { return m_jumpPower; }
			/** ノックバックの衝撃力の取得*/
			inline const float GetKnockbackPower() const { return m_knockbackPower; }
			/** ノックバックの継続時間の取得*/
			inline const float GetKnockbackDuration() const { return m_knockbackDuration; }


		public:
			PlayerStatus();
			~PlayerStatus();

			/** 初期化 */
			virtual void Setup() override;


		private:
			/** 走る移動速度 */
			float m_dashSpeed = 0.0f;
			/** ジャンプ力 */
			float m_jumpPower = 0.0f;
			/** ノックバックの衝撃力 */
			float m_knockbackPower = 0.0f;
			/** ノックバックの継続時間 */
			float m_knockbackDuration = 1.0f;
		};




		/***********************/


		/**
		 * 敵のステータス
		 */
		class EnemyStatus : public CharacterStatus
		{
		public:
			/** ダメージを与える当たり判定の半径の取得*/
			inline const float GetHitRadius() const { return m_hitRadius; }
			/** ターゲットの索敵距離の取得 */
			inline const float GetSearchRange() const { return m_searchRange; }



		public:
			EnemyStatus() {}
			~EnemyStatus() {}

			virtual void Setup() override {}


		protected:
			/** ダメージを与える当たり判定の半径 */
			float m_hitRadius = 0.0f;
			/** ターゲットの索敵距離 */
			float m_searchRange = 0.0f;
		};




		/**********************/


		/**
		 * 基本エネミーのステータス
		 */
		class BasicEnemyStatus : public EnemyStatus
		{
		public:
			BasicEnemyStatus();
			~BasicEnemyStatus();

			/** 初期化 */
			virtual void Setup() override;
		};




		/**********************/


		class DeformEnemyStatus : public BasicEnemyStatus
		{

		public:
			/** 滑走スピードの取得*/
			inline const float GetSlideSpeed() const { return m_slideSpeed; }


		public:
			DeformEnemyStatus();
			~DeformEnemyStatus();

			/** 初期化 */
			virtual void Setup() override;


		private:
			/** 滑走スピード */
			float m_slideSpeed = 0.0f;
		};




		/**********************/


		/**
		 * ボスエネミーのステータス
		 */
		class BossEnemyStatus : public EnemyStatus
		{
		public:
			/** ダッシュスピードの取得*/
			inline const float GetDashSpeed() const { return m_dashSpeed; }


		public:
			BossEnemyStatus();
			~BossEnemyStatus();

			/** 初期化 */
			virtual void Setup() override;


		private:
			/** 走る移動速度 */
			float m_dashSpeed = 0.0f;
		};
	}
}