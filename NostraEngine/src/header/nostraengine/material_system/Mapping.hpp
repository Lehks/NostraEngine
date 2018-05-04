//
// Created by Dennis Franz on 03.05.18.
//

#ifndef NOE_MATERIAL_SYSTEM_MAPPING_HPP
#define NOE_MATERIAL_SYSTEM_MAPPING_HPP

#include "NostraEngine/core/StdIncludes.hpp"
#include "NostraUtils/NostraUtils.hpp"

namespace NOE::NOE_MATSYS
{
    class NOU_CLASS Mapping
    {
    private:
        NOU::NOU_DAT_ALG::String8    m_texture;
        NOU::float32                 m_scale;
        NOU::float32                 m_offset;
    public:
        Mapping(const NOU::NOU_DAT_ALG::String8 &texturePath, NOU::float32 scale, NOU::float32 offset);
    };
}

#endif //NOE_MATERIAL_SYSTEM_MAPPING_HPP
