/**
 * BossStage.cpp
 * ボスステージシーンの実装
 */
#include "stdafx.h"
#include "BossStage.h"
#include "Source/Actor/Character/Enemy/BossEnemy/BossEnemy.h"
#include "Source/Actor/Character/Player/Player.h"
#include "Source/Actor/Object/Spawner.h"
#include "Source/Actor/Planet/BossPlanet.h"
#include "UI/UIBossStage.h"


namespace app
{
	namespace scene
	{
		BossStage::BossStage()
		{
		}


		BossStage::~BossStage()
		{
			DeleteGO(m_bossPlanet);

			DeleteGO(m_bossEnemy);

			for (auto spawner : m_spawners) {
				if (spawner) {
					DeleteGO(spawner);
				}
			}

			DeleteGO(m_uiBossStage);
		}


		bool BossStage::Start()
		{
			/** BGMをループ再生 */
			sound::SoundManager::Play(sound::enSoundList_BossStageBGM, true);
			/** ロード明けで音量が上がるため、一旦音量を0にしておく */
			sound::SoundManager::SetVolume(sound::enSoundList_BossStageBGM, 0.0f);
			/** UIを生成 */
			m_uiBossStage = NewGO<ui::UIBossStage>(0, "UiBossStage");

			return true;
		}

		void BossStage::OnUpdate()
		{
		}


		void BossStage::InitLevel()
		{
			m_levelRender.Init("Assets/modelData/stage/BossPlanet/BossPlanetLevel.tkl", [&](LevelObjectData& objData) {
				if (objData.EqualObjectName(L"planet")) {
					m_bossPlanet = NewGO<actor::BossPlanet>(0, "BossPlanet");
					m_bossPlanet->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				if (objData.EqualObjectName(L"player")) {
					m_player = NewGO<actor::Player>(0, "Player");
					m_player->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				if (objData.EqualObjectName(L"spiderSpawner")) {
					actor::Spawner* spawner = NewGO <actor::Spawner>(0, "Spawner");
					spawner->SetTransform(objData.position, objData.rotation, objData.scale);
					m_spawners.push_back(spawner);
					return true;
				}
				if (objData.EqualObjectName(L"bear")) {
					m_bossEnemy = NewGO <actor::BossEnemy>(0, "BossEnemy");
					m_bossEnemy->SetTransform(objData.position, objData.rotation, objData.scale);
					return true;
				}
				return false;
				});
		}
	}
}