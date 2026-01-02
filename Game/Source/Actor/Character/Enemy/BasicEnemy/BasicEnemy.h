/**
 * BasicEnemy.h
 * 基本エネミーを管理するクラス
 */
#pragma once
#include "Source/Actor/Character/Enemy/Enemy.h"


namespace app
{
	namespace actor
	{
		class BasicEnemy : public Enemy
		{
		public:
			BasicEnemy();
			~BasicEnemy();


		private:
			/** アニメーションクリップのオプション配列 */
			static const Character::AnimationOption BASIC_ENEMY_ANIMATION_OPTIONS[];


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;
		};
	}
}