/**
 * UIInGameBase.h
 * インゲーム全体で共通して表示するUIを実装
 */
#include "stdafx.h"
#include "UIInGameBase.h"
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
			m_canvas = new UICanvas();
		}


		UIInGameBase::~UIInGameBase()
		{
			delete m_canvas;
		}


		bool UIInGameBase::Start()
		{
			if (!m_canvas) {
				return false;
			}
			m_canvas->Start();

			// 1. プレイヤーライフ生成
			m_uiPlayerLife = m_canvas->CreateUI<UIPlayerLife>();
			m_uiPlayerLife->Start();

			// 2. ダメージフラッシュ生成
			m_uiDamageFlash = m_canvas->CreateUI<UIDamageFlash>();
			m_uiDamageFlash->Start();

			// 3. 操作説明生成
			m_uiControls = m_canvas->CreateUI<UIControls>();
			m_uiControls->Start();

			return true;
		}


		void UIInGameBase::Update()
		{
			// キャンバスを一括更新（子UIのUpdateも呼ばれる）
			if (m_canvas) {
				m_canvas->Update();
			}
		}


		void UIInGameBase::Render(RenderContext& rc)
		{
			if (LoadingScreen::GetState() != LoadingScreen::enState_Opened) return;
			if (BattleManager::GetIsBattleFinish()) return;

			// キャンバスを一括描画（子UIのRenderも呼ばれる）
			if (m_canvas) {
				m_canvas->Render(rc);
			}
		}


		void UIInGameBase::SetPlayerHp(int hp)
		{
			if (m_uiPlayerLife) m_uiPlayerLife->SetPlayerHp(hp);
			if (m_uiDamageFlash) m_uiDamageFlash->SetPlayerHp(hp);
		}




		/********************************/


		/**
		 * プレイヤー体力UI
		 */
		UIPlayerLife::UIPlayerLife()
		{
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
			Initialize(
				m_imagePaths[enPlayerCondition_Fine].c_str(),
				LIFE_SIZE_W, LIFE_SIZE_H,
				LIFE_POS,
				Vector3::One,
				Quaternion::Identity
			);
			return true;
		}


		void UIPlayerLife::SetPlayerHp(int hp)
		{
			/** 範囲外なら何もしない */
			if (hp < 0 || hp >= enPlayerCondition_Num) {
				return;
			}
			/** 画像を差し替え */
			m_spriteRender.Init(m_imagePaths[hp].c_str(), LIFE_SIZE_W, LIFE_SIZE_H);
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
			Initialize(
				PATH_FLASH_DANGER,
				FLASH_W, FLASH_H,
				FLASH_POS,
				Vector3::One,
				Quaternion::Identity
			);

			/** 最初は非表示（透明） */
			m_spriteRender.SetMulColor({ 1.0f, 1.0f, 1.0f, 0.0f });
			m_spriteRender.Update();

			return true;
		}


		void UIDamageFlash::SetPlayerHp(int hp)
		{
			if (hp == enPlayerCondition_Danger) {
				// 危険：赤色フラッシュ画像にし、不透明度を上げる
				m_spriteRender.Init(PATH_FLASH_DANGER, FLASH_W, FLASH_H);
				m_spriteRender.SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
			}
			else if (hp == enPlayerCondition_Caution) {
				// 注意：黄色フラッシュ画像にし、不透明度を上げる
				m_spriteRender.Init(PATH_FLASH_CAUTION, FLASH_W, FLASH_H);
				m_spriteRender.SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
			}
			else {
				// それ以外：透明にする
				m_spriteRender.SetMulColor({ 0.0f, 0.0f, 0.0f, 0.0f });
			}
			m_spriteRender.Update();
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
			// ジャンプ
			auto* jump = CreateUI<UIImage>();
			jump->Initialize(
				PATH_CTRL_JUMP,
				CTRL_JUMP_SIZE,
				CTRL_JUMP_SIZE,
				CTRL_JUMP_POS,
				Vector3::One,
				Quaternion::Identity
			);

			// ダッシュ
			auto* dash = CreateUI<UIImage>();
			dash->Initialize(
				PATH_CTRL_DASH,
				CTRL_DASH_SIZE,
				CTRL_DASH_SIZE,
				CTRL_DASH_POS,
				Vector3::One,
				Quaternion::Identity
			);

			// ボタンA
			auto* btnA = CreateUI<UIImage>();
			btnA->Initialize(
				PATH_CTRL_BTN_A,
				CTRL_BTN_SIZE,
				CTRL_BTN_SIZE,
				CTRL_BTN_A_POS,
				Vector3::One,
				Quaternion::Identity
			);

			// ボタンB
			auto* btnB = CreateUI<UIImage>();
			btnB->Initialize(
				PATH_CTRL_BTN_B,
				CTRL_BTN_SIZE,
				CTRL_BTN_SIZE,
				CTRL_BTN_B_POS,
				Vector3::One,
				Quaternion::Identity
			);

			return true;
		}
	}
}