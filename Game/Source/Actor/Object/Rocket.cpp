/**
 * Rocket.cpp
 * ロケットクラスの実装
 */
#include "stdafx.h"
#include "Rocket.h"


namespace app
{
	namespace actor
	{
		Rocket::Rocket()
		{
			/** バトルマネージャーに登録 */
			if (battle::BattleManager::GetInstance()) {
				battle::BattleManager::GetInstance()->Register(this);
			}
		}


		Rocket::~Rocket()
		{
			/** バトルマネージャーから登録解除 */
			if (battle::BattleManager::GetInstance()) {
				battle::BattleManager::GetInstance()->Unregister(this);
			}
		}


		bool Rocket::Start()
		{
			m_modelRender.Init("Assets/modelData/Object/Rocket/rocket.tkm");
			m_transform.m_scale = Vector3(200.0f, 200.0f, 200.0f);
			m_modelRender.SetTRS(m_transform.m_position, m_transform.m_rotation, m_transform.m_scale);
			m_modelRender.Update();
			return true;
		}


		void Rocket::Update()
		{
		}


		void Rocket::Render(RenderContext& rc)
		{
			m_modelRender.Draw(rc);
		}
	}
}