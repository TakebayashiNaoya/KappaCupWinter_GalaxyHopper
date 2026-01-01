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
			PlayerStateMachine(Player* owner);
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

			/** プレイヤーのアニメーション再生処理を実装 */
			void ExecutePlayAnimation(const uint8_t animIndex) override final;
		};
	}
}