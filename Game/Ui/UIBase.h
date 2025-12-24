/**
 * UIBase.h
 * UIの基本的な処理をするクラス群
 */
#pragma once
#include "HierarchicalTransform.h"


namespace app
{
	namespace ui
	{
		class SpriteAnimationBase;


		/**
		 * UIの基本クラス
		 */
		class UIBase : public Noncopyable
		{
		public:
			/** トランスフォーム */
			HierarchicalTransform m_transform;


		protected:
			/** スプライトアニメーション一括管理するためのリスト */
			std::vector<SpriteAnimationBase*> m_spriteAnimationList;


		public:
			UIBase();
			virtual ~UIBase();


		public:
			virtual bool Start() = 0;
			virtual void Update() = 0;
			virtual void Render(RenderContext& rc) = 0;


		public:
			/** スプライトアニメーションの追加 */
			void AddSpriteAnimation(SpriteAnimationBase* animation);
			/** スプライトアニメーションの再生 */
			void PlaySpriteAnimations();
			/** スプライトアニメーションの停止 */
			void StopSpriteAnimations();
		};




		/********************************/


		/**
		 * 画像を使うUIの基本クラス
		 */
		class UIImage : public UIBase
		{
		protected:
			/** スプライトレンダー */
			SpriteRender m_spriteRender;


		protected:
			UIImage();
			~UIImage();


		public:
			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& rc) override;


		public:
			/** スプライトレンダーの取得 */
			SpriteRender* GetSpriteRender() { return &m_spriteRender; }

			/** 初期化 */
			void Initialize(
				const char* assetPath,			/** アセットパス */
				const float width,				/** 幅			 */
				const float height,				/** 高さ		 */
				const Vector3& position,		/** 座標		 */
				const Vector3& scale,			/** 拡大縮小	 */
				const Quaternion& rotation		/** 回転		 */
			);
		};


		/**
		 * ゲージUI
		 */
		class UIGauge : public UIImage
		{
			friend class UICanvas;


		private:
			UIGauge();
			~UIGauge();


		public:
			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& rc) override;
		};


		/**
		 * アイコンUI
		 */
		class UIIcon : public UIImage
		{
			friend class UICanvas;

		private:
			UIIcon();
			~UIIcon();


		public:
			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& rc) override;
		};




		/********************************/


		/**
		 * 文字を使うUIの基本クラス
		 */
		class UIText : public UIBase
		{
		protected:
			FontRender m_fontRender;


		private:
			UIText();
			~UIText();


		public:
			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& rc) override;
		};




		/********************************/


		/**
		 * ボタンを使うUIの基本クラス
		 */
		class UIButton : public UIImage
		{
		private:
			/** ボタンが押されたときの処理(外部から委譲される) */
			std::function<void()> m_delegate;


		private:
			UIButton();
			~UIButton();


		public:
			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& rc) override;
		};




		/********************************/


		/**
		 * 画像を使って数字を表示するUIの基本クラス
		 */
		class UIDigit : public UIBase
		{
		private:
			/** 画像表示機能の可変長配列 */
			std::vector<SpriteRender*> m_renderList;
			/** 表示される数字 */
			int m_number;
			/** 表示してほしい数字 */
			int m_requestNumber;
			/** 桁数 */
			int m_digit;
			/** 数字表示に必要な画像が入った */
			std::string m_assetPath;
			/** 幅 */
			int m_width;
			/** 高さ */
			int m_height;


		public:
			UIDigit();
			~UIDigit();


		public:
			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& rc) override;


		public:
			/** 初期化 */
			void Initialize(
				const char* assetPath,		/** アセットパス */
				const int digit,			/** 桁数		 */
				const int number,			/** 表示したい値 */
				const float widht,			/** 幅			 */
				const float height,			/** 高さ		 */
				const Vector3& position,	/** 座標		 */
				const Vector3& scale,		/** 拡大縮小	 */
				const Quaternion& rotation	/** 回転		 */
			);

			/** 数字を設定 */
			void SetNumber(const int number) { m_requestNumber = number; }

			/** スプライトレンダーのリストを取得 */
			std::vector<SpriteRender*>& GetSpriteRenderList() { return m_renderList; }

			/** スプライトレンダーのリストに対して関数を実行 */
			void ForEach(const std::function<void(SpriteRender*)>& func)
			{
				for (auto* render : m_renderList) {
					func(render);
				}
			}


		private:
			/** 指定した桁の数字を更新する */
			void UpdateNumber(const int targetDigit, const int number);

			/** 指定した桁の位置を更新する */
			void UpdatePosition(const int index);

			/** 指定した桁の数字を取得する */
			int GetDigit(int digit);
		};




		/********************************/


		/**
		 * 絵を書くキャンバスのイメージ
		 * ※UIを作るときにこのクラスを作ること
		 */
		class UICanvas : public UIBase
		{
			friend class UIBase;
			friend class UIImage;
			friend class UIGauge;
			friend class UIIcon;
			friend class UIText;
			friend class UIButton;


		private:
			/**
			 * NOTE: 各UI自体に親子関係持たせたいけど使わない可能性があるので、一旦ここだけにしてみる
			 */
			std::vector<UIBase*> m_uiList;


		public:
			UICanvas();
			~UICanvas();


			bool Start();
			void Update();
			void Render(RenderContext& rc);


		public:
			/** UIの生成 */
			template <typename T>
			T* CreateUI()
			{
				T* ui = new T();
				ui->m_transform.SetParent(&m_transform);
				m_uiList.push_back(ui);
				return ui;
			}
		};
	}
}