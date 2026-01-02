/// <summary>
/// プレイヤーのステートマシン。
/// </summary>
#pragma once
#include "Source/Actor/StateMachineBase.h"


namespace app
{
	namespace actor
	{
		class Player;


		class PlayerStateMachine : public StateMachineBase
		{
		public:
			PlayerStateMachine(Player* owner, PlayerStatus* status);
			virtual ~PlayerStateMachine();


		private:
			/** ステートを識別するenum */
			enum EnPlayerState : uint8_t
			{
				enPlayerState_Idle,
				enPlayerState_Walk,
				enPlayerState_Dash,
				enPlayerState_Jump,
				enPlayerState_Damage,
				enPlayerState_Dying,
				enPlayerState_Dead,
				enPlayerState_Num,
			};

			/** 変更するステートを取得します。 */
			IState* GetChangeState()  override final;

			/** ジャンプ状態に変更できるか */
			bool CanChangeJump();


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