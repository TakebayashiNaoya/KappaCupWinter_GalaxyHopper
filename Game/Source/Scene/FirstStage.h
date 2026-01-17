/**
 * FirstStage.h
 * ファーストステージシーン
 */
#pragma once
#include "Source/Scene/BattleStageBase.h"


namespace app
{
	/** 前方宣言 */
	namespace ui { class UIFirstStage; }
	namespace actor {
		class FirstPlanet;
		class Treasure;
		class Rocket;
	}


	namespace scene
	{
		/**
		 * ファーストステージシーン
		 */
		class FirstStage :public BattleStageBase
		{
		public:
			FirstStage();
			~FirstStage();


		private:
			/** 開始処理 */
			bool Start() override final;
			/** 更新処理 */
			void OnUpdate() override final;
			/** レベルの初期化 */
			void InitLevel()override final;


		private:
			/** ファーストステージ用UI */
			ui::UIFirstStage* m_uiFirstStage = nullptr;
			/** ファーストステージ用オブジェクト */
			actor::FirstPlanet* m_firstStage = nullptr;
			/** 宝箱リスト */
			std::vector<actor::Treasure*> m_treasures;
			/** ロケット */
			actor::Rocket* m_rocket = nullptr;
		};
	}
}