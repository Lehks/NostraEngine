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
}