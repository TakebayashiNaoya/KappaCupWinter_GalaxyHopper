/**
 * UIFirstStage.h
 * ファーストステージ用のUI管理クラス
 */
#pragma once
#include "UIInGameBase.h"

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
			/** ギアUI */
			UIGear* m_uiGear = nullptr;


		public:
			UIFirstStage();
			~UIFirstStage();

			/** ギア獲得数を設定する */
			void SetGearCount(int count);


		protected:
			bool Start() override;
			void Update() override;
		};




		/********************************/


		/**
		 * ギア表示UI
		 * アイコンと数字をまとめて管理するためUICanvasを継承
		 */
		class UIGear : public UICanvas
		{
		private:
			/** ギアのアイコン画像 */
			UIImage* m_icon = nullptr;
			/** ギアの数（数字画像） */
			UIDigit* m_digit = nullptr;


		public:
			UIGear();
			~UIGear();

			bool Start();

			/** 表示する数字を更新 */
			void SetCount(int count);
		};
	}
}