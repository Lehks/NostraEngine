#include "nostraengine/material_system/PreProcessor.hpp"

namespace NOE::NOE_MATSYS
{
    PreProcessor::PreProcessor(NOU::NOU_FILE_MNGT::File *src, NOU::NOU_FILE_MNGT::File *trg):
    m_target(trg),
    m_source(src),
    m_code("")
    {
        src->open();
        NOU::sizeType s = src->size();
        for(NOU::sizeType i = 0; i < s; i++)
        {
            m_code.append(src->read());
        }

        // Needs a faster way of reading in
    }

    PreProcessor::PreProcessor(const NOU::NOU_DAT_ALG::String8 &code, NOU::NOU_FILE_MNGT::File *trg):
    m_code(code),
    m_target(trg),
    m_source(nullptr)
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
        void PreProcessor::setCode(const NOU::NOU_DAT_ALG::String8 &code)
        {
            m_code = code;
        }

        /**
        \brief getter for the code
        \return A string containing the whole source code
        */
        const NOU::NOU_DAT_ALG::String8 &PreProcessor::getCode()
        {
            return m_code;
        }
}