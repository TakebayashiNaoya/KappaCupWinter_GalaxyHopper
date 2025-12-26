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
			if (m_titleLogo) DeleteGO(m_titleLogo);
		}


		bool UITitle::Start()
		{
			/** タイトルロゴ生成 (NewGO) */
			m_titleLogo = NewGO<UITitleLogo>(0, "UITitleLogo");

			return true;
		}


		void UITitle::Update()
		{
			/** ロード中になったら、自身を削除する */
			/** ※自身が削除されるとデストラクタが呼ばれ、m_titleLogoも削除される */
			if (LoadingScreen::GetState() == LoadingScreen::enState_Loading) {
				DeleteGO(this);
			}
		}




		/********************************/


		UITitleLogo::UITitleLogo()
		{
			m_canvas = std::make_unique<UICanvas>();
		}


		UITitleLogo::~UITitleLogo()
		{
		}


		bool UITitleLogo::Start()
		{
			m_canvas->Start();

			/** タイトルロゴの初期化 */
			m_icon = m_canvas->CreateUI<UIImage>();
			m_icon->Initialize(
				PATH_LOGO,
				LOGO_W,
				LOGO_H,
				LOGO_POS
			);

			return true;
		}


		void UITitleLogo::Update()
		{
			if (m_canvas) m_canvas->Update();
		}


		void UITitleLogo::Render(RenderContext& rc)
		{
			/** ロード画面が完全に開いている時だけ描画 */
			if (LoadingScreen::GetState() == LoadingScreen::enState_Opened) {
				if (m_canvas) m_canvas->Render(rc);
			}
		}
	}
}