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