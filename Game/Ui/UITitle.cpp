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
		UITitle::UITitle()
		{
			/** タイトルロゴを作り、キャンバスの子にする */
			m_titleLogo = m_canvas.CreateUI<UIImage>();

			/** タイトルロゴの初期化 */
			m_titleLogo->Initialize(
				"Assets/sprite/TitleLogo.dds",	/** パス		*/
				1000.0f,						/** 幅			*/
				600.0f,							/** 高さ		*/
				Vector3(-400.0f, 100.0f, 0.0f),	/** 位置		*/
				Vector3::One,					/** スケール	*/
				Quaternion::Identity			/** 回転		*/
			);
		}

		UITitle::~UITitle()
		{
			/** UICanvasのデストラクタで子のUIは自動削除されるため、m_titleLogoをdeleteする必要はない */
		}

		bool UITitle::Start()
		{
			return true;
		}

		void UITitle::Update()
		{
			/** キャンバス全体の更新（子のUIも更新される） */
			m_canvas.Update();

			/** ロード中になったら、自身を削除する */
			if (LoadingScreen::GetState() == LoadingScreen::enState_Loading) {
				DeleteGO(this);
			}
		}

		void UITitle::Render(RenderContext& rc)
		{
			/** ロード画面が完全に開いている時だけ描画 */
			if (LoadingScreen::GetState() == LoadingScreen::enState_Opened) {
				/** キャンバスを描画（子のUIも描画される） */
				m_canvas.Render(rc);
			}
		}
	}
}