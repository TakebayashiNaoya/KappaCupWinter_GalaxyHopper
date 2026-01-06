/**
 * BasicEnemy.cpp
 * 基本エネミーの実装
 */
#include "stdafx.h"
#include "BasicEnemy.h"
#include "Collision/CollisionManager.h"
#include "Source/Actor/ActorStatus.h"
#include "BasicEnemyStateMachine.h"


namespace app
{
	namespace actor
	{
		/** アニメーション設定 */
		const Character::AnimationOption BasicEnemy::BASIC_ENEMY_ANIMATION_OPTIONS[] = {
			AnimationOption { std::string("Wolf/idle"),	bool(true) },
			AnimationOption { std::string("Wolf/walk"),	bool(true) },
			AnimationOption { std::string("Wolf/run"),	bool(true) },
		};


		namespace
		{
			const std::string MODEL_PATH = "Wolf/wolf";
			constexpr float MODEL_SCALE = 70.0f;

			constexpr float HIT_COLLIDER_RADIUS = 50.0f;					/** 当たりコライダーのサイズ */
			constexpr float HURT_COLLIDER_RADIUS = 100.0f;					/** やられコライダーのサイズ */
			constexpr float COLLIDER_OFFSET = 50.0f;						/** コライダーのオフセット値 */
		}


		BasicEnemy::BasicEnemy()
		{
			/** アニメーション数チェック */
			static_assert(ARRAYSIZE(BASIC_ENEMY_ANIMATION_OPTIONS) == static_cast<uint8_t>(EnBasicEnemyAnimClip::Num),
				"アニメーションのファイル数とクリップ数が合っていません。");

			/** BasicEnemyStatus型でステータス生成 */
			auto status = CreateStatus<BasicEnemyStatus>();

			/** ステートマシン生成 */
			m_stateMachine = std::make_unique<BasicEnemyStateMachine>(this, status.get());

			/** ステータスをムーブして保持 */
			m_status = std::move(status);
		}


		BasicEnemy::~BasicEnemy()
		{
		}


		bool BasicEnemy::Start()
		{
			/** BasicEnemyStatusにキャストする */
			auto status = GetStatus<BasicEnemyStatus>();

			/** モデルとアニメーションを初期化 */
			InitModel(static_cast<uint8_t>(EnBasicEnemyAnimClip::Num), BASIC_ENEMY_ANIMATION_OPTIONS, MODEL_PATH, status->GetModelScale());

			/** 攻撃判定のコライダーを作成 */
			m_hitCollider = collision::CollisionHitManager::GetInstance()->CreateCollider(
				this,
				collision::EnCollisionType::BasicEnemy,
				status->GetHitRadius(),
				EnCollisionAttr::enCollisionAttr_Enemy
			);

			/** やられ判定のコライダーを作成 */
			m_hurtCollider = collision::CollisionHitManager::GetInstance()->CreateCollider(
				this,
				collision::EnCollisionType::BasicEnemy,
				status->GetHurtRadius(),
				EnCollisionAttr::enCollisionAttr_Enemy
			);

			m_modelRender.Update();
			return true;
		}


		void BasicEnemy::Update()
		{
			/** キャラクター共通の更新処理を呼び出す */
			Character::Update();
		}


		void BasicEnemy::Render(RenderContext& rc)
		{
			m_modelRender.Draw(rc);
		}
	}
}