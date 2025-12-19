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