/**
 * GameCamera.cpp
 * ゲームカメラ実装
 */
#include "stdafx.h"
#include "GameCamera.h"
#include "Source/Scene/SceneManager.h"


#if _DEBUG
#define AddjustConst
#else
#define AddjustConst const
#endif


namespace app
{
	namespace camera
	{
		namespace
		{
			AddjustConst float CAMERA_ROTATION_SPEED = 3.0f;
		}

		bool GameCamera::Start()
		{
			// 初期オフセット設定
			m_toCameraPos.Set(0.0f, 500.0f, -700.0f);

			m_springCamera.Init(
				*g_camera3D,		// ばねカメラ処理を行うカメラ
				2000.0f,			// 最大移動速度
				true,				// 地形判定を行うか
				5.0f				// 球体コリジョン半径
			);

			g_camera3D->SetNear(1.0f);
			g_camera3D->SetFar(20000.0f);

			return true;
		}

		void GameCamera::Update()
		{
			// シーン切り替え中やバトル終了時は更新しない
			if (scene::SceneManager::GetInstance()->GetIsSceneChangeRequested()) {
				return;
			}
			// ※BattleManagerの判定が必要なら、GameCamera自体を止めるか、呼び出し元で制御してください

			// 安全策：ターゲットの上方向が不正ならUpを入れておく
			if (m_targetUp.LengthSq() < 0.0001f) {
				m_targetUp = Vector3::Up;
			}
			// 初回更新時の対策（前回Upがゼロの場合）
			if (m_prevTargetUp.LengthSq() < 0.0001f) {
				m_prevTargetUp = m_targetUp;
			}


			// =================================================================
			// 1. 天体移動に伴うカメラの自動回転補正
			// =================================================================

			// 移動している場合のみ回転補正を行う
			if (m_targetVelocity.LengthSq() > 0.01f)
			{
				// A. 移動方向（Forward）
				Vector3 forward = m_targetVelocity;
				forward.Normalize();

				// B. 回転軸（Right）: 進行方向とUpベクトルの外積
				Vector3 rotateAxis;
				rotateAxis.Cross(m_targetUp, forward);
				rotateAxis.Normalize();

				// C. 回転角度: 前フレームのUpと今のUpのなす角
				float dot = m_prevTargetUp.Dot(m_targetUp);
				if (dot > 1.0f) {
					dot = 1.0f;
				}
				else if (dot < -1.0f) {
					dot = -1.0f;
				}
				float angle = acosf(dot);

				// D. 回転方向の判定
				Vector3 crossCheck;
				crossCheck.Cross(m_prevTargetUp, m_targetUp);
				if (crossCheck.Dot(rotateAxis) < 0.0f) {
					angle *= -1.0f;
				}

				// E. カメラオフセットに回転を適用
				Quaternion planetRot;
				planetRot.SetRotation(rotateAxis, angle);
				planetRot.Apply(m_toCameraPos);
			}

			// 現在のUpを保存（次フレーム用）
			m_prevTargetUp = m_targetUp;


			// =================================================================
			// 2. 右スティックによる任意回転
			// =================================================================
			float x = g_pad[0]->GetRStickXF();
			float y = g_pad[0]->GetRStickYF();

			if (fabsf(x) > 0.01f || fabsf(y) > 0.01f)
			{
				// 縦回転（X軸回転）用にカメラの横方向ベクトルを計算
				Vector3 cameraRight;
				cameraRight.Cross(m_targetUp, m_toCameraPos);
				cameraRight.Normalize();

				Quaternion rotY;
				rotY.SetRotationDeg(m_targetUp, CAMERA_ROTATION_SPEED * x); // 横回転

				Quaternion rotX;
				rotX.SetRotationDeg(cameraRight, CAMERA_ROTATION_SPEED * y); // 縦回転

				// 回転を適用
				rotY.Apply(m_toCameraPos);
				rotX.Apply(m_toCameraPos);
			}


			// =================================================================
			// 3. 座標計算・反映
			// =================================================================

			// 足元アンカー補正（必要なら有効化）
			Vector3 anchorPos = m_targetPos;
			/*
			Vector3 rayStart = m_targetPos + m_targetUp * 50.0f;
			Vector3 hitPos;
			// 地形判定を行い、地面があればそこを基準にするなどの処理
			if (PhysicsWorld::GetInstance()->RayTest(rayStart, Vector3::Zero, hitPos)) {
				// anchorPos = hitPos;
			}
			*/

			Vector3 desiredCameraPos = anchorPos + m_toCameraPos;
			Vector3 lookAtTarget = anchorPos + m_targetUp * 100.0f;

			m_cameraPos = desiredCameraPos;

			// カメラへの適用
			g_camera3D->SetUp(m_targetUp);
			m_springCamera.SetPosition(m_cameraPos);
			m_springCamera.SetTarget(lookAtTarget);
			m_springCamera.Update();
		}
	}
}