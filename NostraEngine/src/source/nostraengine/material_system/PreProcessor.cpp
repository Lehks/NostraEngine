#include "nostraengine/material_system/PreProcessor.hpp"

namespace NOE::NOE_MATSYS
{
    PreProcessor::PreProcessor(NOU::NOU_FILE_MNGT::File *src, NOU::NOU_FILE_MNGT::File *trg):
    m_target(trg)
    {
    }

    PreProcessor(NOU::NOU_DAT_ALG::String8 *src = nullptr, NOU::NOU_FILE_MNGT *trg = nullptr):
    m_code(src),
    m_target(trg)
    { }

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


    /**
        \brief setter for the code
        \param code the sourcecode
        */
        void setCode(const NOU::NOU_DAT_ALG::String8 *code);

        /**
        \brief getter for the code
        \return A string containing the whole source code
        */
        const String8 *getCode();
}