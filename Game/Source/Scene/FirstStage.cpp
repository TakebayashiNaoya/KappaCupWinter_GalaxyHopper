/**
 * FirstStage.cpp
 * ファーストステージシーンの実装
 */
#include "stdafx.h"
#include "FirstStage.h"
#include "Load/LoadManager.h"
#include "Source/Actor/Character/Enemy/BasicEnemy/BasicEnemy.h"
#include "Source/Actor/Character/Enemy/DeformEnemy/DeformEnemy.h"
#include "Source/Actor/Character/Player/Player.h"
#include "Source/Actor/Object/Rocket.h"
#include "Source/Actor/Object/Treasure.h"
#include "Source/Actor/Planet/FirstPlanet.h"
#include "Ui/UIFirstStage.h"


namespace app
{
	namespace scene
	{
		FirstStage::FirstStage()
		{

		}


		FirstStage::~FirstStage()
		{
			DeleteGO(m_firstStage);

			DeleteGO(m_rocket);

			for (auto treasure : m_treasures) {
				DeleteGO(treasure);
			}

			DeleteGO(m_uiFirstStage);
		}


		bool FirstStage::Start()
		{
			/** BGMをループ再生 */
			sound::SoundManager::Play(sound::enSoundList_FirstStageBGM, true);

			/** ロード明けで音量が上がるため、一旦音量を0にしておく */
			sound::SoundManager::SetVolume(sound::enSoundList_FirstStageBGM, 0.0f);

			/** UIを生成 */
			m_uiFirstStage = NewGO<ui::UIFirstStage>(0, "UIFirstStage");

			return true;
		}

		void FirstStage::OnUpdate()
		{
			if (m_rocket)
			{
				if (m_rocket->GetIsGooled() && load::LoadManager::GetState() == load::LoadManager::EnState::Opened) {
					load::LoadManager::StartLoading();
				}
				if (m_rocket->GetIsGooled() && load::LoadManager::GetState() == load::LoadManager::EnState::Loading) {
					SceneManager::GetInstance()->ChangeScene(SceneID::BossStage);
				}
			}
		}


		void FirstStage::InitLevel()
		{
			m_levelRender.Init("Assets/modelData/stage/FirstPlanet/FirstPlanetLevel.tkl", [&](LevelObjectData& objData) {
				if (objData.EqualObjectName(L"Planet")) {
					m_firstStage = NewGO<actor::FirstPlanet>(0, "FirstPlanet");
					m_firstStage->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				if (objData.EqualObjectName(L"player")) {
					m_player = NewGO<actor::Player>(0, "Player");
					m_player->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				if (objData.EqualObjectName(L"wolf")) {
					actor::BasicEnemy* wolf = NewGO<actor::BasicEnemy>(0, "BasicEnemy");
					wolf->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				if (objData.EqualObjectName(L"spider")) {
					actor::DeformEnemy* spider = NewGO <actor::DeformEnemy>(0, "DeformEnemy");
					spider->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				if (objData.EqualObjectName(L"treasure")) {
					actor::Treasure* treasure = NewGO <actor::Treasure>(0, "Treasure");
					treasure->SetTransform(objData.position, objData.rotation, objData.scale);
					m_treasures.push_back(treasure);
					return true;
				}
				if (objData.EqualObjectName(L"rocket")) {
					m_rocket = NewGO <actor::Rocket>(0, "Rocket");
					m_rocket->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				return false;

				});
		}
	}
}