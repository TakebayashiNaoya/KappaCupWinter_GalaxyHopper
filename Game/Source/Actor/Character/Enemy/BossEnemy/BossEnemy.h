/**
 * BossEnemy.h
 * ボスエネミーを管理するクラス
 */
#pragma once
#include "Source/Actor/Character/Enemy/Enemy.h"
#include "Source/Actor/ActorStatus.h" 
#include "Source/Actor/Character/Enemy/EnemyStateMachine.h"


namespace app
{
	namespace actor
	{
		class BossEnemy : public Enemy
		{
		public:
			BossEnemy();
			~BossEnemy();


		private:
			/** アニメーションクリップのオプション配列 */
			static const Character::AnimationOption BOSS_ENEMY_ANIMATION_OPTIONS[];


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;

			/** アニメーションイベント */
			void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
		};
	}
}