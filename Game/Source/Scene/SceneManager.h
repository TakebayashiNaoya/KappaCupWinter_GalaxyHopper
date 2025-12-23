#pragma once

namespace app
{
	namespace scene
	{
		/**
		 * シーンのインターフェース。
		 */
		class IScene
		{
		public:
			IScene() {};
			/** デストラクタにvirtualを付けることで、仮想関数テーブルに登録され、実体（派生先）のデストラクタが呼ばれるようになる */
			virtual~IScene() {};

			virtual bool Start() = 0;
			virtual void Update() = 0;
		};


		/**
		 * シーンの登録・呼び出しに使うID
		 */
		enum class SceneID : uint8_t
		{
			Title = 0,
			FirstStage,
			BossStage,
			None = 0xff	/** 0xで16進数。ffは10進数で255 */
		};


		/**
		 * シーンの管理者。
		 * シーン切り替え・更新の提供を行う。
		 */
		class SceneManager
		{
		private:
			/** 現在のシーン */
			IScene* m_currentScene = nullptr;
			/** 現在のシーンID */
			SceneID m_currentID = SceneID::Title;
			/** シーン切り替えリクエストID */
			SceneID m_requestID = SceneID::Title;


		public:
			/** シーンマネージャーオブジェクトで呼び出すためpublic */
			void Update();

			/** シーン切り替えをリクエスト */
			void ChangeScene(SceneID nextID)
			{
				m_requestID = nextID;
			};

			/**
			 * シーン切り替えがリクエストされているかチェック。
			 */
			bool GetIsSceneChangeRequested() const
			{
				return m_requestID != SceneID::None;
			}


		private:
			SceneManager() {};
			~SceneManager() {};


		private:
			static SceneManager* m_instance;
		public:
			static void CreateInstance()
			{
				if (!m_instance) {
					m_instance = new SceneManager();
				}
			};
			static SceneManager* GetInstance()
			{
				return m_instance;
			};
			static void DeleteInstance()
			{
				if (m_instance) {
					delete m_instance;
					m_instance = nullptr;
				}
			};
		};


		/**
		 * シーンマネージャーを更新したりするためのゲームオブジェクト
		 */
		class SceneManagerObject : public IGameObject
		{
		public:
			SceneManagerObject();
			~SceneManagerObject();


		private:
			bool Start() override;
			void Update() override;
		};
	}
}