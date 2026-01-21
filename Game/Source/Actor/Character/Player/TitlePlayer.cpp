/**
 * TitlePlayer.cpp
 * タイトル用のプレイヤー実装
 */
#include "stdafx.h"
#include "Source/Scene/SceneManager.h"
#include "TitlePlayer.h"


namespace app
{
	namespace actor
	{
		/** アニメーション設定 */
		const Character::AnimationOption TitlePlayer::TITLE_PLAYER_ANIMATION_OPTIONS[] =
		{
			AnimationOption { std::string("Player/walk"),	bool(true)}
		};


		namespace
		{
			/** モデルパス */
			const std::string MODEL_PATH = "Player/rabbit";
			/** スポーン位置 */
			const Vector3 SPAWN_POSITION = Vector3(0.0f, 1000.0f, 0.0f);
		}


		TitlePlayer::TitlePlayer()
		{
			/** カメラがプレイヤーの座標を取得するため、コンストラクタで初期位置を設定しておく */
			m_transform.m_position = SPAWN_POSITION;
		}


		TitlePlayer::~TitlePlayer()
		{
		}


		bool TitlePlayer::Start()
		{
			/** モデルとアニメーションを初期化 */
			InitModel(
				static_cast<uint8_t>(ARRAYSIZE(TITLE_PLAYER_ANIMATION_OPTIONS)),
				TITLE_PLAYER_ANIMATION_OPTIONS,
				MODEL_PATH,
				GetStatus<PlayerStatus>()->GetModelScale()
			);

			/** 星に埋もれないように初期位置を調整 */
			m_modelRender.SetPosition(m_transform.m_position);

			/**
			 * 歩きアニメーションを再生
			 * 今回はアニメーションが1つしかないので0番を再生
			 */
			m_modelRender.PlayAnimation(0);

			return true;
		}


		void TitlePlayer::Update()
		{
			/** シーン切り替え中は更新しない */
			if (scene::SceneManager::GetInstance()->GetIsSceneChangeRequested()) {
				return;
			}

			/** モデルの更新 */
			m_modelRender.Update();
		}


		void TitlePlayer::Render(RenderContext& rc)
		{
			m_modelRender.Draw(rc);
		}
	}
}