/**
 * UIFirstStage.h
 * ファーストステージ用のUI管理クラス
 */
#pragma once
#include "UIInGameBase.h"
#include <memory>

namespace app
{
	namespace ui
	{
		class UIGear;


		/**
		 * ファーストステージUI
		 * 共通UIに加えて、ギア数の表示を行う
		 */
		class UIFirstStage : public UIInGameBase
		{
		private:
			/** ギアUI（IGameObject） */
			UIGear* m_uiGear = nullptr;


		public:
			UIFirstStage();
			~UIFirstStage();


		private:
			bool Start() override final;
		};




		/********************************/


		/**
		 * ギア表示UI
		 * IGameObjectを継承し、Canvasを持つ
		 */
		class UIGear : public IGameObject
		{
		private:
			/** UI描画用のキャンバス */
			std::unique_ptr<UICanvas> m_gearCanvas;

			/** ギアの取得数 */
			UIText* m_gotGearCountText = nullptr;


		public:
			UIGear();
			~UIGear();

			/** 表示する数字を更新 */
			void UpdateCount(int gotCount, int maxCount);


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;
		};
	}
}