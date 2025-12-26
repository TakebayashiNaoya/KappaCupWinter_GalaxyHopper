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
		 * タイトルに関連するUIパーツ（ロゴなど）の生成と寿命管理を行う
		 */
		class UITitle : public IGameObject
		{
		private:
			/** タイトルロゴUI（IGameObject） */
			UITitleLogo* m_titleLogo = nullptr;


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
		 * IGameObjectを継承し、Canvasを持つ
		 */
		class UITitleLogo : public IGameObject
		{
		private:
			/** UI描画用のキャンバス（所有権を持つ） */
			std::unique_ptr<UICanvas> m_canvas;
			/** 実際に描画されるロゴ画像（Canvas管理） */
			UIImage* m_icon = nullptr;


		public:
			UITitleLogo();
			~UITitleLogo();

			bool Start() override;
			void Update() override;
			void Render(RenderContext& rc) override;
		};
	}
}