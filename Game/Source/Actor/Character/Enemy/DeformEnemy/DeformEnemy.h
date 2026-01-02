/**
 * DeformEnemy.h
 * 変形エネミーを管理するクラス
 */
#pragma once
#include "Source/Actor/Character/Enemy/Enemy.h"


namespace app
{
	namespace actor
	{
		class DeformEnemy : public Enemy
		{
		public:
			DeformEnemy();
			~DeformEnemy();


		private:
			/** アニメーションクリップのオプション配列 */
			static const Character::AnimationOption TRANSFORM_ENEMY_ANIMATION_OPTIONS[];


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;
		};
	}
}