//
// Created by Dennis Franz on 04.05.18.
//
#include "NostraEngine/material_system/MaterialEditor.hpp"

namespace NOE::NOE_MATSYS
{
    MaterialEditor* MaterialEditor::getInstance()
    {
        if(s_uniqueInstance == nullptr)
        {
            s_uniqueInstance = new MaterialEditor();
        }

        return s_uniqueInstance;
    }

    void MaterialEditor::setTextureMapping(NOU::boolean setFlag, const NOU::NOU_DAT_ALG::String8 &texturePath,
                                           NOU::float32 scale, NOU::float32 offset)
    {
        if(setFlag == 1)
        {
            m_textureMapping = new TextureMapping(texturePath,scale,offset);
        }else{
            m_textureMapping = nullptr;
        }
    }

    void MaterialEditor::setNormalMapping(NOU::boolean setFlag, const NOU::NOU_DAT_ALG::String8 &texturePath,
                                          const NOU::NOU_DAT_ALG::String8 &normalTexturePath, NOU::float32 scale,
                                          NOU::float32 offset)
    {
        if(setFlag == 1)
        {
            m_normalMapping = new NormalMapping(texturePath,normalTexturePath,scale,offset);
        }else {
            m_normalMapping = nullptr;
        }
    }

    void MaterialEditor::setParralaxMapping(NOU::boolean setFlag, const NOU::NOU_DAT_ALG::String8 &texturePath,
                                            const NOU::NOU_DAT_ALG::String8 &normalTexturePath,
                                            const NOU::NOU_DAT_ALG::String8 &displacementTexturePath,
                                            NOU::float32 scale, NOU::float32 offset)
    {
        if(setFlag == 1)
        {
            m_parrallaxMapping = new ParrallaxMapping(texturePath,normalTexturePath,displacementTexturePath,scale,offset);
        }else{
            m_parrallaxMapping = nullptr;
        }
    }

    void MaterialEditor::setColor(NOU::boolean setFlag)
    {

    }

    void MaterialEditor::setMaterialName(NOU::NOU_DAT_ALG::String8 name)
    {
        m_name = name;
    }

    const NOU::NOU_DAT_ALG::String8 & MaterialEditor::getMaterialName()
    {
        return m_name;
    }
}
