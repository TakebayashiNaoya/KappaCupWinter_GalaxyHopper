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
			/**
			 * アニメーションクリップ
			 * 初期化時とIStateでアニメ再生に使用するのでpublicにしています。
			 */
			enum EnAnimationClip : uint8_t
			{
				enAnimationClip_Idle,	/** 待機		*/
				enAnimationClip_Walk,	/** 歩き		*/
				enAnimationClip_Run,	/** 走り		*/
				enAnimationClip_Attack,	/** 攻撃		*/
				enAnimationClip_Damage,	/** 被弾		*/
				enAnimationClip_Die,	/** 死亡		*/
				enAnimationClip_Num,
			};


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