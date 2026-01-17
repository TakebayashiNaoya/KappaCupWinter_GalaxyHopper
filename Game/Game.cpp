/**
 * Game.cpp
 * ゲームのメインクラス実装
 */
#include "stdafx.h"
#include "Collision/CollisionManager.h"
#include "Core/ParameterManager.h"
#include "Game.h"
#include "Load/LoadManager.h"
#include "Source/Scene/SceneManager.h"


Game::Game()
{
	/** パラメータマネージャーのインスタンス生成 */
	app::core::ParameterManager::CreateInstance();

	/** 各種マネージャーオブジェクトの生成 */
	/** シーン */
	m_sceneManagerObject = NewGO<app::scene::SceneManagerObject>(0, "SceneManagerObject");
	/** ロード */
	m_loadManagerObject = NewGO<app::load::LoadManagerObject>(0, "LoadManagerObject");
	/** サウンド */
	m_soundManagerObject = NewGO<app::sound::SoundManagerObject>(0, "SoundManagerObject");
	/** バトル */
	m_battleManagerObject = NewGO<app::battle::BattleManagerObject>(0, "BattleManagerObject");
	/** 衝突判定 */
	m_collisionManagerObject = NewGO<app::collision::CollisionManagerObject>(0, "CollisionManagerObject");
}


Game::~Game()
{
	/** 各種マネージャーオブジェクトの破棄 */
	/** 衝突判定 */
	DeleteGO(m_collisionManagerObject);
	/** バトル */
	DeleteGO(m_battleManagerObject);
	/** サウンド */
	DeleteGO(m_soundManagerObject);
	/** ロード */
	DeleteGO(m_loadManagerObject);
	/** シーン */
	DeleteGO(m_sceneManagerObject);

	/** パラメータマネージャーのインスタンス破棄 */
	app::core::ParameterManager::DeleteInstance();
}