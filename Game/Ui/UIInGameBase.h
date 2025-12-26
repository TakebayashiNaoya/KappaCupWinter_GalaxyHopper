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
		class UIPlayerHp;
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
			 /** プレイヤー体力UI */
			UIPlayerHp* m_uiPlayerLife = nullptr;
			/** ダメージフラッシュUI */
			UIDamageFlash* m_uiDamageFlash = nullptr;
			/** 操作説明UI */
			UIControls* m_uiControls = nullptr;


		public:
			UIInGameBase();
			virtual ~UIInGameBase();

			/** プレイヤーのHPに応じてUIを更新する */
			void SetPlayerHp(int hp);


		protected:
			/** 
			 * 全てのステージで共通のUIを生成する
			 * 派生先のStartで必ず呼ぶこと
			 */
			virtual bool Start() override;


		private:
			/** 各UIはIGameObjectを継承しているため、ここでは不要 */
			void Update() override final {};
			void Render(RenderContext& rc) override final {};
		};




		/********************************/


		/**
		 * プレイヤー体力UI
		 */
		class UIPlayerHp : public IGameObject
		{
		private:
			/** UI描画用のキャンバス */
			std::unique_ptr<UICanvas> m_playerHpCanvas;
			/** 体力の画像 */
			UIImage* m_playerHpImage = nullptr;
			/** 画像パスの配列 */
			std::array<std::string, enPlayerCondition_Num> m_imagePaths;


		public:
			UIPlayerHp();
			~UIPlayerHp();

			/** HPが変わった時に画像を差し替える */
			void SetPlayerHp(int hp);


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;
		};




		/********************************/


		/**
		 * ダメージフラッシュUI
		 */
		class UIDamageFlash : public IGameObject
		{
		private:
			/** UI描画用のキャンバス */
			std::unique_ptr<UICanvas> m_damageFlashCanvas;
			/** ダメージフラッシュ画像 */
			UIImage* m_damageFlashImage = nullptr;


		public:
			UIDamageFlash();
			~UIDamageFlash();

			/** HPが変わった時に画像を差し替える */
			void SetPlayerHp(int hp);


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;
		};




		/********************************/


		/**
		 * 操作説明UI
		 */
		class UIControls : public IGameObject
		{
		private:
			/** UI描画用のキャンバス */
			std::unique_ptr<UICanvas> m_controlsCanvas;


		public:
			UIControls();
			~UIControls();


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;
		};
	}
}