/**
 * BossEnemy.h
 * ボスエネミーを管理するクラス
 */
#pragma once
#include "Source/Actor/Character/Enemy/Enemy.h"


namespace app
{
	namespace actor
	{
		class BossEnemy : public Enemy
		{
		public:
			BossEnemy();
			~BossEnemy();


		public:
			/**
			 * ボスエネミーのアニメーションクリップ
			 */
			enum class EnBossEnemyAnimClip : uint8_t
			{
				Idle,	/** 待機 */
				Walk,	/** 歩き */
				Dash,	/** 走り */
				Attack,	/** 攻撃 */
				Damage,	/** 被弾 */
				Die,	/** 死亡 */
				Num,
			};


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