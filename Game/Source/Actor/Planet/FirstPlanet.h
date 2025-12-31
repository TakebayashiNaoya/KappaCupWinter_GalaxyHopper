/**
 * FirstPlanet.h
 * Å‰‚Ì˜f¯‚ÌƒNƒ‰ƒX
 */
#pragma once
#include "PlanetBase.h"


namespace app
{
	namespace actor
	{
		class FirstPlanet : public PlanetBase
		{
		public:
			FirstPlanet();
			~FirstPlanet() {};


		private:
			void Update() override final {};
		};
	}
}