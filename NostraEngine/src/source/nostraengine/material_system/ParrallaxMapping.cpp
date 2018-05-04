//
// Created by Dennis Franz on 03.05.18.
//
#include "NostraEngine/material_system/ParrallaxMapping.hpp"

namespace NOE::NOE_MATSYS
{
    ParrallaxMapping::ParrallaxMapping(const NOU::NOU_DAT_ALG::String8 &texturePath, const NOU::NOU_DAT_ALG::String8 &normalTexturePath, const NOU::NOU_DAT_ALG::String8 &displacementTexturePath ,NOU::float32 scale, NOU::float32 offset) :
    Mapping(texturePath, scale, offset),
    m_normalTexture(normalTexturePath),
    m_displacementTexture(displacementTexturePath)
    {}
}

