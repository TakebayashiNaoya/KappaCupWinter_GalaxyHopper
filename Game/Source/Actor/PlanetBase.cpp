/**
 * PlanetBase.cpp
 * 惑星の基底クラス
 */
#include "stdafx.h"
#include "PlanetBase.h"


namespace app
{
	namespace actor
	{
		void PlanetBase::InitModel(const std::string filePath)
		{
			std::string fullFilePath = "Assets/modelData/stage/" + filePath + ".tkm";
			m_modelRender.Init(fullFilePath.c_str());
			m_modelRender.SetTRS(m_transform.m_position, m_transform.m_rotation, m_transform.m_scale);
			m_modelRender.Update();
			physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
			physicsStaticObject.GetbtCollisionObject()->setCollisionFlags(enCollisionAttr_Ground);
		}


		void PlanetBase::Render(RenderContext& rc)
		{
			m_modelRender.Draw(rc);
		}
	}
}