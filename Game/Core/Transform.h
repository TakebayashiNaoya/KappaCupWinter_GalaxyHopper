/**
 * Transform.h
 * トランスフォーム定義
 */
#pragma once


namespace app
{
	namespace core
	{
		class Transform : public Noncopyable
		{
		public:
			/** 座標 */
			Vector3 m_position;
			/** 回転 */
			Quaternion m_rotation;
			/** 拡大縮小 */
			Vector3 m_scale;
		};
	}
}