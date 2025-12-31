/**
 * BasicEnemy.cpp
 * 基本エネミーの実装
 */
#include "stdafx.h"
#include "BasicEnemy.h"
#include "Source/Actor/Character/Enemy/EnemyStateMachine.h"
#include "Collision/CollisionManager.h"

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
			static_assert(ARRAYSIZE(BASIC_ENEMY_ANIMATION_OPTIONS) == enAnimationClip_Num,
				"アニメーションのファイル数とクリップ数が合っていません。");

			/** ステートマシン生成 */
			m_stateMachine = std::make_unique<app::actor::BasicEnemyStateMachine>(this);

			/** ステータス生成 */
			m_status = CreateStatus<BasicEnemyStatus>();
		}


		BasicEnemy::~BasicEnemy()
		{
		}


		bool BasicEnemy::Start()
		{
			/** モデルとアニメーションを初期化 */
			InitModel(enAnimationClip_Num, BASIC_ENEMY_ANIMATION_OPTIONS, MODEL_PATH, MODEL_SCALE);

			/** 攻撃判定のコライダーを作成 */
			m_hitCollider = collision::CollisionHitManager::GetInstance()->CreateCollider(
				this,
				collision::enCollisionType_BasicEnemy,
				HIT_COLLIDER_RADIUS,
				EnCollisionAttr::enCollisionAttr_Enemy
			);

			/** やられ判定のコライダーを作成 */
			m_hurtCollider = collision::CollisionHitManager::GetInstance()->CreateCollider(
				this,
				collision::enCollisionType_BasicEnemy,
				HURT_COLLIDER_RADIUS,
				EnCollisionAttr::enCollisionAttr_Enemy
			);

			m_modelRender.Update();
			return true;
		}


		void BasicEnemy::Update()
		{
			/** ステートマシン更新 */
			m_stateMachine->Update();

			/** モデルと当たり判定の更新に必要な値を取得 */
			m_transform.m_position = m_stateMachine->GetTransform().m_position;
			m_transform.m_rotation = m_stateMachine->GetTransform().m_rotation;
			m_upDirection = m_stateMachine->GetUpDirection();

			/** 当たり判定の更新 */
			collision::CollisionHitManager::GetInstance()->UpdateCollider(this, m_hitCollider, COLLIDER_OFFSET);
			collision::CollisionHitManager::GetInstance()->UpdateCollider(this, m_hurtCollider, COLLIDER_OFFSET);

			/** モデルの更新 */
			m_modelRender.SetPosition(m_transform.m_position);
			m_modelRender.SetRotation(m_transform.m_rotation);
			m_modelRender.Update();
		}


		void BasicEnemy::Render(RenderContext& rc)
		{
			m_modelRender.Draw(rc);
		}
	}
}