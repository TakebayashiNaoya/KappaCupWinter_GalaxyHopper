/**
 * UITitle.cpp
 * タイトルのUIを管理するクラス
 */
#include "stdafx.h"
#include "UITitle.h"
#include "LoadingScreen.h"


namespace app
{
	namespace ui
	{
		namespace
		{
			/**
			 * UITitleLogo用定数
			 */
			const float			LOGO_W = 1000.0f;
			const float			LOGO_H = 600.0f;
			const Vector3		LOGO_POS = { -400.0f, 100.0f, 0.0f };
			const char* const	PATH_LOGO = "Assets/sprite/TitleLogo.dds";
		}




		/********************************/


		UITitle::UITitle()
		{
		}


		UITitle::~UITitle()
		{
			/** 子オブジェクトの削除 */
			DeleteGO(m_titleLogo);
		}


		bool UITitle::Start()
		{
			/** タイトルロゴ生成*/
			m_titleLogo = NewGO<UITitleLogo>(0, "UITitleLogo");

			return true;
		}


		void UITitle::Update()
		{
			if (LoadingScreen::GetState() == LoadingScreen::EnState::Loading) {
				DeleteGO(this);
			}
		}




		/********************************/


		UITitleLogo::UITitleLogo()
		{
		}


		UITitleLogo::~UITitleLogo()
		{
		}


		bool UITitleLogo::Start()
		{
			/** キャンバスの生成 */
			m_canvas = std::make_unique<UICanvas>();

			/** タイトルロゴの初期化 */
			auto* logo = m_canvas->CreateUI<UIImage>();
			logo->Initialize(
				PATH_LOGO,
				LOGO_W,
				LOGO_H,
				LOGO_POS
			);

			return true;
		}


		void UITitleLogo::Update()
		{
			m_canvas->Update();
		}


		void UITitleLogo::Render(RenderContext& rc)
		{
			/** ロード画面が完全に開いている時だけ描画 */
			if (LoadingScreen::GetState() == LoadingScreen::EnState::Opened) {
				m_canvas->Render(rc);
			}
		}
	}
}