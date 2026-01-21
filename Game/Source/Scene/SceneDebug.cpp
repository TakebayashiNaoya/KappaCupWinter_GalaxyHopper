/**
 * SceneDebug.h
 * デバッグの実装
 */
#include "stdafx.h"
#include "SceneDebug.h"
#include "Source/Actor/Character/Player/Player.h"
#include "Source/Actor/Character/Player/PlayerController.h"
#include "Source/Actor/Character/Player/PlayerStateMachine.h"


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

			/** デバッグ用の地面を生成 */
			NewGO<DebugPlanet>(0, "DebugPlanet");

			/** プレイヤーを生成 */
			m_player = NewGO<actor::Player>(0, "Player");
			m_player->SetTransform(Vector3(0.0f, 2000.0f, 0.0f), Quaternion::Identity, Vector3::One);

			return true;
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
