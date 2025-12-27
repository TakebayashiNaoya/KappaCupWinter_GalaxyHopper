/**
 * TitleCamera.h
 * タイトルカメラ処理
 */
#pragma once


namespace app
{
	namespace camera
	{
		class TitleCamera : public IGameObject
		{
		public:
			/**
			 * カメラのターゲット座標を設定する
			 */
			void SetTargetPosition(const Vector3& position)
			{
				m_targetPos = position;
			}


		private:
			/** 注視点から視点までのベクトル */
			Vector3 m_toCameraPos = Vector3::Zero;
			/** カメラの座標 */
			Vector3 m_cameraPos = Vector3::Zero;
			/** ターゲットの座標 */
			Vector3 m_targetPos = Vector3::Zero;


		private:
			bool Start() override final;
			void Update() override final;
		};
	}
}