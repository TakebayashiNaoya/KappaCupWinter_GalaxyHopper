/**
 * FirstStage.cpp
 * ファーストステージシーンの実装
 */
#include "stdafx.h"
#include "FirstStage.h"
#include "LoadingScreen.h"
#include "Source/Actor/Character/Enemy/BasicEnemy/BasicEnemy.h"
#include "Source/Actor/Character/Enemy/DeformEnemy/DeformEnemy.h"
#include "Source/Actor/Character/Player/Player.h"
#include "Source/Actor/Object/Rocket.h"
#include "Source/Actor/Object/Treasure.h"
#include "Source/Actor/Planet/FirstPlanet.h"


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

			battle::BattleManager::GetInstance()->Unregister(m_uiGear);
			DeleteGO(m_uiGear);

			battle::BattleManager::GetInstance()->Unregister(m_rocket);
			DeleteGO(m_rocket);

			for (auto treasure : m_treasures) {
				if (treasure) {
					battle::BattleManager::GetInstance()->Unregister(treasure);
					DeleteGO(treasure);
				}
			}
		}


		bool FirstStage::Start()
		{
			/** BGMをループ再生 */
			sound::SoundManager::Play(sound::enSoundList_FirstStageBGM, true);

			/** ロード明けで音量が上がるため、一旦音量を0にしておく */
			sound::SoundManager::SetVolume(sound::enSoundList_FirstStageBGM, 0.0f);

			m_uiGear = NewGO<UIGear>(0, "UIGear");
			battle::BattleManager::GetInstance()->Register(m_uiGear);

			return true;
		}

		void FirstStage::OnUpdate()
		{
			if (battle::BattleManager::GetInstance()->GetBattleResult() == battle::BattleManager::GetInstance()->EnBattleResult::Lose) {
				sound::SoundManager::StopBGM(sound::enSoundList_FirstStageBGM, 0.0f);
				return;
			}

			if (m_rocket)
			{
				if (m_rocket->GetIsGooled() && LoadingScreen::GetState() == LoadingScreen::Opened) {
					LoadingScreen::StartLoading();
				}
				if (m_rocket->GetIsGooled() && LoadingScreen::GetState() == LoadingScreen::Loading) {
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
					battle::BattleManager::GetInstance()->Register(m_player);
					m_player->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				if (objData.EqualObjectName(L"wolf")) {
					actor::BasicEnemy* wolf = NewGO<actor::BasicEnemy>(0, "BasicEnemy");
					battle::BattleManager::GetInstance()->Register(wolf);
					wolf->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				if (objData.EqualObjectName(L"spider")) {
					actor::DeformEnemy* spider = NewGO <actor::DeformEnemy>(0, "DeformEnemy");
					battle::BattleManager::GetInstance()->Register(spider);
					spider->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				if (objData.EqualObjectName(L"treasure")) {
					actor::Treasure* treasure = NewGO <actor::Treasure>(0, "Treasure");
					battle::BattleManager::GetInstance()->Register(treasure);
					treasure->SetTransform(objData.position, objData.rotation, objData.scale);
					m_treasures.push_back(treasure);
					return true;
				}
				if (objData.EqualObjectName(L"rocket")) {
					m_rocket = NewGO <actor::Rocket>(0, "Rocket");
					battle::BattleManager::GetInstance()->Register(m_rocket);
					m_rocket->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				return false;

				});
		}
	}
}