/**
 * Player.cpp
 * プレイヤーを管理するクラス
 */
#include "stdafx.h"
#include "Player.h"
#include "Collision/CollisionManager.h"


namespace app
{
	namespace actor
	{
		namespace
		{
			constexpr float COLLIDER_OFFSET = 50.0f;							// ボディコライダーのオフセット値。
		}


		/** アニメーション設定 */
		const Character::AnimationOption Player::PLAYER_ANIMATION_OPTIONS[] =
		{
		  AnimationOption { std::string("Player/idle"),		bool(true)	},
		  AnimationOption { std::string("Player/walk"),		bool(true)	},
		  AnimationOption { std::string("Player/dash"),		bool(true)	},
		  AnimationOption { std::string("Player/jump"),		bool(true)	},
		  AnimationOption { std::string("Player/damage"),	bool(true)	},
		  AnimationOption { std::string("Player/die"),		bool(false)	},
		};


		Player::Player()
		{
			/** アニメーション数チェック */
			static_assert(ARRAYSIZE(PLAYER_ANIMATION_OPTIONS) == static_cast<uint8_t>(EnPlayerAnimClip::Num),
				"アニメーションのファイル数とクリップ数が合っていません。");

			/** ステートマシン生成 */
			m_stateMachine = std::make_unique<PlayerStateMachine>(this);

			/** ステータス生成 */
			m_status = CreateStatus<PlayerStatus>();
		}


		Player::~Player()
		{
		}


		bool Player::Start()
		{
			/** モデルとアニメーションの初期化 */
			InitModel(static_cast<uint8_t>(EnPlayerAnimClip::Num), PLAYER_ANIMATION_OPTIONS, "Player/player", GetStatus<PlayerStatus>()->GetModelScale());

			/** やられ判定のコライダーを作成 */
			m_hurtCollider = collision::CollisionHitManager::GetInstance()->CreateCollider(
				this,
				collision::EnCollisionType::Player,
				GetStatus<PlayerStatus>()->GetHurtRadius(),
				app::EnCollisionAttr::enCollisionAttr_Player
			);
			return true;
		}


		void Player::Update()
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

			/** 無敵タイマー更新 */
			//InvincibleTimer();
		}

		void Player::Render(RenderContext& rc)
		{
			Character::Render(rc);
		}
	}
}