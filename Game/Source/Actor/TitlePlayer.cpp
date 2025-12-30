/**
 * TitlePlayer.cpp
 * タイトル用のプレイヤー実装
 */
#include "stdafx.h"
#include "TitlePlayer.h"
#include "Source/Scene/SceneManager.h"


namespace app
{
	namespace actor
	{
		/** アニメーション設定 */
		const Character::AnimationOption TitlePlayer::PLAYER_ANIMATION_OPTIONS[] =
		{
		  AnimationOption { std::string("Player/idle"),		bool(true)	},
		  AnimationOption { std::string("Player/walk"),		bool(true)	},
		  AnimationOption { std::string("Player/dash"),		bool(true)	},
		  AnimationOption { std::string("Player/jump"),		bool(true)	},
		  AnimationOption { std::string("Player/damage"),	bool(true)	},
		  AnimationOption { std::string("Player/die"),		bool(false)	},
		};


		namespace
		{
			/** モデルパス */
			const std::string MODEL_PATH = "Player/rabbit";
			/** モデルのスケール */
			constexpr float MODEL_SCALE = 200.0f;
			/** スポーン位置 */
			const Vector3 SPAWN_POSITION = Vector3(0.0f, 1000.0f, 0.0f);
		}


		TitlePlayer::TitlePlayer()
		{
		}


		TitlePlayer::~TitlePlayer()
		{
		}


		bool TitlePlayer::Start()
		{
			/** モデルとアニメーションを初期化 */
			InitModel(enAnimationClip_Num, TITLE_PLAYER_ANIMATION_OPTIONS, MODEL_PATH, MODEL_SCALE);

			/** 星に埋もれないように初期位置を調整 */
			m_transform.m_position = SPAWN_POSITION;

			return true;
		}


		void TitlePlayer::Update()
		{
			/** シーン切り替え中は更新しない */
			if (scene::SceneManager::GetInstance()->GetIsSceneChangeRequested()) {
				return;
			}

			/** 歩きアニメーションを再生 */
			m_modelRender.PlayAnimation(enAnimationClip_Walk);
			/** モデルの更新 */
			m_modelRender.SetPosition(m_transform.m_position);
			m_modelRender.Update();
		}


		void TitlePlayer::Render(RenderContext& rc)
		{
			m_modelRender.Draw(rc);
		}
	}
}