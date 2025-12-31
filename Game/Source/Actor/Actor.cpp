/**
 * Actor.h
 * 見た目が存在するゲームオブジェクトの基底クラス
 */
#include "stdafx.h"
#include "Actor.h"
#include "StateMachineBase.h"


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
			if (m_stateMachine) {
				m_stateMachine->Update();
			}
		}


		void Actor::Render(RenderContext& renderContect)
		{
		}
	}
}