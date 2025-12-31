/**
 * TitlePlanet.cpp
 * タイトル用の惑星クラス
 */
#include "stdafx.h"
#include "TitlePlanet.h"


namespace app
{
	namespace actor
	{
		TitlePlanet::TitlePlanet()
		{
			InitModel("TitlePlanet/TitlePlanet");
		}


		void TitlePlanet::Update()
		{
			m_transform.m_rotation.AddRotationX(-0.005f);
			m_modelRender.SetRotation(m_transform.m_rotation);
			m_modelRender.Update();
		}
	}
}