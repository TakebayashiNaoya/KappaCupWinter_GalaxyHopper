/**
 * Tree.h
 * 木のクラス
 */
#pragma once
#include "Environment.h"


namespace app
{
	namespace actor
	{
		/**
		 * 木のクラス
		 */
		class Tree : public Environment
		{
		public:
			Tree() = default;
			~Tree() override = default;


		private:
			bool Start() override final;
			void Update() override {}
		};
	}
}
