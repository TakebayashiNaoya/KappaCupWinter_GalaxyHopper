/**
 * Actor.h
 * 見た目が存在するゲームオブジェクトの基底クラス
 */
#pragma once
#include "actorStatus.h"


namespace app
{
	namespace actor
	{
		/** 前方宣言 */
		class ActorStateMachine;
		class ActorStatus;


		/**
		 * 見た目が存在するゲームオブジェクトの基底クラス
		 */
		class Actor : public IGameObject
		{
		public:
			/**
			 * モデル描画機能を取得
			 */
			ModelRender* GetModelRender() { return &m_modelRender; }

			/**
			 * トランスフォームを取得
			 */
			inline Transform& GetTransform() { return m_transform; }

			/**
			 * トランスフォームを設定
			 */
			inline void SetTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
			{
				m_transform.m_position = position;
				m_transform.m_rotation = rotation;
				m_transform.m_scale = scale;
			}

			/**
			 * 座標を設定
			 */
			inline void SetPosition(const Vector3& position) { m_transform.m_position = position; }

			/**
			 * 回転を設定
			 */
			inline void SetRotation(const Quaternion& rotation) { m_transform.m_rotation = rotation; }

			/**
			 * 拡縮を設定
			 */
			inline void SetScale(const Vector3& scale) { m_transform.m_scale = scale; }

			/**
			 * 上方向ベクトルを取得
			 */
			inline const Vector3& GetUpDirection() const { return m_upDirection; }


		public:
			/**
			 * ステートマシンを取得するテンプレート関数
			 * 例: auto* sm = player->GetStateMachine<PlayerStateMachine>();
			 */
			template <typename T>
			T* GetStateMachine() const
			{
				T* casted = dynamic_cast<T*>(m_stateMachine.get());

				/** 中身があるのにキャストしたらnullptrになる場合、型指定が間違っている */
				if (m_stateMachine && !casted) {
					assert(false && "GetStateMachine: 型指定が間違っています");
				}
				return casted;
			}

			/**
			 * ステータスを取得するテンプレート関数
			 * 例: auto* status = player->GetStatus<PlayerStatus>();
			 */
			template <typename T>
			T* GetStatus() const
			{
				T* casted = dynamic_cast<T*>(m_status.get());

				/** 中身があるのにキャストしたらnullptrになる場合、型指定が間違っている */
				if (m_status && !casted) {
					assert(false && "GetStatus: 型指定が間違っています");
				}
				return casted;
			}


		protected:
			/**
			 * ユニークポインタを返すステータス生成関数
			 */
			template <typename TStatus>
			static std::unique_ptr<TStatus> CreateStatus()
			{
				auto status = std::make_unique<TStatus>();
				/**
				 * 万が一親クラスのコンストラクタでSetupを呼んだ場合、子クラスでオーバーライドしたSetupは機能しないため、
				 * 二段階初期化でSetupを呼び出す。
				 */
				status->Setup();
				return status;
			}


		protected:
			/** モデル描画 */
			ModelRender m_modelRender;
			/** トランスフォーム */
			Transform m_transform;
			/** 上方向ベクトル */
			Vector3 m_upDirection = Vector3::Up;
			/** ステートマシン */
			std::unique_ptr<ActorStateMachine> m_stateMachine;
			/** ステータス */
			std::unique_ptr<ActorStatus> m_status;


		public:
			Actor();
			~Actor();


		protected:
			virtual bool Start() override { return true; }
			virtual void Update() override {}
			virtual void Render(RenderContext& rc) override {};
		};
	}
}