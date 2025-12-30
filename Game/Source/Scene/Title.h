/**
 * Title.h
 * タイトルシーンを管理するクラス
 */
#pragma once
#include "Source/Scene/SceneManager.h"


namespace app
{
	namespace actor
	{
		class TitlePlayer;
		class TitlePlanet;
	}
	namespace camera
	{
		class TitleCamera;
	}
	namespace ui
	{
		class UITitle;
	}


	namespace scene
	{
		class Title :public IScene
		{
		public:
			Title();
			~Title();


		private:
			bool Start() override final;
			void Update() override final;


		private:
			actor::TitlePlayer* m_titlePlayer = nullptr;
			actor::TitlePlanet* m_titlePlanet = nullptr;
			camera::TitleCamera* m_titleCamera = nullptr;
			ui::UITitle* m_uiTitle = nullptr;


		private:
			/** 空を初期化 */
			void InitSky();

			SkyCube* m_skyCube = nullptr;
			int m_skyCubeType = enSkyCubeType_SpaceToon_2;
		};
	}
}