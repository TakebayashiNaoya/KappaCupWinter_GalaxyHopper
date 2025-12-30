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
		 * ステータス生成関数
		 * ※必ずこの関数を呼んでステータスの生成をすること！
		 * 　Factoryパターンで指定したステータスを生成してセットアップまでする
		 */
		template <typename TStatus>
		static TStatus* CreateStatus()
		{
			auto* status = new TStatus();
			status->Setup();
			return status;
		}




		/**********************/


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
		protected:
			/** 現在のHP */
			uint8_t m_hp = 0;
			/** 最大HP */
			uint8_t m_maxHp = 0;
			/** 歩く移動速度 */
			float m_walkSpeed = 0.0f;
			/** 走る移動速度 */
			float m_dashSpeed = 0.0f;
			/** ダメージを受ける当たり判定の半径 */
			float m_hurtRadius = 0.0f;
			/** モデルの拡大率 */
			float m_modelScale = 0.0f;
			/** ダメージを受けたかどうか */
			bool m_isDamage = false;


		public:
			CharacterStatus() {}
			~CharacterStatus() {}

			/** 初期設定 */
			virtual void Setup() override {}

			void Update()
			{
				// ダメージフラグリセット
				m_isDamage = false;
			}

			//void Damage(uint8_t damageAmount)
			//{
			//	m_hp -= damageAmount;
			//	m_isDamage = true;
			//}
			void Damage()
			{
				m_hp--;
				m_isDamage = true;
			}


		public:
			/** 現在のHPのゲッター */
			uint8_t GetHp() const { return m_hp; }
			/** 最大HPのゲッター */
			uint8_t GetMaxHp() const { return m_maxHp; }
			/** スピードのゲッター */
			float GetWalkSpeed() const { return m_walkSpeed; }
			/** ダッシュスピードのゲッター */
			float GetDashSpeed() const { return m_dashSpeed; }
			/** 半径のゲッター */
			float GetHurtRadius() const { return m_hurtRadius; }
			/** モデルの拡大率のゲッター */
			float GetModelScale() const { return m_modelScale; }
			/** ダメージを受けたかどうかのゲッター */
			bool IsDamage() const { return m_isDamage; }
		};




		/**********************/


		/**
		 * プレイヤーステータス
		 */
		class PlayerStatus : public CharacterStatus
		{
		private:
			/** ジャンプ力 */
			float m_jumpPower = 0.0f;


		public:
			PlayerStatus();
			~PlayerStatus();

			/** 初期化 */
			virtual void Setup() override;


		public:
			/** ジャンプ力のゲッター */
			float GetJumpPower() const { return m_jumpPower; }
		};




		/***********************/


		/**
		 * 敵のステータス
		 */
		class EnemyStatus : public CharacterStatus
		{
		protected:
			/** ダメージを与える当たり判定の半径 */
			float m_hitRadius = 0.0f;


		public:
			EnemyStatus() {}
			~EnemyStatus() {}

			virtual void Setup() override {}


		public:
			/** 半径のゲッター **/
			float GetHitRadius() const { return m_hitRadius; }
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
		private:
			/** 滑走スピード */
			float m_slideSpeed = 0.0f;


		public:
			DeformEnemyStatus();
			~DeformEnemyStatus();

			/** 初期化 */
			virtual void Setup() override;


		public:
			/** 滑走スピードのゲッター */
			float GetSlideSpeed() const { return m_slideSpeed; }
		};




		/**********************/


		/**
		 * ボスエネミーのステータス
		 */
		class BossEnemyStatus : public EnemyStatus
		{
		public:
			BossEnemyStatus();
			~BossEnemyStatus();

			/** 初期化 */
			virtual void Setup() override;
		};
	}
}