/**
 * Actor.h
 * 見た目が存在するゲームオブジェクトの基底クラス
 */
#include "stdafx.h"
#include "Actor.h"
 /** ステートマシンとステータスをdeleteするために必要 */
#include "Source/Actor/ActorStateMachine.h"
#include "Source/Actor/ActorStatus.h"


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
	}
}