/**
 * PlayerController.h
 * プレイヤーを操作する「頭脳」クラス
 */
#pragma once


namespace app
{
	namespace actor
	{
		class Player;


		class PlayerController : public IGameObject
		{
		public:
			/**
			 * 操作対象のプレイヤーを設定
			 */
			void SetOwnerPlayer(Player* player)
			{
				m_ownerPlayer = player;
			}


		public:
			PlayerController();
			~PlayerController();


		private:
			bool Start() override final;
			void Update() override final;


		private:
			/** 操作対象のプレイヤー（肉体） */
			Player* m_ownerPlayer = nullptr;
			/** プレイヤーのステートマシン */
			PlayerStateMachine* m_stateMachine = nullptr;
			/** プレイヤーのステータス */
			PlayerStatus* m_playerStatus = nullptr;
		};
	}
}