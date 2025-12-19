/**
 * Player.cpp
 * プレイヤーを管理するクラス
 */
#include "stdafx.h"
#include "Player.h"


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
			/** TODO: newとmake_uniqueの使い分けについて確認。 */
			m_status = new PlayerStatus();
			m_status->Setup();

			/** ステートマシン生成 */
			m_stateMachine = std::make_unique<PlayerStateMachine>();
		}


		Player::~Player()
		{
			/** ステータス削除 */
			delete m_status;
			m_status = nullptr;
		}


		bool Player::Start()
		{
			/** モデルとアニメーションの初期化 */
			InitModel(enAnimationClip_Num, PLAYER_ANIMATION_OPTIONS, "Player/player", m_status->GetModelScale());
			return true;
		}


		void Player::Update()
		{
			/** ステートマシン更新 */
			m_stateMachine->Update();

			/** 無敵タイマー更新 */
			InvincibleTimer();
		}
	}
}