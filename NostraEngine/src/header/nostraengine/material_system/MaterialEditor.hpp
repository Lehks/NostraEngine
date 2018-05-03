//
// Created by Dennis Franz on 03.05.18.
//

#ifndef NOE_MATERIAL_SYSTEM_MATERIALEDITOR_HPP
#define NOE_MATERIAL_SYSTEM_MATERIALEDITOR_HPP

#include "NostraEngine/core/StdIncludes.hpp"
#include "NostraUtils/NostraUtils.hpp"

#include "glad/glad.h"

namespace NOE::NOE_MATSYS
{

    class NOU_CLASS MaterialEditor
    {
    private:
        NOU::NOU_FILE_MNGT::File    m_materialSource;
        NOU::NOU_DAT_ALG::String8   m_name;

    public:
        MaterialEditor();
        NOU::NOU_DAT_ALG::String8 generateMaterialFromJSON();
        NOU::NOU_DAT_ALG::String8 generateJSONFromMaterial();
        void setTextureMapping(NOU::boolean setFlag);
        void setNormalMapping(NOU::boolean setFlag);
        void setParralaxMapping(NOU::boolean setFlag);
        void setColor(NOU::boolean setFlag);
        void setMaterialName(NOU::NOU_DAT_ALG::String8 name);
        NOU::NOU_DAT_ALG::String8 getMaterialName();
    };

}

#endif //NOE_MATERIAL_SYSTEM_MATERIALEDITOR_HPP
