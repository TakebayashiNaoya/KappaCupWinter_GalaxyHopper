/**
 * Game.h
 * ゲームのメインクラス
 */
#pragma once


 /** 前方宣言 */
namespace app
{
	namespace scene { class SceneManagerObject; }
	namespace load { class LoadManagerObject; }
	namespace sound { class SoundManagerObject; }
	namespace battle { class BattleManagerObject; }
	namespace collision { class CollisionManagerObject; }
}


/**
 * 全てこの中で生成する
 */
class Game
{
public:
	Game();
	~Game();


	/**
	 * 各種マネージャーオブジェクト
	 */
private:
	/** シーン */
	app::scene::SceneManagerObject* m_sceneManagerObject = nullptr;
	/** ロード */
	app::load::LoadManagerObject* m_loadManagerObject = nullptr;
	/** サウンド */
	app::sound::SoundManagerObject* m_soundManagerObject = nullptr;
	/** バトル */
	app::battle::BattleManagerObject* m_battleManagerObject = nullptr;
	/** 衝突判定 */
	app::collision::CollisionManagerObject* m_collisionManagerObject = nullptr;
};

