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
			m_status = CreateStatus<PlayerStatus>();

			/** バトルマネージャーに登録 */
			if (battle::BattleManager::GetInstance()) {
				battle::BattleManager::GetInstance()->Register(this);
			}
		}


		Player::~Player()
		{
			/** バトルマネージャーから登録解除 */
			if (battle::BattleManager::GetInstance()) {
				battle::BattleManager::GetInstance()->Unregister(this);
			}
		}


		bool Player::Start()
		{
			/** ステートマシンに初期値を渡しておく */
			if (m_stateMachine) {
				m_stateMachine->SetPosition(m_transform.m_position);
				m_stateMachine->SetRotation(m_transform.m_rotation);
			}

			/** PlayerStatusにキャストする */
			auto status = GetStatus<PlayerStatus>();

			/** モデルとアニメーションの初期化 */
			InitModel(static_cast<uint8_t>(EnPlayerAnimClip::Num), PLAYER_ANIMATION_OPTIONS, "Player/rabbit", status->GetModelScale());

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

			/** 無敵状態の更新 */
			UpdateInvincible();
		}


		void Player::Render(RenderContext& rc)
		{
			/** 点滅をフラグで描画する */
			if (m_isVisible) {
				m_modelRender.Draw(rc);
			}
		}


		void Player::UpdateInvincible()
		{
			/** 無敵状態の更新 */
			if (m_isInvincible)
			{
				/** タイマーを進める */
				m_invincibleTimer += g_gameTime->GetFrameDeltaTime();

				/** 無敵時間を超えたら無敵を解除 */
				if (m_invincibleTimer >= GetStatus<PlayerStatus>()->GetInvincibleDuration()) {
					m_invincibleTimer = 0.0f;
					m_isInvincible = false;
					m_isVisible = true;
				}
				else {
					/** 0.1秒間隔で点滅(10を掛けてintにキャストし、偶数奇数で判定) */
					int interval = static_cast<int>(m_invincibleTimer * 10.0f);
					m_isVisible = (interval % 2 == 0);
				}
			}
			else {
				m_invincibleTimer = 0.0f;
				m_isVisible = true;
			}
		}
	}
}