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
		public:
			/** 持ち主のアクターを指定した型にキャストして取得 */
			Player* GetPlayer() const
			{
				return dynamic_cast<Player*>(m_ownerActor);
			}

			/** 持ち主のアクターを指定した型にキャストして取得 */
			PlayerStatus* GetPlayerStatus() const
			{
				return dynamic_cast<PlayerStatus*>(GetPlayer()->GetStatus<PlayerStatus>());
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
			/** ステートを追加するテンプレート関数 */
			template <typename TState>
			void AddState(EnPlayerState stateId)
			{
				StateMachineBase::AddState<TState>(stateId);
			}
		};
	}
}