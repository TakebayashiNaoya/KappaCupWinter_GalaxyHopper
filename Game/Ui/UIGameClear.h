/**
 * UIGameClear.h
 * ゲームクリアUI
 */
#pragma once
#include "UIResultBase.h"


namespace app
{
	namespace ui
	{
		class UIGameClear : public UIResultBase
		{
		private:
			enum enState : uint8_t
			{
				enState_JumpArc,		/** ロゴがジャンプして着地するまでのステート */
				enState_Bouncing,		/** 着地点でバウンドするステート */
				enState_Wait,			/** 待機 */
				enState_Shrink,			/** 収縮 */
				enState_LoadingWait,	/** ローディング待ち */
				enState_End,			/** 終了 */
			};

		public:
			UIGameClear();
			~UIGameClear();

		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;

		private:
			SpriteRender m_gameClearImage;

			Vector3 m_position = Vector3::Zero;
			Vector3 m_scale = Vector3::One;
			float m_alpha = 0.0f;

			Quaternion m_rotation = Quaternion::Identity;
			float m_angle = 0.0f; // 現在の角度（ラジアン）

			// 物理演算用
			Vector3 m_velocity = Vector3::Zero; // 3次元の速度

			float m_timer = 0.0f;
			uint8_t m_state = 0;
		};
	}
}