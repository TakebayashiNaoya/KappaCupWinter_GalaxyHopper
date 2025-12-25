/**
 * UIBossStage.h
 * ボスステージ用のUI管理クラス
 */
#pragma once
#include "UIInGameBase.h"

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


		protected:
			bool Start() override;
			void Update() override;
		};




		/********************************/


		/**
		 * ボスHP表示UI
		 * 名前、HPバー（背景・前景）をまとめて管理
		 */
		class UIBossLife : public UICanvas
		{
		private:
			/** ボス名画像 */
			UIImage* m_name = nullptr;
			/** HPバー背景画像 */
			UIImage* m_barBack = nullptr;
			/** HPバー前景画像 */
			UIImage* m_barFront = nullptr;


		public:
			UIBossLife();
			~UIBossLife();

			bool Start();

			/** HPの更新（バーの長さと色を変える） */
			void UpdateHp(uint8_t currentHp, uint8_t maxHp);
		};
	}
}