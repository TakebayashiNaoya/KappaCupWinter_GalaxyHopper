/**
 * Tree.cpp
 * 木のクラスの実装
 */
#include "stdafx.h"
#include "Collision/CollisionManager.h"
#include "Tree.h"


namespace app
{
	namespace actor
	{
		namespace
		{
			float RADIUS = 100.0f;
			float HEIGHT = 500.0f;
		}


		Tree::~Tree()
		{
			delete m_collider;
			m_collider = nullptr;
		}


		bool Tree::Start()
		{
			/** モデルの初期化 */
			InitModel("Tree/tree");

			/** 当たり判定を作成 */
			m_collider = new CollisionObject();
			m_collider->CreateCapsule(
				m_transform.m_position,
				m_transform.m_rotation,
				RADIUS,
				HEIGHT
			);

			/** 当たり判定を地面に識別 */
			m_collider->GetbtCollisionObject().setUserIndex(enCollisionAttr_Ground);
			m_collider->GetbtCollisionObject().setCollisionFlags(enCollisionAttr_Ground);

			return true;
		}
	}
}
