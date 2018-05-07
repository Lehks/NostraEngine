#include "nostraengine/material_system/PreProcessor.hpp"

namespace NOE::NOE_MATSYS
{
    PreProcessor::PreProcessor(NOU::NOU_FILE_MNGT::File *src, NOU::NOU_FILE_MNGT::File *trg):
    m_source(src),
    m_target(trg)
    {

    }

    void PreProcessor::setSource(const NOU::NOU_FILE_MNGT::File *src)
    {
        m_source = const_cast<NOU::NOU_FILE_MNGT::File*>(src);
    }

    void PreProcessor::setTarget(NOU::NOU_FILE_MNGT::File *trg)
    {
        m_target = const_cast<NOU::NOU_FILE_MNGT::File*>(trg);
    }

    NOU::NOU_FILE_MNGT::File *PreProcessor::getSource()
    {
        return m_source;
    }

    NOU::NOU_FILE_MNGT::File *PreProcessor::getTarget()
    {
        return m_target;
    }
}