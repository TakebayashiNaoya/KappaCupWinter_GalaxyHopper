/**
 * ActorStateMachine.h
 * Actor専用のステートマシン
 */
#pragma once
#include "Core/StateMachineBase.h"
#include "Core/Transform.h"
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
			inline core::Transform& GetTransform() { return m_transform; }
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


			/**
			 * IState用の関数群
			 */
		public:
			/**
			 * アニメーション再生処理のテンプレート関数
			 */
			template <typename TEnum>
			void PlayAnimation(TEnum animId)
			{
				m_ownerActor->GetModelRender()->PlayAnimation(static_cast<int>(animId));
			}
			/**
			 * キャラクターを取得する関数
			 * NOTE:オーナーは派生先のステートマシンごとに決まっているはず
			 *		派生先でオーバーライドし、適切な型にstatic_castして返すように実装する
			 */
			virtual Actor* GetOwner() const = 0;
			/**
			 * オーナーを経由してステータスを取得する関数
			 * NOTE:ステータスは派生先のステートマシンごとに決まっているはず
			 *		派生先でオーバーライドし、適切な型にstatic_castして返すように実装する
			 */
			virtual ActorStatus* GetStatus() const = 0;


		public:
			/** 派生先のステートマシンが生成されたとき、その持ち主をキャッシュする */
			ActorStateMachine(Actor* actor)
				: m_ownerActor(actor)
			{
			}
			virtual ~ActorStateMachine() {}


		protected:
			/** 持ち主となるActor */
			Actor* m_ownerActor = nullptr;
			/** トランスフォーム */
			core::Transform m_transform;
			/** 上方向ベクトル */
			Vector3 m_upDirection = Vector3::Up;
		};
	}
}