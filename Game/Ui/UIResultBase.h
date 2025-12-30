/**
 * UIResultBase.h
 * リザルト用のUIの基底クラス
 */
#pragma once


namespace app
{
	namespace ui
	{
		class UIResultBase : public IGameObject
		{
		public:
			UIResultBase() {}
			virtual ~UIResultBase() {}

			/**
			 * UIアニメーションが終わったかを取得
			 */
			inline const bool GetIsEnd() const
			{
				return m_isEnd;
			}


		protected:
			/** UIアニメーションが終わったか */
			bool m_isEnd = false;
		};
	}
}
