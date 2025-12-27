/**
 * TitleCamera.cpp
 * タイトルカメラ実装
 */
#include "stdafx.h"
#include "TitleCamera.h"
#include "Source/Scene/SceneManager.h"


namespace app
{
	namespace camera
	{
		namespace
		{
			const Vector3 TARGET_OFFSET = Vector3(100.0f, 100.0f, 100.0f);
			const Vector3 CAMERA_OFFSET = Vector3(-200.0f, 100.0f, 200.0f);
		}

		bool TitleCamera::Start()
		{
			// 注視点から視点までのベクトルを設定。
			// ※Update内でCAMERA_OFFSET定数が使われているため、この変数が実際に使われているか確認してください
			m_toCameraPos.Set(-300.0f, 500.0f, 300.0f);

			g_camera3D->SetNear(1.0f);
			g_camera3D->SetFar(20000.0f);

			return true;
		}

		void TitleCamera::Update()
		{
			// シーン切り替え中は更新しない。
			if (scene::SceneManager::GetInstance()->GetIsSceneChangeRequested()) {
				return;
			}

			// セッターで受け取った座標を使用
			Vector3 playerPos = m_targetPos;

			m_cameraPos = playerPos + CAMERA_OFFSET;
			Vector3 target = playerPos + TARGET_OFFSET;

			g_camera3D->SetPosition(m_cameraPos);
			g_camera3D->SetTarget(target);
			g_camera3D->SetUp(Vector3::Up);
			g_camera3D->Update();
		}
	}
}