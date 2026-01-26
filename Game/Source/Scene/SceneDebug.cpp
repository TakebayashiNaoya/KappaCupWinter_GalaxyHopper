/**
 * SceneDebug.h
 * デバッグの実装
 */
#include "stdafx.h"
#include "SceneDebug.h"
#include "Source/Actor/Character/Player/Player.h"
#include "Source/Actor/Character/Player/PlayerController.h"
#include "Source/Actor/Character/Player/PlayerStateMachine.h"
#include "Source/Actor/Environment/Tree.h"


namespace app
{
	namespace scene
	{
		SceneDebug::SceneDebug()
		{
		}


		SceneDebug::~SceneDebug()
		{
		}


		bool SceneDebug::Start()
		{
			/** 当たり判定を可視化 */
			PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

			return true;
		}


		void SceneDebug::InitLevel()
		{
			m_levelRender.Init("Assets/modelData/stage/DebugPlanet/debugPlanet.tkl", [&](LevelObjectData& objData) {
				if (objData.EqualObjectName(L"debugPlanet")) {
					NewGO<DebugPlanet>(0, "DebugPlanet");
					return true;
				}
				if (objData.EqualObjectName(L"player")) {
					m_player = NewGO<actor::Player>(0, "Player");
					m_player->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				if (objData.EqualObjectName(L"object")) {
					auto tree = NewGO<actor::Tree>(0, "Tree");
					tree->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				return false;
				});
		}




		/**********************************************/


		DebugPlanet::DebugPlanet()
		{
			m_modelRender.Init("Assets/modelData/stage/DebugPlanet/debugPlanet.tkm");
			m_modelRender.SetPosition(Vector3::Zero);
			m_modelRender.SetScale(Vector3::One);
			m_modelRender.Update();
			physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
			physicsStaticObject.GetbtCollisionObject()->setCollisionFlags(enCollisionAttr_Ground);
		}


		DebugPlanet::~DebugPlanet()
		{
		}


		bool DebugPlanet::Start()
		{
			return true;
		}


		void DebugPlanet::Update()
		{
			m_modelRender.Update();
		}


		void DebugPlanet::Render(RenderContext& rc)
		{
			m_modelRender.Draw(rc);
		}
	}
}
