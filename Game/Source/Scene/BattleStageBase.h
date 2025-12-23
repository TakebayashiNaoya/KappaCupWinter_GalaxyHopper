#pragma once
#include "SceneManager.h"


class Player;
class BossEnemy;
class GameCamera;
class UIInGame;
class BattleManagerObject;
class CollisionManagerObject;
class UIResultBase;


namespace app
{
	namespace scene
	{
		/**
		 * バトルがあるステージ共通の親クラス
		 */
		class BattleStageBase : public IScene
		{
		public:
			BattleStageBase();
			virtual ~BattleStageBase();


		protected:
			/**
			 * 派生先で開始処理を実装するための仮想関数
			 */
			virtual bool Start() override;

			/**
			 * 派生先で更新処理を実装するための仮想関数
			 */
			virtual void OnUpdate() {};

			/**
			 * レベルの初期化を行う仮想関数です。
			 * 派生クラスでオーバーライドして初期化してください
			 */
			virtual void InitLevel() {};

			/**
			 * 勝敗判定に必要なため基底クラスに持たせている
			 * 各ステージで生成したPlayer、BossEnemyのポインタをセットすること
			 */
			Player* m_player = nullptr;
			BossEnemy* m_bossEnemy = nullptr;	// ※派生先でDeleteGOしてください。


			/**
			 * ゲームの進行状態を管理し、共通の勝敗判定を行います
			 */
		private:
			/**
			 * 戦闘の進行状態を表す列挙型
			 */
			enum enBattlePhase
			{
				enBattlePhase_Battle,				/** 戦闘中 */
				enBattlePhase_BattleFinish,			/** 戦闘時の処理を呼び出す */
				enBattlePhase_WaitFinishAnimation,	/** 戦闘終了アニメーションの完了待ち */
				enBattlePhase_GameOver,				/** ゲームオーバー処理 */
				enBattlePhase_GameClear,			/** ゲームクリア処理 */
				enBattlePhase_WaitEnd,				/** ゲームオーバー、またはゲームクリアUIの終了待ち */
				enBattlePhase_End
			};
			enBattlePhase m_battlePhase = enBattlePhase_Battle;

			/**
			 * 勝敗結果を表す列挙型
			 */
			enum enResult
			{
				enResult_None,
				enResult_PlayerWin,
				enResult_PlayerLose
			};
			enResult m_result = enResult_None;

			/**
			 * 全てのステージで共通する勝敗判定を行う
			 */
			void Update() override final;


			/**
			 * 全てのステージで共通するオブジェクトの初期化を行う
			 */
		private:
			/**
			 * 全てのステージで共通するオブジェクトの初期化。
			 * NOTE:ロード画面を円滑に動かすため、switchで初期化を分割している
			 */
			void InitObjects();

			/**
			 * InitObjectsで実行するタスクを登録する
			 */
			void RegisterLoadingTasks();

			/** 初期化するタスクのリスト */
			std::vector<std::function<void()>> m_loadingTasks;
			/** 現在実行中のタスク番号 */
			int m_currentTaskIndex = 0;

			/** バトルマネージャー */
			BattleManagerObject* m_battleManager = nullptr;
			/** コリジョンマネージャー */
			CollisionManagerObject* m_collisionManager = nullptr;
			/** インゲームUI */
			UIInGame* m_inGameUI = nullptr;
			/** ゲームカメラ */
			GameCamera* m_gameCamera = nullptr;
			/** リザルトUI */
			UIResultBase* m_uiResult = nullptr;


			/** 空を初期化 */
			void InitSky();
			/** スカイキューブ */
			SkyCube* m_skyCube = nullptr;
			/** スカイキューブのタイプ */
			int m_skyCubeType = enSkyCubeType_Night;
		};
	}
}