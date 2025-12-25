/**
 * UIFirstStage.cpp
 * ファーストステージ用のUI管理クラスの実装
 */
#include "stdafx.h"
#include "UIFirstStage.h"
#include "LoadingScreen.h"
#include "Battle/BattleManager.h"


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
			if (m_uiGear) DeleteGO(m_uiGear);
		}


		bool UIFirstStage::Start()
		{
			/** 共通UIのStartを必ず呼ぶ */
			if (!UIInGameBase::Start()) {
				return false;
			}

			/** ギアUIを生成 */
			m_uiGear = NewGO<UIGear>(0, "UIGear");

			return true;
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
			m_canvas = std::make_unique<UICanvas>();
		}


		UIGear::~UIGear()
		{
		}


		bool UIGear::Start()
		{
			m_canvas->Start();

			/** アイコンの生成 */
			m_icon = m_canvas->CreateUI<UIIcon>();
			m_icon->Initialize(
				PATH_GEAR_ICON,
				GEAR_ICON_SIZE,
				GEAR_ICON_SIZE,
				GEAR_ICON_POS
			);

			/** 数字の生成 */
			m_digit = m_canvas->CreateUI<UIDigit>();
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


		void UIGear::Update()
		{
			if (m_canvas) m_canvas->Update();
		}


		void UIGear::Render(RenderContext& rc)
		{
			if (LoadingScreen::GetState() != LoadingScreen::enState_Opened) {
				return;
			}
			if (battle::BattleManager::GetIsBattleFinish()) {
				return;
			}

			if (m_canvas) m_canvas->Render(rc);
		}


		void UIGear::SetCount(int count)
		{
			if (m_digit) {
				m_digit->SetNumber(count);
			}
		}
	}
}