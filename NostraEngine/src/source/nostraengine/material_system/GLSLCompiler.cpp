#include "nostraengine/material_system/GLSLCompiler.hpp"



namespace NOE::NOE_MATSYS
{
    GLSLCompiler():
        m_source(nullptr),
        m_target(nullptr)
    {

    }

    void GLSLCompiler::compile()
    {

    }

    void GLSLCompiler::generate()
    {
        if(m_source==nullptr)
        {
            NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::PATH_NOT_FOUND, "Sourcefile not found");
            return;
        }
        preProccessor();
    }

    void GLSLCompiler::setMaterial()
    {

    }

    void preProccessor()
    {

    }
}