#include "nostraengine/material_system/PreProcessor.hpp"

namespace NOE::NOE_MATSYS
{
    PreProcessor::PreProcessor(const File *src, const File *trg):
    m_source(src),
    m_target(trg)
    {

    }

    void PreProcessor::setSource(const File *src)
    {
        m_source = src;
    }

    void PreProcessor::setTarget(const File *trg)
    {
        m_target = trg;
    }

    const File *getSource()
    {
        return m_source;
    }

    const File *PreProcessor::getTarget()
    {
        return m_targets;
    }
}