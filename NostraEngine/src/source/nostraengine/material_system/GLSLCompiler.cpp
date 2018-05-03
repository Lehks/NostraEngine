#include "nostraengine/material_system/GLSLCompiler.hpp"



namespace NOE
{
    namespace NOE_MATSYS
    {
        GLSLCompiler::GLSLCompiler()
        {
            m_source = nullptr;
            m_target = nullptr;
        }

        void GLSLCompiler::compile()
        {

        }

        void GLSLCompiler::generate()
        {
            if(m_source==nullptr)
            {
                NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), NOU::NOU_CORE::ErrorCodes::CANNOT_OPEN_FILE, "Sourcefile not found");
                return;
            }
            //preProccessor();
        }

        void GLSLCompiler::setMaterial()
        {

        }

        void GLSLCompiler::preProcessor()
        {

        }

        void GLSLCompiler::lex()
        {

        }
    }
}