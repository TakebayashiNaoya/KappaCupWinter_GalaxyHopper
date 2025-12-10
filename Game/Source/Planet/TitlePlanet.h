/**
 * TitlePlanet.h
 * タイトル用の惑星クラス
 */
#pragma once
#include "PlanetBase.h"


class TitlePlanet : public PlanetBase
{
public:
	TitlePlanet();
	~TitlePlanet() {};


private:
	void Update() override final;
};

