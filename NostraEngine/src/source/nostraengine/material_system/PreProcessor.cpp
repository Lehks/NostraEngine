#include "nostraengine/material_system/PreProcessor.hpp"


#define DEBUG_PRINTS_PRE_PROCESSOR_

#ifdef DEBUG_PRINTS_PRE_PROCESSOR
#   include <iostream>
#   define NOT_PRINT(ARG) std::cout<<ARG<<std::endl
#else
#   define NOT_PRINT(ARG)
#endif

namespace NOT
{

    const NOU::NOU_DAT_ALG::HashMap<PreProcessor::ErrorCode, NOU::NOU_DAT_ALG::String8> PreProcessor::s_errors;
    const NOU::NOU_DAT_ALG::HashMap<PreProcessor::WarningCode, NOU::NOU_DAT_ALG::String8> PreProcessor::s_warnings;
    const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> PreProcessor::s_tokenSeperators;

    //-------PRE PROCESSOR KEYWORDS-------
    static const NOU::NOU_DAT_ALG::StringView8 PRE_PROCESSOR_DIRECTIVE_PREFIX = "#";
    static const NOU::NOU_DAT_ALG::StringView8 PRE_PROCESSOR_INCLUDE = static_cast<NOU::NOU_DAT_ALG::StringView8>("include");

    PreProcessor::PreProcessor(NOU::NOU_FILE_MNGT::File &f, const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &args):
    m_targetCode(""),
    m_currState(States::DEFAULT)
    {
        initializeStaticMembers();
        if(f.isCurrentlyOpen())
        {
            f.close();
        }
        f.open();
        f.read(m_sourceCode);
        f.close();
    }

    void PreProcessor::start()
    {
        Iterator it(m_sourceCode, s_tokenSeperators);
        NOU::sizeType tokenSize;
        NOU::NOU_DAT_ALG::String8 &s = it.getCurrentToken();
        NOU::boolean b;
        NOU::char8 currChar;
        m_targetCode;

        while(it.hasNext())
        {
            s = it.next();
            tokenSize = s.size();
            b = false;
            s = s.trim();
            directive(it);


            switch(m_currState)
            {
                case States::DEFAULT:
                    m_targetCode.append(s);
                    m_targetCode.append('\n');
                    break;
                case States::INCLUDE:
                    break;

            }




        }
    }

    void PreProcessor::initializeStaticMembers()
    {
        if(s_errors.size() == 0)
        {
            NOU::NOU_DAT_ALG::HashMap<ErrorCode, NOU::NOU_DAT_ALG::String8> *ec = const_cast<NOU::NOU_DAT_ALG::HashMap<ErrorCode, NOU::NOU_DAT_ALG::String8>*>(&s_errors);
            ec->map(1, "Test");
            NOT_PRINT(s_errors.size());
        }

        if(s_warnings.size() == 0)
        {
            NOU::NOU_DAT_ALG::HashMap<WarningCode, NOU::NOU_DAT_ALG::String8> *wc = const_cast<NOU::NOU_DAT_ALG::HashMap<WarningCode, NOU::NOU_DAT_ALG::String8>*>(&s_errors);
            wc->map(1, "Test");
            NOT_PRINT(s_warnings.size());
        }

        if(s_tokenSeperators.size() == 0)
        {
            NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> *ts = const_cast<NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>*>(&s_tokenSeperators);
            ts->emplaceBack(";");
            ts->emplaceBack("{");
            NOT_PRINT(s_tokenSeperators.size());
        }
    }

    // ------------------------DIRECTIVES------------------------

    void PreProcessor::directive(Iterator &it)
    {
        NOU::NOU_DAT_ALG::String8 *s = const_cast<NOU::NOU_DAT_ALG::String8*>(&it.getCurrentToken());
        s->trim();
        if(!s->startsWith(PRE_PROCESSOR_DIRECTIVE_PREFIX))
        {
            m_currState = States::DEFAULT;
            return;
        }
        s->remove(0,1);
        s->trim();




        if(s->find(PRE_PROCESSOR_INCLUDE) == 0){
            m_currState = States::INCLUDE;
        } else {
            m_currState = States::DEFAULT;
        }
    }

    // ------------------------ITERATOR--------------------------

    PreProcessor::Iterator::Iterator(const NOU::NOU_DAT_ALG::String8 &s, const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &tokenSeperators, NOU::sizeType pos):
    m_currString(s),
    m_currToken(""),
    m_tokenSeperators(tokenSeperators),
    m_currPos(pos)
    { }

    NOU::boolean PreProcessor::Iterator::hasNext() const
    {
        NOU::boolean b;
        b = m_currPos != m_currString.size() -1;
        return b;
    }

    const NOU::NOU_DAT_ALG::String8 &PreProcessor::Iterator::next() 
    {
        NOU::boolean b;
        NOU::sizeType tkSepCount, tmp, currSeperatorPos, min, nextPos;

        tkSepCount = m_tokenSeperators.size();
        nextPos = -1;
        b = true;
        /*
           b -> init      -> true  !-> false
           ; -> not found -> false !-> true
           { -> not found -> false !-> true
        */
        for(NOU::sizeType i = 0; i < tkSepCount; i++)
        {   
            tmp = m_currString.find(m_tokenSeperators[i], m_currPos);

            b = b && (tmp == -1);

            nextPos = NOU::NOU_CORE::min(nextPos, tmp+1);
        }

        if(b)
        {
            nextPos = m_currString.size() - 1;
        }
        m_currToken.clear();
        m_currString.copySubstringTo(m_currToken, m_currPos, nextPos);
        m_currPos = nextPos;
        return m_currToken;
    }
    
    const NOU::NOU_DAT_ALG::String8 &PreProcessor::Iterator::getCurrentToken() const
    {
        NOU_LOG_DEBUG(m_currToken);
        return m_currToken;
    }

    NOU::NOU_DAT_ALG::String8 &PreProcessor::Iterator::getCurrentToken()
    {
        NOU_LOG_DEBUG(m_currToken);
        return m_currToken;
    }
}