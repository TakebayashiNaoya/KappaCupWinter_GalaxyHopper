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
			const float			CTRL_BTN_A_SIZE = 100.0f;
			const char* const	PATH_CTRL_BTN_A = "Assets/sprite/ButtonA_2.dds";

			/** ボタンB */
			const Vector3		CTRL_BTN_B_POS = { 870.0f, -380.0f, 0.0f };
			const float			CTRL_BTN_B_SIZE = 100.0f;
			const char* const	PATH_CTRL_BTN_B = "Assets/sprite/ButtonB_2.dds";
		}




		/********************************/


		UIInGameBase::UIInGameBase()
		{
		}


		UIInGameBase::~UIInGameBase()
		{
			DeleteGO(m_uiPlayerHp);
			DeleteGO(m_uiDamageFlash);
			DeleteGO(m_uiControls);
		}


		bool UIInGameBase::Start()
		{
			/** プレイヤーライフ生成 (NewGO) */
			m_uiPlayerHp = NewGO<UIPlayerHp>(0, "UIPlayerHp");

			/** ダメージフラッシュ生成 */
			m_uiDamageFlash = NewGO<UIDamageFlash>(0, "UIDamageFlash");

			/** 操作説明生成 */
			m_uiControls = NewGO<UIControls>(0, "UIControls");

			return true;
		}


		void UIInGameBase::SetPlayerHp(int hp)
		{
			if (m_uiPlayerHp) {
				m_uiPlayerHp->SetPlayerHp(hp);
			}
			if (m_uiDamageFlash) {
				m_uiDamageFlash->SetPlayerHp(hp);
			}
		}




		/********************************/


		/**
		 * プレイヤー体力UI
		 */
		UIPlayerHp::UIPlayerHp()
		{
		}


		UIPlayerHp::~UIPlayerHp()
		{
		}


		bool UIPlayerHp::Start()
		{
			/** キャンバス生成 */
			m_playerHpCanvas = std::make_unique<UICanvas>();

			/** パスを保存しておく */
			m_imagePaths[enPlayerCondition_Dead] = PATH_HP_DEAD;
			m_imagePaths[enPlayerCondition_Danger] = PATH_HP_DANGER;
			m_imagePaths[enPlayerCondition_Caution] = PATH_HP_CAUTION;
			m_imagePaths[enPlayerCondition_Fine] = PATH_HP_FINE;

			/** キャンバス生成 */
			m_playerHpImage = m_playerHpCanvas->CreateUI<UIImage>();
			m_playerHpImage->Initialize(m_imagePaths[enPlayerCondition_Fine].c_str(), LIFE_SIZE_W, LIFE_SIZE_H, LIFE_POS);

			return true;
		}


		void UIPlayerHp::Update()
		{
			m_playerHpCanvas->Update();
		}


		void UIPlayerHp::Render(RenderContext& rc)
		{
			if (LoadingScreen::GetState() != LoadingScreen::EnState::Opened) {
				return;
			}
			if (battle::BattleManager::GetInstance()->IsResultSequence()) {
				return;
			}

			m_playerHpCanvas->Render(rc);
		}


		void UIPlayerHp::SetPlayerHp(int hp)
		{
			/** 画像を差し替え */
			m_playerHpImage->GetSpriteRender()->Init(m_imagePaths[hp].c_str(), LIFE_SIZE_W, LIFE_SIZE_H);
		}




		/********************************/


		/**
		 * ダメージフラッシュUI
		 */
		UIDamageFlash::UIDamageFlash()
		{
		}


		UIDamageFlash::~UIDamageFlash()
		{
		}


		bool UIDamageFlash::Start()
		{
			/** キャンバス生成 */
			m_damageFlashCanvas = std::make_unique<UICanvas>();

			/** ダメージフラッシュ画像生成 */
			m_damageFlashImage = m_damageFlashCanvas->CreateUI<UIImage>();
			m_damageFlashImage->Initialize(PATH_FLASH_DANGER, FLASH_W, FLASH_H, FLASH_POS);

			/** 初期状態は非表示にするため全快状態に設定 */
			SetPlayerHp(enPlayerCondition_Fine);

			return true;
		}


		void UIDamageFlash::Update()
		{
			m_damageFlashCanvas->Update();
		}


		void UIDamageFlash::Render(RenderContext& rc)
		{
			if (LoadingScreen::GetState() != LoadingScreen::EnState::Opened) {
				return;
			}
			if (battle::BattleManager::GetInstance()->IsResultSequence()) {
				return;
			}

			m_damageFlashCanvas->Render(rc);
		}


		void UIDamageFlash::SetPlayerHp(int hp)
		{
			auto* render = m_damageFlashImage->GetSpriteRender();

			if (hp == 1) {
				render->Init(PATH_FLASH_DANGER, FLASH_W, FLASH_H);
			}
			else if (hp == 2) {
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
		}


		UIControls::~UIControls()
		{
		}


		bool UIControls::Start()
		{
			/** キャンバス生成 */
			m_controlsCanvas = std::make_unique<UICanvas>();

			/** ジャンプ */
			auto* jump = m_controlsCanvas->CreateUI<UIImage>();
			jump->Initialize(PATH_CTRL_JUMP, CTRL_JUMP_SIZE, CTRL_JUMP_SIZE, CTRL_JUMP_POS);

			/** ダッシュ */
			auto* dash = m_controlsCanvas->CreateUI<UIImage>();
			dash->Initialize(PATH_CTRL_DASH, CTRL_DASH_SIZE, CTRL_DASH_SIZE, CTRL_DASH_POS);

			/** ボタンA */
			auto* btnA = m_controlsCanvas->CreateUI<UIImage>();
			btnA->Initialize(PATH_CTRL_BTN_A, CTRL_BTN_A_SIZE, CTRL_BTN_A_SIZE, CTRL_BTN_A_POS);

			/** ボタンB */
			auto* btnB = m_controlsCanvas->CreateUI<UIImage>();
			btnB->Initialize(PATH_CTRL_BTN_B, CTRL_BTN_B_SIZE, CTRL_BTN_B_SIZE, CTRL_BTN_B_POS);

			return true;
		}


		void UIControls::Update()
		{
			m_controlsCanvas->Update();
		}


		void UIControls::Render(RenderContext& rc)
		{
			if (LoadingScreen::GetState() != LoadingScreen::EnState::Opened) {
				return;
			}
			if (battle::BattleManager::GetInstance()->IsResultSequence()) {
				return;
			}

			m_controlsCanvas->Render(rc);
		}
	}
}