#pragma once
#include "Source/Scene/BattleStageBase.h"

class FirstPlanet;
class Treasure;
class Rocket;
class UIGear;


namespace app
{
	namespace ui
	{
		class UIFirstStage;
	}


	namespace scene
	{
		class FirstStage :public BattleStageBase
		{
		public:
			FirstStage();
			~FirstStage();


		private:
			bool Start() override final;

			void OnUpdate() override final;

			void InitLevel()override final;
			LevelRender m_levelRender;


		private:
			/** ファーストステージ用UI */
			ui::UIFirstStage* m_uiFirstStage = nullptr;
			/** ファーストステージ用オブジェクト */
			FirstPlanet* m_firstStage = nullptr;
			/** 宝箱リスト */
			std::vector<Treasure*> m_treasures;
			/** ロケット */
			Rocket* m_rocket = nullptr;
		};
	}
}