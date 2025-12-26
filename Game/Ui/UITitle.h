/**
 * UITitle.h
 * タイトルのUIを管理するクラス
 */
#pragma once
#include "UIBase.h"
#include <memory>

namespace app
{
	namespace ui
	{
		class UITitleLogo;


		/**
		 * タイトル画面UI管理クラス
		 */
		class UITitle : public IGameObject
		{
		private:
			/** タイトルロゴUI */
			UITitleLogo* m_titleLogo = nullptr;

			/** タイトルで他に描画したい物があればここに追加する */


		public:
			UITitle();
			~UITitle();


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final {};
		};




		/********************************/


		/**
		 * タイトルロゴ表示UI
		 */
		class UITitleLogo : public IGameObject
		{
		private:
			/** UI描画用のキャンバス */
			std::unique_ptr<UICanvas> m_canvas;


		public:
			UITitleLogo();
			~UITitleLogo();


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;
		};
	}
}