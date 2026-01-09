/// <summary>
/// プレイヤーのステートマシン。
/// </summary>
#pragma once
#include "Source/Actor/Character/CharacterStateMachine.h"


namespace app
{
	namespace actor
	{
		/** 前方宣言 */
		class Player;


		/**
		 * プレイヤー用ステートマシン
		 */
		class PlayerStateMachine : public CharacterStateMachine
		{
			/**
			 * コリジョンマネージャーからノックバック方向を受け取るための関数群
			 */
		public:
			/**
			 * ノックバック方向を取得
			 */
			inline const Vector3& GetKnockBackDirection() const { return m_knockBackDirection; }
			/**
			 * ノックバック方向を設定
			 */
			inline void SetKnockBackDirection(const Vector3& dir) { m_knockBackDirection = dir; }



			/**
			 * IState用の関数群
			 */
		public:
			/** オーナーを取得 */
			Player* GetOwner() const override final
			{
				return static_cast<Player*>(m_ownerActor);
			}
			/** オーナーのステータスを取得 */
			PlayerStatus* GetStatus() const override final
			{
				return static_cast<PlayerStatus*>(GetOwner()->GetStatus<PlayerStatus>());
			}


		public:
			PlayerStateMachine(Player* owner);
			virtual ~PlayerStateMachine();


		private:
			/** ステートを識別するenum */
			enum EnPlayerState : uint8_t
			{
				Idle,
				Walk,
				Dash,
				Jump,
				Damage,
				Dying,
				Dead,
				Num,
			};

			/** 変更するステートを取得します。 */
			core::IState* GetChangeState()  override final;

			/** ジャンプ状態に変更できるか */
			bool CanChangeJump();

			/** ダメージ状態が終了したか */
			bool IsDamageStateFinished() override final;


		private:
			/** ノックバックする方向 */
			Vector3 m_knockBackDirection = Vector3::Zero;
		};
	}
}