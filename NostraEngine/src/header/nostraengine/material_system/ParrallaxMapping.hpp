//
// Created by Dennis Franz on 03.05.18.
//

#ifndef NOSTRAENGINE_PARRALLAXMAPPING_HPP
#define NOSTRAENGINE_PARRALLAXMAPPING_HPP

#include "NostraEngine/core/StdIncludes.hpp"
#include "NostraUtils/NostraUtils.hpp"
#include "NostraEngine/material_system/Mapping.hpp"

namespace NOE::NOE_MATSYS
{
    class NOU_CLASS ParrallaxMapping : public Mapping
    {
    public:
        ParrallaxMapping(NOU::NOU_DAT_ALG::String8 texturePath, NOU::float32 scale, NOU::float32 offset);
    };
}

#endif //NOSTRAENGINE_PARRALLAXMAPPING_HPP
