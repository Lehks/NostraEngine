//
// Created by Dennis Franz on 03.05.18.
//
#include "NostraEngine/material_system/NormalMapping.hpp"

namespace NOE::NOE_MATSYS
{
    NormalMapping::NormalMapping(const NOU::NOU_DAT_ALG::String8 &texturePath, const NOU::NOU_DAT_ALG::String8 &normalTexturePath,NOU::float32 scale, NOU::float32 offset) :
        Mapping(texturePath, scale, offset),
        m_normalTexture()
    {}
}
