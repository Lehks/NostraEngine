#include "nostraengine/material_system/PreProcessor.hpp"


#define DEBUG_STUFF_

#ifdef DEBUG_STUFF
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
    const NOU::NOU_DAT_ALG::StringView8 PreProcessor::PRE_PROCESSOR_DIRECTIVE_PREFIX = "#";
    const NOU::NOU_DAT_ALG::StringView8 PreProcessor::PRE_PROCESSOR_INCLUDE = static_cast<NOU::NOU_DAT_ALG::StringView8>("include");

    PreProcessor::PreProcessor(NOU::NOU_FILE_MNGT::File &f, const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &args):
    m_targetCode(""),
    m_currState(States::DEFAULT),
    m_sourcePath(f.getPath())
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
        convertLineendings();
        Iterator it(m_sourceCode, s_tokenSeperators);
        NOU::NOU_DAT_ALG::String8 line = "";
        NOU::NOU_DAT_ALG::String8 tmpStr;
        NOU::sizeType pos;

        while(it.hasNext())
        {
            line = it.next();
            tmpStr = line;

            directive(it);

            switch(m_currState)
            {
                case States::DEFAULT:
                    m_targetCode.append(line);
                    break;
                case States::INCLUDE:
                    include(it);
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
            ts->emplaceBack("\n");
            NOT_PRINT(s_tokenSeperators.size());
        }
    }

    void PreProcessor::convertLineendings()
    {
        m_sourceCode.replace("\r\n", "\n");
    }

    // ------------------------DIRECTIVES------------------------

    void PreProcessor::directive(Iterator &it)
    {
        NOU::NOU_DAT_ALG::String8 s = it.getCurrentToken();
        s.trim();
        if(!s.startsWith(PRE_PROCESSOR_DIRECTIVE_PREFIX))
        {
            m_currState = States::DEFAULT;
            return;
        }
        s.remove(0,1);
        s.trim();

        if(s.find(PRE_PROCESSOR_INCLUDE) == 0){
            m_currState = States::INCLUDE;
        } else {
            m_currState = States::DEFAULT;
        }
    }

    void PreProcessor::include(Iterator &it)
    {
        /*
        TODO:
        - Add Error when second \" has not been found
        - Add Error when file has not been found
        - Add Warning when file has allready been included
        - Includes that are in a different root folder than the src
        */


        static NOU::NOU_DAT_ALG::Vector<NOU::NOU_FILE_MNGT::Path> allreadyIncluded;
        NOU::sizeType pos1, pos2, s;
        NOU::NOU_DAT_ALG::String8 tmp, pathString;

        tmp  = it.getCurrentToken();
        pos1 = tmp.find("\"") + 1;
        pos2 = tmp.find("\"", pos1);
        tmp.copySubstringTo(pathString, pos1, pos2);

        NOU::NOU_FILE_MNGT::Path p(m_sourcePath.getParentPath());
        p += pathString;

        s = allreadyIncluded.size();
        for(NOU::sizeType i = 0; i < s; i++)
        {
            if (p == allreadyIncluded[i])           // if File has been included allready
            {
                s = it.getCurrentToken().size();
                pos1 = it.getCurrentPosition()-s;
                s--;
                tmp = "";
                for(NOU::sizeType i = 0; i < s; i++)
                    {
                        tmp.append(" ");
                    }

                m_sourceCode.replace(pos1, s, tmp); // remove directive
                return;
            }
        }

        allreadyIncluded.emplaceBack(p);

        NOU::NOU_FILE_MNGT::File f(p);
        NOU::NOU_DAT_ALG::String8 includeCode;

        f.open();
        f.read(includeCode);
        f.close();


        s = it.getCurrentToken().size();
        pos1 = it.getCurrentPosition()-s;
        s--;
        tmp = "";
        for(NOU::sizeType i = 0; i < s; i++)
        {
            tmp.append(" ");
        }

        m_sourceCode.replace(pos1, s, tmp); // remove directive
        s++;
        m_sourceCode.insert(s, "\n");
        s++;
        m_sourceCode.insert(s, includeCode);

        #ifdef DEBUG_STUFF
            NOU::NOU_FILE_MNGT::File tmpf("C:/Users/Leslie/Desktop/NOMatTestFiles/out");
            if(tmpf.exists()){
                tmpf.deleteFile();
                tmpf.createFile();
            } else {
                tmpf.createFile();
            }
            tmpf.open();
            tmpf.write(m_sourceCode);
            tmpf.close();
        #endif
        

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
        b = m_currPos != m_currString.size();
        return b;
    }

    NOU::NOU_DAT_ALG::String8 &PreProcessor::Iterator::next() 
    {
        NOU::boolean b;
        NOU::sizeType tkSepCount, tmp, currSeperatorPos, min, nextPos;

        tkSepCount = m_tokenSeperators.size();
        nextPos = -1;
        b = true;
        for(NOU::sizeType i = 0; i < tkSepCount; i++)
        {   
            tmp = m_currString.find(m_tokenSeperators[i], m_currPos);

            b = b && (tmp == -1);

            nextPos = NOU::NOU_CORE::min(nextPos, tmp+1);
        }

        if(b)
        {
            nextPos = m_currString.size();
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

    NOU::sizeType PreProcessor::Iterator::getCurrentPosition() const
    {
        return m_currPos;
    }
}