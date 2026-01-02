/**
 * PlayerIState.h
 * プレイヤーの各ステート
 */
#pragma once
#include "Source/Actor/StateMachineBase.h"


namespace app
{
	namespace actor
	{
		class PlayerStateMachine;
		class Player;
		class PlayerStatus;


		/**
		 * プレイヤー専用のステート基底クラス
		 */
		class PlayerStateBase : public IState
		{
		protected:
			/** キャッシュ用ポインタ */
			PlayerStateMachine* m_stateMachine = nullptr;
			Player* m_player = nullptr;
			PlayerStatus* m_status = nullptr;


		public:
			/** コンストラクタでステートマシン、プレイヤー、ステータスを受け取る */
			PlayerStateBase(PlayerStateMachine* machine, Player* player, PlayerStatus* status);
			virtual ~PlayerStateBase() {}
		};




		/********************************/


		/**
		 * 止まってる
		 */
		class PlayerIdleState : public PlayerStateBase
		{
		public:
			PlayerIdleState(PlayerStateMachine* machine, Player* player, PlayerStatus* status)
				: PlayerStateBase(machine, player, status) {
			};
			~PlayerIdleState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 歩く
		 */
		class PlayerWalkState : public PlayerStateBase
		{
		public:
			PlayerWalkState(PlayerStateMachine* machine, Player* player, PlayerStatus* status)
				: PlayerStateBase(machine, player, status) {
			};
			~PlayerWalkState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 走る
		 */
		class PlayerDashState : public PlayerStateBase
		{
		public:
			PlayerDashState(PlayerStateMachine* machine, Player* player, PlayerStatus* status)
				: PlayerStateBase(machine, player, status) {
			};
			~PlayerDashState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * ジャンプ
		 */
		class PlayerJumpState : public PlayerStateBase
		{
		public:
			PlayerJumpState(PlayerStateMachine* machine, Player* player, PlayerStatus* status)
				: PlayerStateBase(machine, player, status) {
			};
			~PlayerJumpState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * ダメージを受ける
		 */
		class PlayerDamageState : public PlayerStateBase
		{
		public:
			PlayerDamageState(PlayerStateMachine* machine, Player* player, PlayerStatus* status)
				: PlayerStateBase(machine, player, status) {
			};
			~PlayerDamageState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 死んでいる最中
		 */
		class PlayerDyingState : public PlayerStateBase
		{
		public:
			PlayerDyingState(PlayerStateMachine* machine, Player* player, PlayerStatus* status)
				: PlayerStateBase(machine, player, status) {
			};
			~PlayerDyingState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};




		/********************************/


		/**
		 * 死亡
		 */
		class PlayerDeadState : public PlayerStateBase
		{
		public:
			PlayerDeadState(PlayerStateMachine* machine, Player* player, PlayerStatus* status)
				: PlayerStateBase(machine, player, status) {
			};
			~PlayerDeadState() {};

			void Enter() override final;
			void Update() override final;
			void Exit() override final;
		};
	}
}