#include "nostraengine/material_system/ShaderCompiler.hpp"

namespace NOE::NOE_MATSYS
{
    void ShaderCompiler::setSource(const NOU::NOU_FILE_MNGT::File *src)
    {
        m_source = src;
    }

    const NOU::NOU_FILE_MNGT::File &ShaderCompiler::getTarget()
    {
        return m_target;
    }

    void ShaderCompiler::setTarget(const NOU::NOU_FILE_MNGT::File *trg)
    {
        m_target = trg
    }

    void ShaderCompiler::setPreProcessedTarget(const NOU::NOU_FILE_MNGT::File *pp)
    {
        m_processed = pp;
    }

    const NOU::NOU_FILE_MNGT::File *Shadercompiler::getPreProcessedTarget()
    {
        return m_processed;
    }

    void ShaderCompiler::process()
    {
        m_processed->start();
    }
}