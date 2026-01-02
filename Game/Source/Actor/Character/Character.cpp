/**
 * Actor.h
 * 見た目が存在するゲームオブジェクトの基底クラス
 */
#include "stdafx.h"
#include "Character.h"
#include "Source/Actor/Character/CharacterStateMachine.h"
#include "Collision/CollisionManager.h"


namespace app
{
	namespace actor
	{
		namespace
		{
			/** モデルを格納しているファイルのパスとモデルの拡張子 */
			const std::string MODEL_FILE_PATH = "Assets/modelData/Character/";
			const std::string MODEL_EXTENSION = ".tkm";
			/** アニメーションデータを格納しているファイルのパスとアニメーションデータの拡張子 */
			const std::string ANIM_FILE_PATH = "Assets/animData/";
			const std::string ANIM_EXTENSION = ".tka";
		}


		Character::Character()
		{
		}


		Character::~Character()
		{
		}


		bool Character::Start()
		{
			return Actor::Start();
		}


		void Character::Update()
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


		void Character::Render(RenderContext& renderContect)
		{
			Actor::Render(renderContect);
		}


		/**
		 * モデルとアニメーションの初期化を行う。
		 * ・アニメーションクリップの数
		 * ・アニメーションクリップのオプション配列
		 * ・モデルファイルのパス
		 * ・モデルの拡大率
		 */
		void Character::InitModel(
			const uint8_t count,
			const AnimationOption* option,
			const std::string path,
			const float scale
		)
		{
			/** アニメーションクリップのリストを確保 */
			m_animationClipList.resize(count);

			/** アニメーションクリップの読み込み */
			for (size_t i = 0; i < count; i++) {
				auto* animationClip = new AnimationClip();
				std::string animFullPath = ANIM_FILE_PATH + option[i].fileName + ANIM_EXTENSION;
				animationClip->Load(animFullPath.c_str());
				animationClip->SetLoopFlag(option[i].is_loop);
				m_animationClipList[i] = animationClip;
			}

			/** モデルの初期化 */
			std::string fullModelPath = MODEL_FILE_PATH + path + MODEL_EXTENSION;
			m_modelRender.Init(fullModelPath.c_str(), *m_animationClipList.data(), count, enModelUpAxisY);

			/** モデルの初期化 */
			m_transform.m_scale = Vector3(scale, scale, scale);
			m_modelRender.SetPosition(m_transform.m_position);
			m_modelRender.SetScale(m_transform.m_scale);
			m_modelRender.SetRotation(m_transform.m_rotation);
		}
	}
}