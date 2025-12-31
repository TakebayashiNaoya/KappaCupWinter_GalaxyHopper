#include "stdafx.h"
#include "BossStage.h"
//#include "Source/Actor/Character/Player/Player.h"
//#include "Source/Actor/Character/Enemy/BossEnemy/BossEnemy.h"
//#include "Source/Actor/Planet/BossPlanet.h"
//#include "Source/Actor/Object/Spawner/Spawner.h"
//#include "Source/UI/UIBossHp.h"
//#include "Source/Actor/Actor.h"


namespace app
{
	namespace scene
	{
		BossStage::BossStage()
		{
		}


		BossStage::~BossStage()
		{
			//DeleteGO(m_bossPlanet);

			//BattleManager::GetInstance()->Unregister(m_uiBossHp);
			//DeleteGO(m_uiBossHp);

			//BattleManager::GetInstance()->Unregister(m_bossEnemy);
			//DeleteGO(m_bossEnemy);

			//for (auto spawner : m_spawners) {
			//	if (spawner) {
			//		DeleteGO(spawner);
			//	}
			//}
		}


		bool BossStage::Start()
		{
			//SoundManager::Play(enSoundList_BossStageBGM, true);
			//// ロード明けで音量が上がるため、一旦音量を0にしておく。
			//SoundManager::SetVolume(enSoundList_BossStageBGM, 0.0f);

			//m_uiBossHp = NewGO<UIBossHp>(0, "UIBossHp");
			//BattleManager::GetInstance()->Register(m_uiBossHp);

			return true;
		}

		void BossStage::OnUpdate()
		{
			//if (BattleManager::IsWinnerDecided()) {
			//	SoundManager::StopBGM(enSoundList_BossStageBGM, 0.0f);
			//	return;
			//}
		}


		void BossStage::InitLevel()
		{
			//m_levelRender.Init("Assets/modelData/stage/BossPlanet/BossPlanetLevel.tkl", [&](LevelObjectData& objData) {
			//	if (objData.EqualObjectName(L"planet")) {
			//		m_bossPlanet = NewGO<BossPlanet>(0, "BossPlanet");
			//		m_bossPlanet->SetTRS(objData.position, objData.rotation, objData.scale);
			//		return true;
			//	}
			//	if (objData.EqualObjectName(L"player")) {
			//		m_player = NewGO<Player>(0, "Player");
			//		BattleManager::GetInstance()->Register(m_player);
			//		m_player->SetTRS(objData.position, objData.rotation, objData.scale);
			//		return true;
			//	}
			//	if (objData.EqualObjectName(L"spiderSpawner")) {
			//		Spawner* spider = NewGO <Spawner>(0, "Spawner");
			//		spider->SetTRS(objData.position, objData.rotation, objData.scale);
			//		m_spawners.push_back(spider);
			//		return true;
			//	}
			//	if (objData.EqualObjectName(L"bear")) {
			//		m_bossEnemy = NewGO <BossEnemy>(0, "BossEnemy");
			//		BattleManager::GetInstance()->Register(m_bossEnemy);
			//		m_bossEnemy->SetTRS(objData.position, objData.rotation, objData.scale);
			//		return true;
			//	}
			//	return false;

			//	});
		}
	}
}