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
		class PlayerStatus;


		/**
		 * プレイヤー用ステートマシン
		 */
		class PlayerStateMachine : public CharacterStateMachine
		{
		public:
			PlayerStateMachine(Player* owner, PlayerStatus* status);
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
			/** ステートを追加するテンプレート関数 */
			template <typename TState>
			void AddState(EnPlayerState stateId)
			{
				StateMachineBase::AddState<TState>(stateId, this, m_myPlayer, m_myStatus);
			}


		private:
			/**
			 * キャッシュ用のプレイヤーとステータス
			 * ※頻繁にアクセスするため、キャスト不要で高速にアクセスできるように保持しておく
			 */
			Player* m_myPlayer = nullptr;
			PlayerStatus* m_myStatus = nullptr;
		};
	}
}