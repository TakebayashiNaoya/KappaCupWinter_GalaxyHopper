/**
 * Actor.h
 * 見た目が存在するゲームオブジェクトの基底クラス
 */
#include "stdafx.h"
#include "Character.h"





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
			//上方向ベクトルの更新。
			UpdateUpDirection();
			Actor::Update();
		}


		void Character::Render(RenderContext& renderContect)
		{
			Actor::Render(renderContect);
		}


		void Character::UpdateUpDirection()
		{
			Vector3 planetCenter = Vector3::Zero;
			m_upDirection = m_transform.m_position - planetCenter;
			m_upDirection.Normalize();
		}


		void Character::InitModel(
			const uint8_t count,			/** アニメーションクリップの数 */
			const AnimationOption* option,	/** アニメーションクリップのオプション配列 */
			const std::string path,			/** モデルファイルのパス */
			const float scale				/** モデルの拡大率 */
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