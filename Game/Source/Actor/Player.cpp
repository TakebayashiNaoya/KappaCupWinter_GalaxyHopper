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
			static_assert(ARRAYSIZE(PLAYER_ANIMATION_OPTIONS) == enAnimationClip_Num,
				"アニメーションのファイル数とクリップ数が合っていません。");

			/** ステータス生成 */
			m_status = std::make_unique<PlayerStatus>();

			/** ステートマシン生成 */
			m_stateMachine = std::make_unique<PlayerStateMachine>(this);
		}


		Player::~Player()
		{
		}


		bool Player::Start()
		{
			/** モデルとアニメーションの初期化 */
			InitModel(enAnimationClip_Num, PLAYER_ANIMATION_OPTIONS, "Player/player", GetStatus<PlayerStatus>()->GetModelScale());

			/** やられ判定のコライダーを作成 */
			m_hurtCollider = collision::CollisionHitManager::GetInstance()->CreateCollider(
				this,
				collision::EnCollisionType::enCollisionType_Player,
				GetStatus<PlayerStatus>()->GetHurtRadius(),
				app::EnCollisionAttr::enCollisionAttr_Player
			);
			return true;
		}


		void Player::Update()
		{
			/** ステートマシン更新 */
			m_stateMachine->Update();

			/** 無敵タイマー更新 */
			//InvincibleTimer();
		}

		void Player::Render(RenderContext& rc)
		{
			Character::Render(rc);
		}
	}
}