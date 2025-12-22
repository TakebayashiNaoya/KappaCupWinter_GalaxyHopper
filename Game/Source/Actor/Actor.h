/**
 * Actor.h
 * 見た目が存在するゲームオブジェクトの基底クラス
 */
#pragma once
#include "ActorStatus.h"


namespace app
{
	namespace actor
	{
		class Actor : public IGameObject
		{
		public:
			/**
			 * モデル描画機能を取得
			 */
			ModelRender* GetModelRender() { return &m_modelRender; }

			/**
			 * ステータスを取得する
			 */
			template<typename TStatus>
			TStatus* GetStatus() { return dynamic_cast<TStatus*>(m_status); }

			/**
			 * トランスフォームを取得
			 */
			inline Transform& GetTransform() { return m_transform; }

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


		protected:
			/** モデル描画 */
			ModelRender m_modelRender;
			/** トランスフォーム */
			Transform m_transform;
			/** 上方向ベクトル */
			Vector3 m_upDirection = Vector3::Up;
			/** ステータス */
			ActorStatus* m_status = nullptr;


		protected:
			/**
			 * 「惑星の中心→キャラ」のベクトルを計算し、正規化します。
			 * ※派生先クラスのUpdate関数内で、StateMachineのUpdate関数を呼ぶ前に実行してください。
			 */
			void UpdateUpDirection();


		public:
			Actor();
			~Actor();


		protected:
			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& renderContect) override;
		};
	}
}