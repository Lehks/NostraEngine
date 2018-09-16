#ifndef NOE_SCENE_TRANFORMATION_HPP
#define NOE_SCENE_TRANFORMATION_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"

namespace NOE::NOE_SCENE
{
	class Tranformation
	{
    private:
        NOU::NOU_MATH::Vec3 m_pos;

        NOU::NOU_MATH::Vec3 m_rot;

        NOU::NOU_MATH::Vec3 m_scale;

    public:
        explicit Tranformation(const NOU::NOU_MATH::Vec3 &pos = NOU::NOU_MATH::Vec3(0.0f, 0.0f, 0.0f), 
                               const NOU::NOU_MATH::Vec3 &rot = NOU::NOU_MATH::Vec3(0.0f, 0.0f, 0.0f),
                               const NOU::NOU_MATH::Vec3 &scale = NOU::NOU_MATH::Vec3(1.0f, 1.0f, 1.0f));

        const NOU::NOU_MATH::Vec3& getPosition() const;
        NOU::NOU_MATH::Vec3& getPosition();

        const NOU::NOU_MATH::Vec3& getRotation() const;
        NOU::NOU_MATH::Vec3& getRotation();

        const NOU::NOU_MATH::Vec3& getScale() const;
        NOU::NOU_MATH::Vec3& getScale();
    };
}

#endif // !NOE_SCENE_TRANFORMATION_HPP

