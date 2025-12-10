/**
 * BossPlanet.h
 * ボス用の惑星クラス
 */
#pragma once
#include "PlanetBase.h"


class BossPlanet : public PlanetBase
{
public:
	BossPlanet();
	~BossPlanet() {};


private:
	void Update() override final {};
};