#include "nostraengine/material_system/GLSLPreProcessor.hpp"
#include "nostrautils/NostraUtils.hpp"

#include <stdlib.h>
#include <stdio.h>

namespace NOE::NOE_MATSYS
{
    GLSLPreProcessor::GLSLPreProcessor(NOU::NOU_FILE_MNGT::File *src, NOU::NOU_FILE_MNGT::File *trg):
        PreProcessor(src, trg),
        m_currentState(State::DEFAULT),
        m_lines() { }

    void GLSLPreProcessor::start(NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>)
    {
        
    }











    // +---------------+
    // | CODE ITERATOR |
    // +---------------+

    GLSLPreProcessor::CodeIterator::CodeIterator(const NOU::NOU_DAT_ALG::String8 &code):
    m_code(code),
    m_pos(0){ }

    void GLSLPreProcessor::CodeIterator::reset()
    {
        m_pos = 0;
        m_currToken = NOU::NOU_DAT_ALG::String8("");
    }

    const NOU::NOU_DAT_ALG::String8 &GLSLPreProcessor::CodeIterator::getCurrToken()
    {
        return m_currToken;
    }

    NOU::boolean GLSLPreProcessor::CodeIterator::hasNext()
    {
        NOU::boolean ret = getNextEnd() != -1;
        if(m_pos >= m_code.size())
        {
            ret = false;
        }
        return ret;
    }

    const NOU::NOU_DAT_ALG::String8 &GLSLPreProcessor::CodeIterator::next()
    {
        NOU::uint64 tmp = getNextEnd();
        m_currToken = m_code.substring(m_pos, tmp);
        m_pos = tmp + 1;
        return m_currToken;
    }

    NOU::int64 GLSLPreProcessor::CodeIterator::getNextEnd()
    {
        NOU::sizeType tmp, tmpPos;
        NOU::sizeType idx;
        NOU::sizeType arraySize = sizeof(TOKEN_SEPERATOR) / sizeof(TOKEN_SEPERATOR[0]);
        NOU::sizeType ret = -1;



        tmpPos = m_pos;
        idx = m_code.find(TOKEN_SEPERATOR[0], m_pos);   // find occurance of the first seperator in the array


        for(NOU::sizeType j = 1; j < arraySize; j++)    // for every other seperator
        {
            tmp = m_code.find(TOKEN_SEPERATOR[j], m_pos);   // find first occurance
            if(tmp == -1)                                // if no occurance found
            {
                continue;
            }

            if(idx > tmp)                                // if occurance is earlier than the previous
            {
                idx = tmp;
                continue;
            }

            idx = (idx < tmp) ? idx : tmp;
        }

        if(idx != -1)     // if overall occurance found
        {
            ret = idx;
            return ret;
        }

        if((m_pos < m_code.size() - 1))
        {
            ret = m_code.size() - 1;
        }

        return ret;
    }


}