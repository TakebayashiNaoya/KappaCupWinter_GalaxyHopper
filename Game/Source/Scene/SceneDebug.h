/**
 * SceneDebug.h
 * デバッグ用のシーン
 */
#pragma once
#include "BattleStageBase.h"


namespace app
{
	namespace scene
	{
		class SceneDebug :public BattleStageBase
		{
		public:
			SceneDebug();
			~SceneDebug();


		private:
			bool Start() override final;
			void InitLevel();
		};




		/**********************************************/


		/**
		 * DebugPlanet.h
		 * デバッグ用の地面オブジェクト
		 */
		class DebugPlanet : public IGameObject
		{
		public:
			DebugPlanet();
			~DebugPlanet();


		private:
			bool Start() override final;
			void Update() override final;
			void Render(RenderContext& rc) override final;


		private:
			/** モデルの当たり判定 */
			PhysicsStaticObject physicsStaticObject;
			/** モデルレンダー*/
			ModelRender m_modelRender;
		};
	}
}