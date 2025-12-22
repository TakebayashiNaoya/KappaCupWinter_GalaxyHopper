/**
 * Actor.h
 * 見た目が存在するゲームオブジェクトの基底クラス
 */
#include "stdafx.h"
#include "Actor.h"


namespace app
{
	namespace actor
	{
		void Actor::UpdateUpDirection()
		{
			Vector3 planetCenter = Vector3::Zero;
			m_upDirection = m_transform.m_position - planetCenter;
			m_upDirection.Normalize();
		}


		Actor::Actor()
		{
		}


		Actor::~Actor()
		{
		}


		bool Actor::Start()
		{
			return true;
		}


		void Actor::Update()
		{
		}


		void Actor::Render(RenderContext& renderContect)
		{
		}
	}
}