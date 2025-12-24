/**
 * UIInGameBase.h
 * インゲーム全体で共通して表示するUIを管理するクラス
 */
#pragma once
#include "UIBase.h"


namespace app
{
	namespace ui
	{
		/**
		 * インゲーム全体で共通して表示するUIを管理するクラス
		 */
		class UIInGameBase : public IGameObject
		{
		public:
			UIInGameBase();
			virtual ~UIInGameBase();

			// 外部（Playerなど）からHPを受け取るメソッド
			void SetPlayerHp(int hp);

		protected:
			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& rc) override;

			// UI管理用キャンバス
			app::ui::UICanvas* m_canvas = nullptr;

			// 共通UIへのポインタ（更新時にアクセスするため）
			UIPlayerLife* m_uiPlayerLife = nullptr;
			UIDamageFlash* m_uiDamageFlash = nullptr;
			UIControls* m_uiControls = nullptr;
		};




		/********************************/


		/**
		 * プレイヤーの体力表示
		 */
		class UIPlayerLife : public UIBase
		{
		public:
			UIPlayerLife() {}
			~UIPlayerLife() {}

			void SetPlayerHp(int hp) { m_playerHp = hp; }

			bool Start() override {
				// 画像の読み込み
				// 座標などは定数定義するか、Initializeで外部から受け取る形にします
				// ここでは元のコードの座標をそのまま使用する例です
				const Vector3 POS = { 800.0f, 400.0f, 0.0f };
				m_hpSprites[enPlayerCondition_Dead].Init("Assets/sprite/HP0.dds", 300.0f, 300.0f);
				m_hpSprites[enPlayerCondition_Danger].Init("Assets/sprite/HP1.dds", 300.0f, 300.0f);
				m_hpSprites[enPlayerCondition_Caution].Init("Assets/sprite/HP2.dds", 300.0f, 300.0f);
				m_hpSprites[enPlayerCondition_Fine].Init("Assets/sprite/HP3.dds", 300.0f, 300.0f);

				for (auto& sprite : m_hpSprites) {
					sprite.SetPosition(POS);
					sprite.Update();
				}
				return true;
			}

			void Update() override {
				// 必要ならアニメーション更新など
			}

			void Render(RenderContext& rc) override {
				// 現在のHPに応じた画像だけを描画
				if (m_playerHp >= 0 && m_playerHp < enPlayerCondition_Num) {
					m_hpSprites[m_playerHp].Draw(rc);
				}
			}

		private:
			std::array<SpriteRender, enPlayerCondition_Num> m_hpSprites;
			int m_playerHp = enPlayerCondition_Fine;
		};

		// =================================================================
		// ダメージフラッシュ (UIBaseを継承)
		// =================================================================
		class UIDamageFlash : public UIBase
		{
		public:
			UIDamageFlash() {}
			~UIDamageFlash() {}

			void SetPlayerHp(int hp) { m_playerHp = hp; }

			bool Start() override {
				m_flashSprites[enPlayerCondition_Danger].Init("Assets/sprite/DamageFlash1.dds", 1920.0f, 1080.0f);
				m_flashSprites[enPlayerCondition_Caution].Init("Assets/sprite/DamageFlash2.dds", 1920.0f, 1080.0f);
				return true;
			}

			void Update() override {}

			void Render(RenderContext& rc) override {
				// 危険か注意のときだけ描画
				if (m_playerHp == enPlayerCondition_Danger || m_playerHp == enPlayerCondition_Caution) {
					m_flashSprites[m_playerHp].Draw(rc);
				}
			}

		private:
			SpriteRender m_flashSprites[enPlayerCondition_Num];
			int m_playerHp = 0;
		};

		// =================================================================
		// 操作説明 (UIBaseを継承)
		// =================================================================
		class UIControls : public UIBase
		{
		public:
			UIControls() {}
			~UIControls() {}

			bool Start() override {
				m_jumpImage.Init("Assets/sprite/RabbitJump.dds", 150.0f, 150.0f);
				m_jumpImage.SetPosition({ 630.0f, -370.0f, 0.0f });
				m_jumpImage.Update();

				m_dashImage.Init("Assets/sprite/RabbitDash.dds", 150.0f, 150.0f);
				m_dashImage.SetPosition({ 800.0f, -300.0f, 0.0f });
				m_dashImage.Update();

				m_buttonA.Init("Assets/sprite/ButtonA_2.dds", 100.0f, 100.0f);
				m_buttonA.SetPosition({ 700.0f, -450.0f, 0.0f });
				m_buttonA.Update();

				m_buttonB.Init("Assets/sprite/ButtonB_2.dds", 100.0f, 100.0f);
				m_buttonB.SetPosition({ 870.0f, -380.0f, 0.0f });
				m_buttonB.Update();
				return true;
			}

			void Update() override {}

			void Render(RenderContext& rc) override {
				m_jumpImage.Draw(rc);
				m_dashImage.Draw(rc);
				m_buttonA.Draw(rc);
				m_buttonB.Draw(rc);
			}

		private:
			SpriteRender m_jumpImage;
			SpriteRender m_dashImage;
			SpriteRender m_buttonA;
			SpriteRender m_buttonB;
		};
	}
}