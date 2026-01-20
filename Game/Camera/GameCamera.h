/**
 * GameCamera.h
 * ゲーム内カメラの処理を行うクラス
 */
#pragma once
#include "camera/SpringCamera.h"


namespace app
{
	/** 前方宣言 */
	namespace actor { class Player; }


	namespace camera
	{
		/**
		 * インゲームゲームのカメラクラス
		 */
		class GameCamera : public IGameObject
		{
		public:
			/**
			 * 追従対象のプレイヤーを設定
			 */
			void SetTarget(actor::Player* target)
			{
				m_target = target;
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

			/** 追従対象のプレイヤー */
			actor::Player* m_target = nullptr;


		public:
			GameCamera();
			~GameCamera();


		private:
			bool Start() override final;
			void Update() override final;
		};
	}
}