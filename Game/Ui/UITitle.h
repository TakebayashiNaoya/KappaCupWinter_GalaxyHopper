/**
 * UITitle.h
 * タイトルのUIを管理するクラス
 */
#pragma once
#include "UIBase.h"

namespace app
{
	namespace ui
	{
		class UITitle : public IGameObject
		{
		private:
			/** UIを管理するキャンバス */
			UICanvas m_canvas;
			/** タイトルロゴの画像 */
			UIImage* m_titleLogo = nullptr;


		public:
			UITitle();
			~UITitle();


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;
		};
	}
}