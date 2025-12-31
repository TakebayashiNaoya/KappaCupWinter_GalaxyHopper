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
			/**
			 * アニメーションクリップ
			 * 初期化時とIStateでアニメ再生に使用するのでpublicにしています。
			 */
			enum EnAnimationClip : uint8_t
			{
				enAnimationClip_Idle,	/** 待機 */
				enAnimationClip_Walk,	/** 歩き */
				enAnimationClip_Run,	/** 走り */
				enAnimationClip_Dead,	/** 死亡 */
				enAnimationClip_Num,
			};


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