#include "nostraengine/scene/Tranformation.hpp"

namespace NOE::NOE_SCENE
{
    Tranformation::Tranformation(const NOU::NOU_MATH::Vec3 &pos,
                                 const NOU::NOU_MATH::Vec3 &rot,
                                 const NOU::NOU_MATH::Vec3 &scale) :
        m_pos(pos),
        m_rot(rot),
        m_scale(scale)
    {}

    const NOU::NOU_MATH::Vec3& Tranformation::getPosition() const
    {
        return m_pos;
    }

    NOU::NOU_MATH::Vec3& Tranformation::getPosition()
    {
        return m_pos;
    }

    const NOU::NOU_MATH::Vec3& Tranformation::getRotation() const
    {
        return m_rot;
    }

    NOU::NOU_MATH::Vec3& Tranformation::getRotation()
    {
        return m_rot;
    }

    const NOU::NOU_MATH::Vec3& Tranformation::getScale() const
    {
        return m_scale;
    }

    NOU::NOU_MATH::Vec3& Tranformation::getScale()
    {
        return m_scale;
    }

	NOU::NOU_MATH::Mat3 Tranformation::toRotationMatrix() const
	{
		NOU::NOU_MATH::Mat3 ret;

		NOU::float32 sa = NOU::NOU_MATH::sin(m_rot[0]);
		NOU::float32 ca = NOU::NOU_MATH::cos(m_rot[0]);

		NOU::float32 sb = NOU::NOU_MATH::sin(m_rot[2]);
		NOU::float32 cb = NOU::NOU_MATH::cos(m_rot[2]);

		NOU::float32 sh = NOU::NOU_MATH::sin(m_rot[1]);
		NOU::float32 ch = NOU::NOU_MATH::cos(m_rot[1]);

		ret.value(0, 0) = ch * ca;
		ret.value(0, 1) = -ch * sa * cb + sh * sb;
		ret.value(0, 2) = ch * sa * sb + sh * cb;

		ret.value(1, 0) = sa;
		ret.value(1, 1) = ca * cb;
		ret.value(1, 2) = -ca * sb;

		ret.value(2, 0) = -sh * ca;
		ret.value(2, 1) = sh * sa * cb + ch * sb;
		ret.value(2, 2) = -sh * sa * sb + ch * cb;

		return ret;
	}
} 