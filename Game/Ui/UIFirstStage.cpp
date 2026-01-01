/**
 * UIFirstStage.cpp
 * ファーストステージ用のUI管理クラスの実装
 */
#include "stdafx.h"
#include "UIFirstStage.h"
#include "LoadingScreen.h"


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
			DeleteGO(m_uiGear);
		}


		bool UIFirstStage::Start()
		{
			/** 共通UIのStartを必ず呼ぶ */
			if (!UIInGameBase::Start()) {
				return false;
			}

			/** ギアUIを生成 */
			m_uiGear = NewGO<UIGear>(0, "UIGear");
			/** バトルマネージャーに登録 */
			battle::BattleManager::GetInstance()->Register(m_uiGear);

			return true;
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
			m_gearCanvas = std::make_unique<UICanvas>();

			/** ギアアイコンの生成 */
			auto* gear = m_gearCanvas->CreateUI<UIImage>();
			gear->Initialize(
				PATH_GEAR_ICON,
				GEAR_ICON_SIZE,
				GEAR_ICON_SIZE,
				GEAR_ICON_POS
			);

			/** 獲得数の生成 */
			m_gotGearCountText = m_gearCanvas->CreateUI<UIText>();
			m_gotGearCountText->Initialize(
				L"0/0",
				GEAR_NUM_POS,
				1.5f,
				Vector4::White
			);

			return true;
		}


		void UIGear::Update()
		{
			m_gearCanvas->Update();
		}


		void UIGear::Render(RenderContext& rc)
		{
			if (LoadingScreen::GetState() != LoadingScreen::Opened) {
				return;
			}
			if (battle::BattleManager::GetInstance()->IsResultSequence()) {
				return;
			}

			m_gearCanvas->Render(rc);
		}


		void UIGear::SetCount(int gotCount, int maxCount)
		{
			m_gotGearCountText->SetText(L"%d/%d", gotCount, maxCount);
		}
	}
}