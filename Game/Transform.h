#pragma once

class Transform : public Noncopyable
{
public:
	Vector3 m_position;
	Quaternion m_rotation;
	Vector3 m_scale;
};