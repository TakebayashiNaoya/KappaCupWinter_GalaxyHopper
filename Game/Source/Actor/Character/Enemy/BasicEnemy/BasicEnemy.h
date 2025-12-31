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
			/**
			 * アニメーションクリップ
			 * 初期化時とIStateでアニメ再生に使用するのでpublicにしています。
			 */
			enum EnAnimationClip : uint8_t
			{
				enAnimationClip_Idle,	/** 待機 */
				enAnimationClip_Walk,	/** 歩き */
				enAnimationClip_Run,	/** 走り */
				enAnimationClip_Num,
			};


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