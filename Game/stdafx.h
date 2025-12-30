#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "k2EnginePreCompile.h"
using namespace nsK2EngineLow;
using namespace nsK2Engine;

//#include "Types.h"
#include "json/json.hpp"

#include "Transform.h"
#include "Sound/SoundManager.h"
#include "Battle/BattleManager.h"

//#include "core/Fade.h"

namespace app
{
	enum EnCollisionAttr : uint8_t
	{
		enCollisionAttr_Player = enCollisionAttr_User,
		enCollisionAttr_Enemy,
	};
}