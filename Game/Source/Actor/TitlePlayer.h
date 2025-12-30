/**
 * TitlePlayer.h
 * タイトル用のプレイヤークラス
 */
#pragma once
#include "Player.h"


namespace app
{
	namespace camera
	{
		class TitleCamera;
	}

	namespace actor
	{
		class TitlePlayer : public Player
		{
		public:
			TitlePlayer();
			~TitlePlayer();


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;

			/** タイトルカメラ */
			camera::TitleCamera* m_titleCamera = nullptr;

			/** クラススコープで宣言し、cppで定義 */
			static const Character::AnimationOption TITLE_PLAYER_ANIMATION_OPTIONS[];

			/** アニメーションクリップ */
			AnimationClip m_animationClip;
		};
	}
}