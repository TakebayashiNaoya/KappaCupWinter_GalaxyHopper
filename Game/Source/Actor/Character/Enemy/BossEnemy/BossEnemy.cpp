#include "stdafx.h"
#include "BossEnemy.h"
#include "Source/Actor/Character/Enemy/EnemyStateMachine.h"
#include "Collision/CollisionManager.h"


namespace app
{
	namespace actor
	{
		/** アニメーション設定 */
		const Character::AnimationOption BossEnemy::BOSS_ENEMY_ANIMATION_OPTIONS[] = {
		  AnimationOption { std::string("Bear/idle"),		bool(true)	},
		  AnimationOption { std::string("Bear/walk"),		bool(true)	},
		  AnimationOption { std::string("Bear/dash"),		bool(true)	},
		  AnimationOption { std::string("Bear/attack"),		bool(false)	},
		  AnimationOption { std::string("Bear/damage"),		bool(true)	},
		  AnimationOption { std::string("Bear/die"),		bool(false)	},
		};


		namespace
		{
			const std::string MODEL_PATH = "Bear/bear";

			constexpr float COLLIDER_OFFSET = 100.0f;							// ボディコライダーのオフセット値。
			constexpr float HIT_COLLIDER_RADIUS = 100.0f;						// 当たりコライダーのサイズ。
			constexpr float HURT_COLLIDER_RADIUS = 300.0f;

			constexpr float COOLDOWN_DURATION = 3.0f;							// 攻撃のクールダウン時間。
			constexpr float ATTACK_RANGE = 300.0f;								// 攻撃範囲。
			constexpr float ATTACK_RADIUS = 200.0f;								// 攻撃判定の半径。
		}


		BossEnemy::BossEnemy()
		{
			/** アニメーション数チェック */
			static_assert(ARRAYSIZE(BOSS_ENEMY_ANIMATION_OPTIONS) == static_cast<uint8_t>(EnBossEnemyAnimClip::Num),
				"アニメーションのファイル数とクリップ数が合っていません。");

			/** ステートマシン生成 */
			m_stateMachine = std::make_unique<BossEnemyStateMachine>(this);

			/** ステータス生成 */
			m_status = CreateStatus<BossEnemyStatus>();
		}


		BossEnemy::~BossEnemy()
		{
		}


		bool BossEnemy::Start()
		{
			/** モデルとアニメーションを初期化 */
			InitModel(static_cast<uint8_t>(EnBossEnemyAnimClip::Num), BOSS_ENEMY_ANIMATION_OPTIONS, MODEL_PATH, GetStatus<BossEnemyStatus>()->GetModelScale());

			/** 攻撃判定のコライダーを作成 */
			m_hitCollider = collision::CollisionHitManager::GetInstance()->CreateCollider(
				this,
				collision::EnCollisionType::BossEnemy,
				HIT_COLLIDER_RADIUS,
				app::EnCollisionAttr::enCollisionAttr_Enemy
			);

			/** やられ判定のコライダーを作成 */
			m_hurtCollider = collision::CollisionHitManager::GetInstance()->CreateCollider(
				this,
				collision::EnCollisionType::BossEnemy,
				HURT_COLLIDER_RADIUS,
				app::EnCollisionAttr::enCollisionAttr_Enemy
			);

			/** アニメーションイベント用の関数を設定する */
			m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
				OnAnimationEvent(clipName, eventName);
				});

			return true;
		}


		void BossEnemy::Update()
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


		void BossEnemy::Render(RenderContext& rc)
		{
			m_modelRender.Draw(rc);
		}


		void BossEnemy::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
		{
			/** キーの名前が「attack_start」の時 */
			if (wcscmp(eventName, L"attack_start") == 0)
			{
				/** 攻撃音再生 */
				sound::SoundManager::Play(sound::enSoundList_BossAttack, false, true, m_transform.m_position);

				if (collision::CollisionHitManager::GetInstance() == nullptr) {
					return;
				}

				/** 攻撃用コライダーを作成 */
				m_attackHitCollider = collision::CollisionHitManager::GetInstance()->CreateCollider(
					this,
					collision::EnCollisionType::BossEnemy,
					ATTACK_RADIUS,
					app::EnCollisionAttr::enCollisionAttr_Enemy
				);
				/** 攻撃用コライダーの位置を設定 */
				Vector3 attackPosition = m_transform.m_position + m_attackDirection * ATTACK_RANGE;
				m_attackHitCollider->SetPosition(attackPosition);
			}
			/** キーの名前が「attack_end」の時 */
			else if (wcscmp(eventName, L"attack_end") == 0)
			{
				if (collision::CollisionHitManager::GetInstance() == nullptr) {
					return;
				}

				/** 攻撃用コライダーを削除 */
				m_attackHitCollider = collision::CollisionHitManager::GetInstance()->DeleteCollider(m_attackHitCollider);
			}
			/** キーの名前が「step」の時 */
			else if (wcscmp(eventName, L"step") == 0)
			{
				sound::SoundManager::GetInstance()->Play(sound::enSoundList_BossStep);
			}
			/** キーの名前が「dead」の時 */
			else if (wcscmp(eventName, L"dead") == 0) {
				sound::SoundManager::Play(sound::enSoundList_BossDead, false, true, m_transform.m_position);
			}
		}
	}
}