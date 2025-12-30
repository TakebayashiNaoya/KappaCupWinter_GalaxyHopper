/**
 * BossEnemy.h
 * ボスエネミーを管理するクラス
 */
#pragma once
#include "Enemy.h"
#include "ActorStatus.h" 
#include "EnemyStateMachine.h"


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

			/** ボスエネミーステートマシンの取得 */
			BossEnemyStateMachine* GetStateMachine() const { return m_stateMachine.get(); }

			/** ボスエネミーステータスの取得 */
			BossEnemyStatus* GetStatus() const { return m_status.get(); }


		public:
			///// <summary>
			///// アニメーションイベントを処理します。
			///// </summary>
			//void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName) override final;


		public:
			BossEnemy();
			~BossEnemy();


		private:
			// ボスエネミーのステートマシン。
			std::unique_ptr<BossEnemyStateMachine> m_stateMachine;
			/** ステータス */
			std::unique_ptr<BossEnemyStatus> m_status;


			// クラススコープで宣言し、cppで定義。
			static const Character::AnimationOption BOSS_ENEMY_ANIMATION_OPTIONS[];


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;
		};
	}
}