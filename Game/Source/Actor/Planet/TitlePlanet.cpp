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
			/** トランスフォームを初期化 */
			m_transform.m_position = Vector3::Zero;
			m_transform.m_scale = Vector3::One;
			/** モデルを初期化 */
			InitModel("TitlePlanet/TitlePlanet");
		}


		void TitlePlanet::Update()
		{
			/** 惑星をゆっくり回転させる */
			m_transform.m_rotation.AddRotationX(-0.005f);
			m_modelRender.SetRotation(m_transform.m_rotation);
			m_modelRender.Update();
		}
	}
}