/**
 * Player.cpp
 * プレイヤーを管理するクラス
 */
#include "stdafx.h"
#include "Collision/CollisionManager.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Source/Actor/ActorStatus.h" 


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
			static_assert(ARRAYSIZE(PLAYER_ANIMATION_OPTIONS) == static_cast<uint8_t>(EnPlayerAnimClip::Num),
				"アニメーションのファイル数とクリップ数が合っていません。");

			/** ステートマシンを生成 */
			m_stateMachine = std::make_unique<PlayerStateMachine>(this);

			/** ステータスを生成 */
			m_status = std::make_unique<PlayerStatus>();
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
			/** キャラクター共通の更新処理を呼び出す */
			Character::Update();

			/** 無敵タイマー更新 */
			//InvincibleTimer();
		}

		void Player::Render(RenderContext& rc)
		{
			m_modelRender.Draw(rc);
		}
	}
}