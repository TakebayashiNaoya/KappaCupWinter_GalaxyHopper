/**
 * Environment.h
 * 環境オブジェクトの基底クラス
 */
#pragma once
#include "Source/Actor/Actor.h"


namespace app
{
	namespace actor
	{
		/**
		 * 環境オブジェクトの基底クラス
		 */
		class Environment :public Actor
		{
		public:
			Environment() = default;
			~Environment() override = default;


		protected:
			bool Start() override { return true; }
			void Update() override {}

			/**
			 * モデルの初期化
			 */
			void InitModel(std::string path);

			/** 当たり判定 */
			CollisionObject* m_collider;


		private:
			/** 描画は統一処理なのでprivateにしておく */
			void Render(RenderContext& rc) override final;
		};
	}
}

