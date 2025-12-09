/**
 * FirstPlanet.h
 * Å‰‚Ì˜f¯‚ÌƒNƒ‰ƒX
 */
#pragma once
#include "PlanetBase.h"


class FirstPlanet : public PlanetBase
{
public:
	FirstPlanet();
	~FirstPlanet();


private:
	void Update() override final;
};