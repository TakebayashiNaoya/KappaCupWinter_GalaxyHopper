/**
 * UIFirstStage.cpp
 * ファーストステージ用のUI管理クラスの実装
 */
#include "stdafx.h"
#include "UIFirstStage.h"


namespace app
{
	namespace ui
	{
		namespace
		{
			/**
			 * UIGear用定数
			 */
			 /** アイコン */
			const Vector3		GEAR_ICON_POS = { -850.0f, 450.0f, 0.0f };
			const float			GEAR_ICON_SIZE = 150.0f;
			const char* const	PATH_GEAR_ICON = "Assets/sprite/Gear.dds";

			/** 取得数 */
			const Vector3		GEAR_NUM_POS = { -770.0f, 490.0f, 0.0f };
			const float			GEAR_NUM_W = 50.0f;
			const float			GEAR_NUM_H = 100.0f;
			const int			GEAR_DIGIT_COUNT = 1;

			/** UIDigitは末尾の数字を置換して読み込むため、0番のパスを指定する */
			const char* const	PATH_GEAR_NUM_BASE = "Assets/sprite/Numbers/0.dds";
		}




		/********************************/


		UIFirstStage::UIFirstStage()
		{
		}


		UIFirstStage::~UIFirstStage()
		{
		}


		bool UIFirstStage::Start()
		{
			/** 共通UIのStartを必ず呼ぶ */
			if (!UIInGameBase::Start()) {
				return false;
			}

			/** ギアUIを生成 */
			if (m_canvas) {
				m_uiGear = m_canvas->CreateUI<UIGear>();
				m_uiGear->Start();
			}

			return true;
		}


		void UIFirstStage::Update()
		{
			/** 親クラスの更新（キャンバス更新） */
			UIInGameBase::Update();

			/** 追加の処理があればここに記載 */
		}


		void UIFirstStage::SetGearCount(int count)
		{
			if (m_uiGear) {
				m_uiGear->SetCount(count);
			}
		}




		/********************************/


		/**
		 * ギア表示UI
		 */
		UIGear::UIGear()
		{
		}


		UIGear::~UIGear()
		{
		}


		bool UIGear::Start()
		{
			/** アイコンの生成 */
			m_icon = CreateUI<UIImage>();
			m_icon->Initialize(
				PATH_GEAR_ICON,
				GEAR_ICON_SIZE,
				GEAR_ICON_SIZE,
				GEAR_ICON_POS
			);

			/** 数字の生成 */
			m_digit = CreateUI<UIDigit>();
			m_digit->Initialize(
				PATH_GEAR_NUM_BASE,
				GEAR_DIGIT_COUNT,
				0,
				GEAR_NUM_W,
				GEAR_NUM_H,
				GEAR_NUM_POS
			);

			return true;
		}


		void UIGear::SetCount(int count)
		{
			if (m_digit) {
				m_digit->SetNumber(count);
			}
		}
	}
}