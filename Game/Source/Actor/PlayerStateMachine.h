/// <summary>
/// プレイヤーのステートマシン。
/// </summary>
#pragma once
#include "StateMachine.h"


namespace app
{
	namespace actor
	{
		class Player;


		class PlayerStateMachine : public StateMachineBase
		{
		private:
			/** ステートを識別するenum */
			enum EnPlayerState
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


		private:
			/** ジャンプできるか */
			bool m_isJump = false;


		public:
			PlayerStateMachine(Player* owner);
			virtual ~PlayerStateMachine();

			/** アニメーション再生 */
			void PlayAnimation(const int animationIndex) override final;


		private:
			/** 変更するステートを取得します。 */
			IState* GetChangeState()  override final;

			/** ジャンプ状態に変更できるか */
			bool CanChangeJump();
		};
	}
}