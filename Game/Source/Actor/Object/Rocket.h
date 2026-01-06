/**
 * Rocket.h
 * ロケットクラス
 */
#pragma once
#include "Source/Actor/Actor.h" 


namespace app
{
	namespace actor
	{
		class Rocket : public Actor
		{
		public:
			const bool GetIsGooled() const
			{
				return m_isGooled;
			}
			const void SetIsGooled(const bool isGooled)
			{
				m_isGooled = isGooled;
			}


		public:
			Rocket();
			~Rocket();


		private:
			bool m_isGooled = false;


		private:
			virtual bool Start() override final;
			virtual void Update() override final;
			virtual void Render(RenderContext& rc) override final;
		};
	}
}