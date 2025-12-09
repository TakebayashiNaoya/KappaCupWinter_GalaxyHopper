/**
 * PlanetBase.cpp
 * ˜f¯‚ÌŠî’êƒNƒ‰ƒX
 */
#include "stdafx.h"
#include "PlanetBase.h"


void PlanetBase::InitModel(const std::string filePath)
{
	std::string fullFilePath = "Assets/modelData/stage/" + filePath + ".tkm";
	m_modelRender.Init(fullFilePath.c_str());
	m_modelRender.SetTRS(m_transform.m_localPosition, m_transform.m_localRotation, m_transform.m_localScale);
	m_modelRender.Update();
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	physicsStaticObject.GetbtCollisionObject()->setCollisionFlags(enCollisionAttr_Ground);
}


PlanetBase::PlanetBase()
{
}


PlanetBase::~PlanetBase()
{
}


void PlanetBase::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}