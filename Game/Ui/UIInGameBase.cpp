/**
 * UIInGameBase.cpp
 * インゲーム全体で共通して表示するUIを実装
 */
#include "stdafx.h"
#include "UIInGameBase.h"
#include "Battle/BattleManager.h"
#include "LoadingScreen.h"


namespace app
{
	namespace ui
	{
		namespace
		{
			/**
			 * UIPlayerLife用定数
			 */
			const Vector3		LIFE_POS = { 800.0f, 400.0f, 0.0f };
			const float			LIFE_SIZE_W = 300.0f;
			const float			LIFE_SIZE_H = 300.0f;

			const char* const	PATH_HP_DEAD = "Assets/sprite/HP0.dds";
			const char* const	PATH_HP_DANGER = "Assets/sprite/HP1.dds";
			const char* const	PATH_HP_CAUTION = "Assets/sprite/HP2.dds";
			const char* const	PATH_HP_FINE = "Assets/sprite/HP3.dds";


			/**
			 * UIDamageFlash用定数
			 */
			const float			FLASH_W = 1920.0f;
			const float			FLASH_H = 1080.0f;
			const Vector3		FLASH_POS = Vector3::Zero;

			const char* const	PATH_FLASH_NONE = "Assets/sprite/DamageFlash0.dds";
			const char* const	PATH_FLASH_DANGER = "Assets/sprite/DamageFlash1.dds";
			const char* const	PATH_FLASH_CAUTION = "Assets/sprite/DamageFlash2.dds";


			/**
			 * UIControls用定数
			 */
			 /** ジャンプ */
			const Vector3		CTRL_JUMP_POS = { 630.0f, -370.0f, 0.0f };
			const float			CTRL_JUMP_SIZE = 150.0f;
			const char* const	PATH_CTRL_JUMP = "Assets/sprite/RabbitJump.dds";

			/** ダッシュ */
			const Vector3		CTRL_DASH_POS = { 800.0f, -300.0f, 0.0f };
			const float			CTRL_DASH_SIZE = 150.0f;
			const char* const	PATH_CTRL_DASH = "Assets/sprite/RabbitDash.dds";

			/** ボタンA */
			const Vector3		CTRL_BTN_A_POS = { 700.0f, -450.0f, 0.0f };
			const float			CTRL_BTN_SIZE = 100.0f;
			const char* const	PATH_CTRL_BTN_A = "Assets/sprite/ButtonA_2.dds";

			/** ボタンB */
			const Vector3		CTRL_BTN_B_POS = { 870.0f, -380.0f, 0.0f };
			const float			CTRL_BTN_SIZE = 100.0f;
			const char* const	PATH_CTRL_BTN_B = "Assets/sprite/ButtonB_2.dds";
		}




		/********************************/


		UIInGameBase::UIInGameBase()
		{
		}


		UIInGameBase::~UIInGameBase()
		{
			/** IGameObjectはDeleteGOで削除する */
			if (m_uiPlayerLife) DeleteGO(m_uiPlayerLife);
			if (m_uiDamageFlash) DeleteGO(m_uiDamageFlash);
			if (m_uiControls) DeleteGO(m_uiControls);
		}


		bool UIInGameBase::Start()
		{
			/** プレイヤーライフ生成 (NewGO) */
			m_uiPlayerLife = NewGO<UIPlayerLife>(0, "UIPlayerLife");
			/** NewGOで生成されたオブジェクトのStartはエンジンが自動で呼ぶため、ここでは呼ばない */

			/** ダメージフラッシュ生成 */
			m_uiDamageFlash = NewGO<UIDamageFlash>(0, "UIDamageFlash");

			/** 操作説明生成 */
			m_uiControls = NewGO<UIControls>(0, "UIControls");

			return true;
		}


		void UIInGameBase::SetPlayerHp(int hp)
		{
			if (m_uiPlayerLife) {
				m_uiPlayerLife->SetPlayerHp(hp);
			}
			if (m_uiDamageFlash) {
				m_uiDamageFlash->SetPlayerHp(hp);
			}
		}




		/********************************/


		/**
		 * プレイヤー体力UI
		 */
		UIPlayerLife::UIPlayerLife()
		{
			m_canvas = std::make_unique<UICanvas>();

			/** パスを保存しておく */
			m_imagePaths[enPlayerCondition_Dead] = PATH_HP_DEAD;
			m_imagePaths[enPlayerCondition_Danger] = PATH_HP_DANGER;
			m_imagePaths[enPlayerCondition_Caution] = PATH_HP_CAUTION;
			m_imagePaths[enPlayerCondition_Fine] = PATH_HP_FINE;
		}


		UIPlayerLife::~UIPlayerLife()
		{
		}


		bool UIPlayerLife::Start()
		{
			m_canvas->Start();

			m_icon = m_canvas->CreateUI<UIImage>();
			m_icon->Initialize(m_imagePaths[enPlayerCondition_Fine].c_str(), LIFE_SIZE_W, LIFE_SIZE_H, LIFE_POS);

			return true;
		}


		void UIPlayerLife::Update()
		{
			if (m_canvas) m_canvas->Update();
		}


		void UIPlayerLife::Render(RenderContext& rc)
		{
			/** UIPlayerLife自体が描画条件を持つ場合ここに記述 */
			if (LoadingScreen::GetState() != LoadingScreen::enState_Opened) {
				return;
			}
			if (battle::BattleManager::GetIsBattleFinish()) {
				return;
			}

			if (m_canvas) m_canvas->Render(rc);
		}


		void UIPlayerLife::SetPlayerHp(int hp)
		{
			/** 範囲外なら何もしない */
			if (hp < 0 || hp >= enPlayerCondition_Num) {
				return;
			}
			/** 画像を差し替え */
			if (m_icon) {
				m_icon->GetSpriteRender()->Init(m_imagePaths[hp].c_str(), LIFE_SIZE_W, LIFE_SIZE_H);
			}
		}




		/********************************/


		/**
		 * ダメージフラッシュUI
		 */
		UIDamageFlash::UIDamageFlash()
		{
			m_canvas = std::make_unique<UICanvas>();
		}


		UIDamageFlash::~UIDamageFlash()
		{
		}


		bool UIDamageFlash::Start()
		{
			m_canvas->Start();

			m_icon = m_canvas->CreateUI<UIImage>();
			m_icon->Initialize(PATH_FLASH_DANGER, FLASH_W, FLASH_H, FLASH_POS);

			SetPlayerHp(enPlayerCondition_Fine);

			return true;
		}


		void UIDamageFlash::Update()
		{
			if (m_canvas) m_canvas->Update();
		}


		void UIDamageFlash::Render(RenderContext& rc)
		{
			if (LoadingScreen::GetState() != LoadingScreen::enState_Opened) {
				return;
			}
			if (battle::BattleManager::GetIsBattleFinish()) {
				return;
			}

			if (m_canvas) m_canvas->Render(rc);
		}


		void UIDamageFlash::SetPlayerHp(int hp)
		{
			if (!m_icon) return;

			auto* render = m_icon->GetSpriteRender();

			if (hp == enPlayerCondition_Danger) {
				render->Init(PATH_FLASH_DANGER, FLASH_W, FLASH_H);
			}
			else if (hp == enPlayerCondition_Caution) {
				render->Init(PATH_FLASH_CAUTION, FLASH_W, FLASH_H);
			}
			else {
				render->Init(PATH_FLASH_NONE, FLASH_W, FLASH_H);
			}
			render->Update();
		}




		/********************************/


		/**
		 * 操作説明UI
		 */
		UIControls::UIControls()
		{
			m_canvas = std::make_unique<UICanvas>();
		}


		UIControls::~UIControls()
		{
		}


		bool UIControls::Start()
		{
			m_canvas->Start();

			/** ジャンプ */
			auto* jump = m_canvas->CreateUI<UIImage>();
			jump->Initialize(PATH_CTRL_JUMP, CTRL_JUMP_SIZE, CTRL_JUMP_SIZE, CTRL_JUMP_POS);

			/** ダッシュ */
			auto* dash = m_canvas->CreateUI<UIImage>();
			dash->Initialize(PATH_CTRL_DASH, CTRL_DASH_SIZE, CTRL_DASH_SIZE, CTRL_DASH_POS);

			/** ボタンA */
			auto* btnA = m_canvas->CreateUI<UIImage>();
			btnA->Initialize(PATH_CTRL_BTN_A, CTRL_BTN_SIZE, CTRL_BTN_SIZE, CTRL_BTN_A_POS);

			/** ボタンB */
			auto* btnB = m_canvas->CreateUI<UIImage>();
			btnB->Initialize(PATH_CTRL_BTN_B, CTRL_BTN_SIZE, CTRL_BTN_SIZE, CTRL_BTN_B_POS);

			return true;
		}


		void UIControls::Update()
		{
			if (m_canvas) m_canvas->Update();
		}


		void UIControls::Render(RenderContext& rc)
		{
			if (LoadingScreen::GetState() != LoadingScreen::enState_Opened) {
				return;
			}
			if (battle::BattleManager::GetIsBattleFinish()) {
				return;
			}

			if (m_canvas) m_canvas->Render(rc);
		}
	}
}