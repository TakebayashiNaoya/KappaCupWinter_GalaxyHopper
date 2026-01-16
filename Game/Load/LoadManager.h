#pragma once

namespace app
{
	class LoadManager
	{
	public:
		/**
		 * ロード画面の状態
		 */
		enum class EnState : uint8_t
		{
			Closing,
			Loading,
			Opening,
			Opened,
			None
		};

		/**
		 * ロードを開始させる
		 */
		static void StartLoading();

		/**
		 * ロードを終了させる
		 */
		static void FinishLoading();

		/**
		 * ロード状態を強制的にロード中のレイアウトに変更し、全ての音を停止する
		 */
		void SnapToLoading();

		/**
		 * ロード状態を強制的にロード完了のレイアウトに変更する
		 */
		void SnapToOpened();

		/**
		 * ロード状態を強制的に変更する
		 */
		static void ChangeState(EnState state);

		/**
		 * ロード画面の状態を取得する
		 */
		static const EnState GetState();


	private:
		/** ロード画面を構成する画像パーツ */
		enum EnImageParts :uint8_t
		{
			enImageParts_Center,	/** 中央 */
			enImageParts_Top,		/** 上　 */
			enImageParts_Bottom,	/** 下　 */
			enImageParts_Left,		/** 左　 */
			enImageParts_Right,		/** 右　 */
			enImageParts_Num
		};


	private:
		/** 画像リスト */
		SpriteRender* m_displayImages = nullptr;
		/** ローディングアイコン */
		SpriteRender m_loadingIcon;
		/** ロード状態 */
		EnState m_state = EnState::None;
		/** アニメーション用タイマー */
		float m_timer = 0.0f;


	private:
		LoadManager();
		~LoadManager();


	public:
		bool Start();
		void Update();
		void Render(RenderContext& rc);


	private:
		/**
		 * レイアウトの初期化
		 */
		void InitLayout();

		/**
		 * アイリスイン・アイリスアウト時の各画像の大きさ・座標を更新する
		 * 引数が0.0fで閉じた状態、1.0fで開いた状態
		 */
		void UpdateIrisTransform(float ratio);

		/**
		 * アニメーションの更新
		 * startRatio～endRatioまでduration秒かけて変化させ、nextStateに遷移する
		 */
		void UpdateAnimation(float startRatio, float endRatio, float duration, EnState nextState);


		/**
		 * シングルトン関連
		 */
	private:
		static LoadManager* m_instance;

	public:
		static LoadManager* CreateInstance()
		{
			if (m_instance == nullptr) {
				m_instance = new LoadManager();
			}
			return m_instance;
		}
		static LoadManager* GetInstance()
		{
			return m_instance;
		}
		static bool GetIsAvailable()
		{
			return m_instance != nullptr;
		}
		static void Delete()
		{
			if (m_instance != nullptr) {
				delete m_instance;
				m_instance = nullptr;
			}
		}
	};




	/********************************/


	class LoadManagerObject : public IGameObject
	{
	public:
		LoadManagerObject();
		~LoadManagerObject();


	private:
		bool Start() override;
		void Update() override;
		void Render(RenderContext& rc) override;
	};
}