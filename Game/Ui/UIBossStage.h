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
		class UIBossHp;


		/**
		 * ボスステージUI
		 * 共通UIに加えて、ボスHPの表示を行う
		 */
		class UIBossStage : public UIInGameBase
		{
		private:
			/** ボスHP UI */
			UIBossHp* m_uiBossHp = nullptr;


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
		class UIBossHp : public IGameObject
		{
		private:
			/** UI描画用のキャンバス */
			std::unique_ptr<UICanvas> m_bossHpCanvas;
			/** HPバー前景画像 */
			UIImage* m_frontBarImage = nullptr;


		public:
			UIBossHp();
			~UIBossHp();

			/** HPの更新（バーの長さと色を変える） */
			void UpdateHp(uint8_t currentHp, uint8_t maxHp);


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;
		};
	}
}