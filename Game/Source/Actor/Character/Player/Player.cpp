/**
 * Player.cpp
 * プレイヤーを管理するクラス
 */
#include "stdafx.h"
#include "Player.h"
#include "Collision/CollisionManager.h"
#include "Source/Actor/ActorStatus.h" 
#include "PlayerStateMachine.h"


namespace app
{
	namespace actor
	{
		namespace
		{
			constexpr float COLLIDER_OFFSET = 50.0f;		// ボディコライダーのオフセット値。
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

			/** PlayerStatus型でステータス生成 */
			auto status = CreateStatus<PlayerStatus>();

			/** ステートマシンを生成し、自分（Player型）とステータス（PlayerStatus型）の生ポインタを渡す */
			m_stateMachine = std::make_unique<PlayerStateMachine>(this, status.get());

			/** ステータスをムーブして保持 */
			m_status = std::move(status);
		}


		Player::~Player()
		{
		}


		bool Player::Start()
		{
			/** PlayerStatusにキャストする */
			auto status = GetStatus<PlayerStatus>();

			/** モデルとアニメーションの初期化 */
			InitModel(static_cast<uint8_t>(EnPlayerAnimClip::Num), PLAYER_ANIMATION_OPTIONS, "Player/player", status->GetModelScale());

			/** やられ判定のコライダーを作成 */
			m_hurtCollider = collision::CollisionHitManager::GetInstance()->CreateCollider(
				this,
				collision::EnCollisionType::Player,
				status->GetHurtRadius(),
				app::EnCollisionAttr::enCollisionAttr_Player
			);
			return true;
		}


		void Player::Update()
		{
			/** 無敵タイマー更新 */
			//InvincibleTimer();
		}

		void Player::Render(RenderContext& rc)
		{
			Character::Render(rc);
		}
	}
}