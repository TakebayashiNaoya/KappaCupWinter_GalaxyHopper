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

			/** ギア獲得数を設定する */
			void SetGearCount(int count);


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
			std::unique_ptr<UICanvas> m_canvas;

			/** ギアのアイコン画像 */
			UIIcon* m_icon = nullptr;
			/** ギアの数（数字画像） */
			UIDigit* m_digit = nullptr;


		public:
			UIGear();
			~UIGear();

			bool Start() override;
			void Update() override;
			void Render(RenderContext& rc) override;

			/** 表示する数字を更新 */
			void SetCount(int count);
		};
	}
}