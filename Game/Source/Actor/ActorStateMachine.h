/**
 * ActorStateMachine.h
 * Actor専用のステートマシン
 */
#pragma once
#include "Core/StateMachineBase.h"
#include "Source/Actor/Actor.h"


namespace app
{
	namespace actor
	{
		/** 前方宣言 */
		class ActorStatus;


		/**
		 * Actor用ステートマシン
		 */
		class ActorStateMachine : public core::StateMachineBase
		{
		public:
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
			 * 上方向ベクトルの取得
			 */
			inline const Vector3& GetUpDirection() const { return m_upDirection; }
			/**
			 * 上方向ベクトルの設定
			 */
			inline void SetUpDirection(const Vector3& upDir) { m_upDirection = upDir; }


		public:
			/**
			 * アニメーション再生処理のテンプレート関数
			 */
			template <typename TEnum>
			void PlayAnimation(TEnum animId)
			{
				m_actor->GetModelRender()->PlayAnimation(static_cast<int>(animId));
			}


		public:
			ActorStateMachine(Actor* actor, ActorStatus* status)
				: m_actor(actor)
				, m_actorStatus(status)
			{
			}
			virtual ~ActorStateMachine() {}


		protected:
			/** 操作対象のActor */
			Actor* m_actor = nullptr;
			/** Actor共通のステータス */
			ActorStatus* m_actorStatus = nullptr;
			/** トランスフォーム */
			Transform m_transform;
			/** 上方向ベクトル */
			Vector3 m_upDirection = Vector3::Up;
		};
	}
}