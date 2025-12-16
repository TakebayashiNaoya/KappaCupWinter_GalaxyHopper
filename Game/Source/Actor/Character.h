/**
 * Character.h
 * キャラクターとなる要素をもったクラス
 */
#pragma once
#include "Actor.h"


class CharacterStatus;


namespace app
{
	namespace actor
	{
		class Character : public Actor
		{
		protected:
			/** アニメーションクリップのリスト */
			std::vector<AnimationClip*> m_animationClipList;

			/** やられ判定 */
			CollisionObject* m_hurtCollider = nullptr;
			/** 体の当たり判定 */
			CollisionObject* m_bodyHitCollider = nullptr;
			/** 一時的な攻撃判定 */
			CollisionObject* m_attackHitCollider = nullptr;


		public:
			Character();
			~Character();


		protected:
			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& renderContect) override;


		public:
			/** キャラクターステータスの取得 */
			CharacterStatus* GetStatus()
			{
				return dynamic_cast<CharacterStatus*>(m_status);
			}
		};
	}
}