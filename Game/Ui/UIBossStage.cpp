/**
 * UIBossStage.cpp
 * ボスステージ用のUI管理クラスの実装
 */
#include "stdafx.h"
#include "UIBossStage.h"
#include "LoadingScreen.h"
#include "Battle/BattleManager.h"


namespace app
{
	namespace ui
	{
		namespace
		{
			/**
			 * UIBossLife用定数
			 */

			 /** ボス名 */
			const Vector3		NAME_POS = { 0.0f, 480.0f, 0.0f };
			const float			NAME_W = 180.0f;
			const float			NAME_H = 50.0f;
			const char* const	NAME_PATH = "Assets/sprite/Boss.dds";

			/** HPバー背景 */
			const Vector3		BAR_BACK_POS = { 0.0f, 400.0f, 0.0f };
			const float			BAR_BACK_W = 1071.0f;
			const float			BAR_BACK_H = 107.0f;
			const char* const	BAR_BACK_PATH = "Assets/sprite/BossHpBarBack.dds";

			/** HPバー前景 */
			const Vector3		BAR_FRONT_POS = { -420.0f, 400.0f, 0.0f };
			const float			BAR_FRONT_W = 937.0f;
			const float			BAR_FRONT_H = 37.0f;
			const char* const	BAR_FRONT_PATH = "Assets/sprite/BossHpBarFront.dds";

			/** ピボット設定（左中央） */
			const Vector2		PIVOT_LEFT_CENTER = { 0.0f, 0.5f };

			/** HPバーの色定義 */
			const Vector4		COLOR_GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
			const Vector4		COLOR_YELLOW = { 1.0f, 1.0f, 0.0f, 1.0f };
			const Vector4		COLOR_RED = { 1.0f, 0.0f, 0.0f, 1.0f };

			/** HPバーの色が変化するHPの割合 */
			constexpr float		HP_MIDDLE = 0.5f;	/** 黄色に変化するHP残量*/
			constexpr float		HP_LOW = 0.2f;		/** 赤色に変化するHP残量*/
		}




		/********************************/


		/**
		 * ボスステージ用UI
		 */
		UIBossStage::UIBossStage()
		{
		}


		UIBossStage::~UIBossStage()
		{
			DeleteGO(m_uiBossHp);
		}


		bool UIBossStage::Start()
		{
			/** 親クラス（共通UI）のStart */
			if (!UIInGameBase::Start()) {
				return false;
			}

			/** ボスHP UI生成 */
			m_uiBossHp = NewGO<UIBossHp>(0, "UIBossHp");

			return true;
		}


		void UIBossStage::SetBossHp(uint8_t currentHp, uint8_t maxHp)
		{
			m_uiBossHp->UpdateHp(currentHp, maxHp);
		}




		/********************************/


		/**
		 * ボスHP表示UI
		 */
		UIBossHp::UIBossHp()
		{
		}


		UIBossHp::~UIBossHp()
		{
		}


		bool UIBossHp::Start()
		{
			/** キャンバス生成 */
			m_bossHpCanvas = std::make_unique<UICanvas>();

			/** ボス名の画像生成 */
			auto* bossName = m_bossHpCanvas->CreateUI<UIImage>();
			bossName->Initialize(
				NAME_PATH,
				NAME_W,
				NAME_H,
				NAME_POS
			);

			/** HPバー背景画像の生成 */
			auto* backBar = m_bossHpCanvas->CreateUI<UIImage>();
			backBar->Initialize(
				BAR_BACK_PATH,
				BAR_BACK_W,
				BAR_BACK_H,
				BAR_BACK_POS
			);

			/** HPバー前景の生成 */
			m_frontBarImage = m_bossHpCanvas->CreateUI<UIImage>();
			/** 左端を基準に伸縮させるため、ピボットを左中央に設定 */
			m_frontBarImage->GetSpriteRender()->SetPivot(PIVOT_LEFT_CENTER);
			/** 初期カラー（緑） */
			m_frontBarImage->GetSpriteRender()->SetMulColor(COLOR_GREEN);
			m_frontBarImage->Initialize(
				BAR_FRONT_PATH,
				BAR_FRONT_W,
				BAR_FRONT_H,
				BAR_FRONT_POS
			);
			m_frontBarImage->GetSpriteRender()->Update();

			return true;
		}


		void UIBossHp::Update()
		{
			m_bossHpCanvas->Update();
		}


		void UIBossHp::Render(RenderContext& rc)
		{
			if (LoadingScreen::GetState() != LoadingScreen::enState_Opened) {
				return;
			}
			if (battle::BattleManager::GetInstance()->IsResultSequence()) {
				return;
			}
			m_bossHpCanvas->Render(rc);
		}


		void UIBossHp::UpdateHp(uint8_t currentHp, uint8_t maxHp)
		{
			if (!m_frontBarImage || maxHp <= 0) {
				return;
			}

			/** HP割合計算 */
			float hpRatio = static_cast<float>(currentHp) / static_cast<float>(maxHp);
			/** HPバーの長さ更新 */
			m_frontBarImage->GetSpriteRender()->SetScale(Vector3(hpRatio, 1.0f, 1.0f));

			/** 色更新 */
			Vector4 color = COLOR_RED;
			if (hpRatio > HP_MIDDLE) {
				color = COLOR_GREEN;
			}
			else if (hpRatio > HP_LOW) {
				color = COLOR_YELLOW;
			}

			m_frontBarImage->GetSpriteRender()->SetMulColor(color);
			m_frontBarImage->GetSpriteRender()->Update();
		}
	}
}