/**
 * UIInGameBase.h
 * インゲーム全体で共通して表示するUI
 */
#pragma once
#include "UIBase.h"
#include "Source/Actor/Types.h"


namespace app
{
	namespace ui
	{
		class UIPlayerLife;
		class UIDamageFlash;
		class UIControls;


		/**
		 * インゲーム共通UI管理クラス
		 */
		class UIInGameBase : public IGameObject
		{
		private:
			/** 管理用キャンバス */
			UICanvas* m_canvas = nullptr;
			/** プレイヤーHP */
			UIPlayerLife* m_uiPlayerLife = nullptr;
			/** ダメージフラッシュ */
			UIDamageFlash* m_uiDamageFlash = nullptr;
			/** 操作説明 */
			UIControls* m_uiControls = nullptr;


		public:
			UIInGameBase();
			virtual ~UIInGameBase();

			/** プレイヤーのHPに応じてUIを更新する */
			void SetPlayerHp(int hp);


		protected:
			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& rc) override;
		};




		/********************************/


		/**
		 * プレイヤー体力UI
		 */
		class UIPlayerLife : public UIImage
		{
		private:
			/** 画像パスの配列 */
			std::array<std::string, enPlayerCondition_Num> m_imagePaths;


		public:
			UIPlayerLife();
			~UIPlayerLife();

			bool Start() override;

			/** HPが変わった時に画像を差し替える */
			void SetPlayerHp(int hp);
		};




		/********************************/


		/**
		 * ダメージフラッシュUI
		 */
		class UIDamageFlash : public UIImage
		{
		public:
			UIDamageFlash();
			~UIDamageFlash();

			bool Start() override;

			/** HPに応じて表示・非表示を切り替える */
			void SetPlayerHp(int hp);
		};




		/********************************/


		/**
		 * 操作説明UI
		 */
		class UIControls : public UICanvas
		{
		public:
			UIControls();
			~UIControls();

			bool Start(); // UICanvasにはStartの純粋仮想がないため、独自定義
		};
	}
}