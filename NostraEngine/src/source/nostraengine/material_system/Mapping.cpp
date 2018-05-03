//
// Created by Dennis Franz on 03.05.18.
//
#include "NostraEngine/material_system/Mapping.hpp"

namespace NOE::NOE_MATSYS
{
    Mapping::Mapping(const NOU::NOU_DAT_ALG::String8 &texturePath, NOU::float32 scale, NOU::float32 offset) :
        m_texture(texturePath),
        m_scale(scale),
        m_offset(offset)
    {}
}
