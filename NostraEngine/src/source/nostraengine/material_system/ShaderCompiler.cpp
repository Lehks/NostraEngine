#include "nostraengine/material_system/ShaderCompiler.hpp"
#include "nostraengine/core/StdIncludes.hpp"


namespace NOE::NOE_MATSYS
{
    void ShaderCompiler::setSource(NOU::NOU_FILE_MNGT::File *src)
    {
        m_source = src;
    }

    NOU::NOU_FILE_MNGT::File &ShaderCompiler::getTarget()
    {
        return *m_target;
    }

    void ShaderCompiler::setTarget(NOU::NOU_FILE_MNGT::File *trg)
    {
        m_target = trg;
    }

    void ShaderCompiler::setPreProcessedTarget(NOU::NOU_FILE_MNGT::File *pp)
    {
        m_processed = pp;
    }

    NOU::NOU_FILE_MNGT::File *ShaderCompiler::getPreProcessedTarget()
    {
        return m_processed;
    }

    void ShaderCompiler::setPreProcessor(PreProcessor *pp){
        m_preprocessor = pp;
    }

    void ShaderCompiler::process()
    {
        //m_processed->start();
    }
}