#include "nostraengine/material_system/ShaderCompiler.hpp"

namespace NOE::NOE_MATSYS
{
    void ShaderCompiler::setSource(const NOU::NOU_FILE_MNGT::File &src)
    {
        m_source = &src;
    }

    const NOU::NOU_FILE_MNGT::File& ShaderCompiler::getTarget()
    {
        return *m_target;
    }
}