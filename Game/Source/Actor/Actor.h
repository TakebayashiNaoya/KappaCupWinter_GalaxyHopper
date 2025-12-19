/**
 * Actor.h
 * 見た目が存在するゲームオブジェクトの基底クラス
 */
#pragma once
#include "ActorStatus.h"


namespace app
{
	namespace actor
	{
		class Actor : public IGameObject
		{
		public:
			/**
			 * トランスフォーム(座標(position)、拡縮(scale)、回転(rotation))
			 * NOTE:例外的にpublicにしている
			 */
			Transform m_transform;



		public:
			/** モデル描画機能を取得 */
			ModelRender* GetModelRender()
			{
				return &m_modelRender;
			}


		protected:
			/** モデル描画 */
			ModelRender m_modelRender;
			/** ステータス */
			ActorStatus* m_status;


		public:
			Actor();
			~Actor();

			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& renderContect) override;
		};
	}
}