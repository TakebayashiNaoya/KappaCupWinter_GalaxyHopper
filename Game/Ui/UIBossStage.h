/**
 * UIBossStage.h
 * ボスステージ用のUI管理クラス
 */
#pragma once
#include "UIInGameBase.h"
#include <memory>

namespace app
{
	namespace ui
	{
		class UIBossLife;


		/**
		 * ボスステージUI
		 * 共通UIに加えて、ボスHPの表示を行う
		 */
		class UIBossStage : public UIInGameBase
		{
		private:
			/** ボスHP UI */
			UIBossLife* m_uiBossLife = nullptr;


		public:
			UIBossStage();
			~UIBossStage();

			/** ボスのHPを設定する */
			void SetBossHp(uint8_t currentHp, uint8_t maxHp);


		private:
			bool Start() override final;
		};




		/********************************/


		/**
		 * ボスHP表示UI
		 * IGameObjectを継承し、Canvasを持つ
		 */
		class UIBossLife : public IGameObject
		{
		private:
			std::unique_ptr<UICanvas> m_canvas;

			/** ボス名画像 */
			UIImage* m_name = nullptr;
			/** HPバー背景画像 */
			UIImage* m_barBack = nullptr;
			/** HPバー前景画像 */
			UIImage* m_barFront = nullptr;


		public:
			UIBossLife();
			~UIBossLife();

			bool Start() override;
			void Update() override;
			void Render(RenderContext& rc) override;

			/** HPの更新（バーの長さと色を変える） */
			void UpdateHp(uint8_t currentHp, uint8_t maxHp);
		};
	}
}