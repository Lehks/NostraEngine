#include "nostraengine/material_system/ShaderCompiler.hpp"

namespace NOE::NOE_MATSYS
{
    void ShaderCompiler::setSource(const File &src)
    {
        m_source = src;
    }

    const File& ShaderCompiler::getTarget()
    {
        return m_target;
    }
}