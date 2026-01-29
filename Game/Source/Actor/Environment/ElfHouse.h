/**
 * ElfHouse.h
 * エルフの家のクラス
 */
#pragma once
#include "Environment.h"


namespace app
{
	namespace actor
	{
		/**
		 * エルフの家のクラス
		 */
		class ElfHouse : public Environment
		{
		public:
			ElfHouse() = default;
			~ElfHouse() override = default;


		private:
			bool Start() override final;
			void Update() override {}
		};
	}
}
