#include "nostraengine/material_system/GLSLPreProcessor.hpp"
#include "nostrautils/NostraUtils.hpp"

namespace NOE::NOE_MATSYS
{
    GLSLPreProcessor::GLSLPreProcessor(NOU::NOU_FILE_MNGT::File *src, NOU::NOU_FILE_MNGT::File *trg):
        PreProcessor(src, trg),
        m_currentState(State::DEFAULT) { }

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
        NOU::boolean b = false;
        for(NOU::sizeType i = 0; i < sizeof(TOKEN_SEPERATOR)/ sizeof(TOKEN_SEPERATOR[0]); i++) 
        {

        }
        return b;
    }

    const NOU::NOU_DAT_ALG::String8 &GLSLPreProcessor::CodeIterator::next()
    {
        return NOU::NOU_DAT_ALG::String8("");
    }


}