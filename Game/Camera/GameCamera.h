/**
 * GameCamera.h
 * ゲーム内カメラの処理を行うクラス
 */
#pragma once
#include "camera/SpringCamera.h"


namespace app
{
	namespace camera
	{
		class GameCamera : public IGameObject
		{
		public:
			/**
			 * カメラの追従対象の情報を設定する
			 * ・追従対象の座標（Vector3）
			 * ・追従対象の上方向ベクトル（Vector3）
			 * ・追従対象の速度ベクトル（Vector3）
			 */
			void SetTargetInfo(const Vector3& position, const Vector3& upDirection, const Vector3& velocity)
			{
				m_targetPos = position;
				m_targetUp = upDirection;
				m_targetVelocity = velocity;
			}


		private:
			/** スプリングカメラ */
			SpringCamera m_springCamera;
			/** 1フレーム前の上方向 */
			Vector3 m_prevTargetUp = Vector3::Up;
			/** 注視点から視点までのベクトル */
			Vector3 m_toCameraPos = Vector3::Zero;
			/** カメラの座標 */
			Vector3 m_cameraPos = Vector3::Zero;

			/** 追従対象の座標 */
			Vector3 m_targetPos = Vector3::Zero;
			/** 追従対象の上方向ベクトル */
			Vector3 m_targetUp = Vector3::Up;
			/** 追従対象の速度ベクトル */
			Vector3 m_targetVelocity = Vector3::Zero;


		public:
			GameCamera();
			~GameCamera();


		private:
			bool Start() override final;
			void Update() override final;
		};
	}
}