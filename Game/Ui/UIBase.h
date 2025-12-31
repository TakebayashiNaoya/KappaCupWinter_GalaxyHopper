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
			/** CreateUIでの自身の生成を許可 */
			friend class UICanvas;


		protected:
			/** スプライトレンダー */
			SpriteRender m_spriteRender;


		protected:
			UIImage();
			virtual ~UIImage();


		public:
			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& rc) override;


		public:
			/** スプライトレンダーの取得 */
			SpriteRender* GetSpriteRender() { return &m_spriteRender; }

			/**
			 * 初期化
			 * ・アセットパス
			 * ・幅
			 * ・高さ
			 * ・座標
			 * ・拡大縮小（デフォルト: Vector3::One）
			 * ・回転（デフォルト: Quaternion::Identity）
			 */
			void Initialize(
				const char* assetPath,
				const float width,
				const float height,
				const Vector3& position,
				const Vector3& scale = Vector3::One,
				const Quaternion& rotation = Quaternion::Identity
			);
		};




		/********************************/


		/**
		 * 文字を使うUIの基本クラス
		 */
		class UIText : public UIBase
		{
			/** CreateUIでの自身の生成を許可 */
			friend class UICanvas;


		protected:
			FontRender m_fontRender;


		private:
			UIText();
			~UIText();


		public:
			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& rc) override;


		public:
			/** フォントレンダーの取得 */
			FontRender* GetFontRender() { return &m_fontRender; }

			/**
			 * 初期化
			 * ・初期表示するテキスト（"0/3" など）
			 * ・座標
			 * ・大きさ
			 * ・色
			 * ・回転（デフォルト: Quaternion::Identity）
			 */
			void Initialize(
				const wchar_t* text,
				const Vector3& position,
				const float scale,
				const Vector4& color,
				const Quaternion& rotation = Quaternion::Identity
			);

			/**
			 * テキストを設定・更新する
			 * 例: uiText->SetText(L"%d/%d", current, max);
			 */
			void SetText(const wchar_t* format, ...);
		};




		/********************************/


		/**
		 * 画像を使って数字を表示するUIの基本クラス
		 */
		class UIDigit : public UIBase
		{
			/** CreateUIでの自身の生成を許可 */
			friend class UICanvas;


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
			/**
			 * 初期化
			 * ・アセットパス
			 * ・桁数
			 * ・表示したい値
			 * ・幅
			 * ・高さ
			 * ・座標
			 * ・拡大縮小（デフォルト: Vector3::One）
			 * ・回転（デフォルト: Quaternion::Identity）
			 */
			void Initialize(
				const char* assetPath,								/** アセットパス */
				const int digit,									/** 桁数		 */
				const int number,									/** 表示したい値 */
				const float widht,									/** 幅			 */
				const float height,									/** 高さ		 */
				const Vector3& position,							/** 座標		 */
				const Vector3& scale = Vector3::One,				/** 拡大縮小	 */
				const Quaternion& rotation = Quaternion::Identity	/** 回転		 */
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
		private:
			/** 描画するUIのリスト */
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