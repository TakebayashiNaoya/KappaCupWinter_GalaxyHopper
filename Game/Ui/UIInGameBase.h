/**
 * UIInGameBase.h
 * インゲーム全体で共通して表示するUI
 */
#pragma once
#include "UIBase.h"
#include "Source/Actor/Types.h"
#include <memory>


namespace app
{
	namespace ui
	{
		class UIPlayerLife;
		class UIDamageFlash;
		class UIControls;


		/**
		 * インゲーム共通UI管理クラス
		 * 各UI要素（IGameObject）を統括して管理する
		 */
		class UIInGameBase : public IGameObject
		{
		private:
			/**
			 * 各UIはIGameObjectとして管理する
			 */
			UIPlayerLife* m_uiPlayerLife = nullptr;
			UIDamageFlash* m_uiDamageFlash = nullptr;
			UIControls* m_uiControls = nullptr;


		public:
			UIInGameBase();
			virtual ~UIInGameBase();

			/** プレイヤーのHPに応じてUIを更新する */
			void SetPlayerHp(int hp);


		protected:
			/** 派生先のStartで必ず呼ぶこと */
			virtual bool Start() override;


		private:
			/** 各UIはIGameObjectを継承しているため、ここでは不要 */
			void Update() override final {};
			void Render(RenderContext& rc) override final {};
		};




		/********************************/


		/**
		 * プレイヤー体力UI
		 * IGameObjectを継承し、Canvasを持つ
		 */
		class UIPlayerLife : public IGameObject
		{
		private:
			/** UI描画用のキャンバス（所有権を持つ） */
			std::unique_ptr<UICanvas> m_canvas;

			/** 実際に描画されるアイコン（Canvas管理） */
			UIIcon* m_icon = nullptr;

			/** 画像パスの配列 */
			std::array<std::string, enPlayerCondition_Num> m_imagePaths;


		public:
			UIPlayerLife();
			~UIPlayerLife();

			bool Start() override;
			void Update() override;
			void Render(RenderContext& rc) override;

			/** HPが変わった時に画像を差し替える */
			void SetPlayerHp(int hp);
		};




		/********************************/


		/**
		 * ダメージフラッシュUI
		 * IGameObjectを継承し、Canvasを持つ
		 */
		class UIDamageFlash : public IGameObject
		{
		private:
			std::unique_ptr<UICanvas> m_canvas;
			UIIcon* m_icon = nullptr;

		public:
			UIDamageFlash();
			~UIDamageFlash();

			bool Start() override;
			void Update() override;
			void Render(RenderContext& rc) override;

			/** HPに応じて表示・非表示を切り替える */
			void SetPlayerHp(int hp);
		};




		/********************************/


		/**
		 * 操作説明UI
		 * IGameObjectを継承し、Canvasを持つ
		 */
		class UIControls : public IGameObject
		{
		private:
			std::unique_ptr<UICanvas> m_canvas;

		public:
			UIControls();
			~UIControls();

			bool Start() override;
			void Update() override;
			void Render(RenderContext& rc) override;
		};
	}
}