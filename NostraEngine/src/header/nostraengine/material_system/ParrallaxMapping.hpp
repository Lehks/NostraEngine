//
// Created by Dennis Franz on 03.05.18.
//

#ifndef NOE_MATERIAL_SYSTEM_PARRALLAXMAPPING_HPP
#define NOE_MATERIAL_SYSTEM_PARRALLAXMAPPING_HPP

#include "NostraEngine/core/StdIncludes.hpp"
#include "NostraUtils/NostraUtils.hpp"
#include "NostraEngine/material_system/Mapping.hpp"

namespace NOE::NOE_MATSYS
{
    class NOU_CLASS ParrallaxMapping : public Mapping
    {
    private:
        NOU::NOU_DAT_ALG::String8   m_normalTexture;
        NOU::NOU_DAT_ALG::String8   m_displacementTexture;
    public:
        ParrallaxMapping(const NOU::NOU_DAT_ALG::String8 &texturePath, const NOU::NOU_DAT_ALG::String8 &normalTexturePath, const NOU::NOU_DAT_ALG::String8 &displacementTexturePath ,NOU::float32 scale, NOU::float32 offset);
    };
}

#endif //NOE_MATERIAL_SYSTEM_PARRALLAXMAPPING_HPP
