/**
 * DeformEnemy.cpp
 * 変形エネミーの実装
 */
#include "stdafx.h"
#include "DeformEnemy.h"
#include "Collision/CollisionManager.h"
#include "Source/Actor/ActorStatus.h"
#include "DeformEnemyStateMachine.h"


namespace app
{
	namespace actor
	{
		/** アニメーション設定 */
		const Character::AnimationOption DeformEnemy::TRANSFORM_ENEMY_ANIMATION_OPTIONS[] = {
		   AnimationOption { std::string("Spider/idle"),	bool(true) },
		   AnimationOption { std::string("Spider/walk"),	bool(true) },
		   AnimationOption { std::string("Spider/run"),		bool(true) },
		   AnimationOption { std::string("Spider/dead"),	bool(false) },
		};


		namespace
		{
			const std::string MODEL_PATH = "Spider/spider";
			constexpr float MODEL_SCALE = 30.0f;

			constexpr float HIT_COLLIDER_RADIUS = 40.0f;						/** 当たりコライダーのサイズ */
			constexpr float HURT_COLLIDER_RADIUS = 80.0f;						/** やられコライダーのサイズ */
			constexpr float COLLIDER_OFFSET = 30.0f;							/** コライダーのオフセット値 */
		}


		DeformEnemy::DeformEnemy()
		{
			/** アニメーション数チェック */
			static_assert(ARRAYSIZE(TRANSFORM_ENEMY_ANIMATION_OPTIONS) == static_cast<uint8_t>(EnDeformEnemyAnimClip::Num),
				"アニメーションのファイル数とクリップ数が合っていません。");

			/** DeformEnemyStatus型でステータスを生成 */
			auto status = CreateStatus<DeformEnemyStatus>();

			/** ステートマシン生成 */
			m_stateMachine = std::make_unique<app::actor::DeformEnemyStateMachine>(this, status.get());

			/** ステータス生成 */
			m_status = std::move(status);
		}


		DeformEnemy::~DeformEnemy()
		{
		}


		bool DeformEnemy::Start()
		{
			/** DeformEnemyStatusにキャストする */
			auto status = GetStatus<DeformEnemyStatus>();

			/** モデルとアニメーションを初期化 */
			InitModel(static_cast<uint8_t>(EnDeformEnemyAnimClip::Num), TRANSFORM_ENEMY_ANIMATION_OPTIONS, MODEL_PATH, status->GetModelScale());

			/** 攻撃判定のコライダーを作成 */
			m_hitCollider = collision::CollisionHitManager::GetInstance()->CreateCollider(
				this,
				collision::EnCollisionType::DeformEnemy,
				status->GetHitRadius(),
				app::EnCollisionAttr::enCollisionAttr_Enemy
			);
			/** やられ判定のコライダーを作成 */
			m_hurtCollider = collision::CollisionHitManager::GetInstance()->CreateCollider(
				this,
				collision::EnCollisionType::DeformEnemy,
				status->GetHurtRadius(),
				app::EnCollisionAttr::enCollisionAttr_Enemy
			);

			m_modelRender.Update();

			return true;
		}


		void DeformEnemy::Update()
		{
			/** キャラクター共通の更新処理を呼び出す */
			Character::Update();
		}


		void DeformEnemy::Render(RenderContext& rc)
		{
			m_modelRender.Draw(rc);
		}
	}
}