/**
 * BossStage.h
 * ボスステージシーン
 */
#pragma once
#include "Source/Scene/BattleStageBase.h"


namespace app
{
	/** 前方宣言 */
	namespace actor {
		class BossPlanet;
		class Spawner;
	}
	namespace ui { class UIBossStage; }


	namespace scene
	{
		/**
		 * ボスステージシーン
		 */
		class BossStage : public BattleStageBase
		{
		public:
			BossStage();
			~BossStage();


		private:
			/** 開始処理 */
			bool Start() override final;
			/** 更新処理 */
			void OnUpdate() override final;
			/** レベルの初期化 */
			void InitLevel()override final;


		private:
			actor::BossPlanet* m_bossPlanet = nullptr;
			std::vector<actor::Spawner*> m_spawners;
			ui::UIBossStage* m_uiBossStage = nullptr;
		};
	}
}