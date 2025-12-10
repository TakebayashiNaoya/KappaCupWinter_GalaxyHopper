/**
 * TitlePlanet.cpp
 * タイトル用の惑星クラス
 */
#include "stdafx.h"
#include "TitlePlanet.h"


TitlePlanet::TitlePlanet()
{
	InitModel("TitlePlanet/TitlePlanet");
}


void TitlePlanet::Update()
{
	m_transform.m_localRotation.AddRotationX(-0.005f);
	m_modelRender.SetRotation(m_transform.m_localRotation);
	m_modelRender.Update();
}