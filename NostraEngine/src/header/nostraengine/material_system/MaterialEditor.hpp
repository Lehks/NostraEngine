//
// Created by Dennis Franz on 03.05.18.
//

#ifndef NOE_MATERIAL_SYSTEM_MATERIALEDITOR_HPP
#define NOE_MATERIAL_SYSTEM_MATERIALEDITOR_HPP

#include "NostraEngine/core/StdIncludes.hpp"
#include "NostraUtils/NostraUtils.hpp"
#include "NostraEngine/material_system/TextureMapping.hpp"
#include "NostraEngine/material_system/NormalMapping.hpp"
#include "NostraEngine/material_system/ParrallaxMapping.hpp"

#include "glad/glad.h"

namespace NOE::NOE_MATSYS
{

    class NOU_CLASS MaterialEditor
    {
    private:
        NOU::NOU_FILE_MNGT::File            m_materialSource;
        NOU::NOU_DAT_ALG::String8           m_name;
        NOE::NOE_MATSYS::TextureMapping     m_textureMapping;
        NOE::NOE_MATSYS::NormalMapping      m_normalMapping;
        NOE::NOE_MATSYS::ParrallaxMapping   m_ParrallaxMapping;

    public:
        MaterialEditor(NOU::NOU_DAT_ALG::String8 m_name);
        NOU::NOU_DAT_ALG::String8 generateMaterialFromJSON();
        NOU::boolean generateJSONFromMaterial();
        void setTextureMapping(NOU::boolean setFlag, const NOU::NOU_DAT_ALG::String8 &texturePath, NOU::float32 scale, NOU::float32 offset);
        void setNormalMapping(NOU::boolean setFlag, const NOU::NOU_DAT_ALG::String8 &texturePath, const NOU::NOU_DAT_ALG::String8 &normalTexturePath, NOU::float32 scale, NOU::float32 offset);
        void setParralaxMapping(NOU::boolean setFlag, const NOU::NOU_DAT_ALG::String8 &texturePath, const NOU::NOU_DAT_ALG::String8 &normalTexturePath, const NOU::NOU_DAT_ALG::String8 &displacementTexturePath,NOU::float32 scale, NOU::float32 offset);
        void setColor(NOU::boolean setFlag);
        void setMaterialName(NOU::NOU_DAT_ALG::String8 name);
        NOU::NOU_DAT_ALG::String8 getMaterialName();
    };

}

#endif //NOE_MATERIAL_SYSTEM_MATERIALEDITOR_HPP
