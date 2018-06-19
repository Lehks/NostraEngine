#include "nostraengine/material_system/PreProcessor.hpp"


/**
TODO:
- Refactoring
- Add method for adding DefineVars
- Add argument to add defines before starting the preprocessor
- make NOT expand to nostra::tools
- start making more terrible jokes
- use exceptions for warnings and Errors.
*/



#define DEBUG_STUFF_

#ifdef DEBUG_STUFF
#   include <iostream>
#   define NOT_PRINT(ARG) std::cout<<ARG<<std::endl
    void dbgPrintFile(NOU::NOU_DAT_ALG::String8 s)
    {
        NOU::sizeType counter, pos;
        NOU::NOU_DAT_ALG::String8 replacement;

        counter = 0;
        replacement = "\\n\n";

        for(NOU::sizeType i = 0; i < s.size(); i++)
        {
            if(counter != 0){
                counter--;
                continue;
            }
            if(s[i] == '\n')
            {
                s.remove(i, i+1);
                s.insert(i, replacement);
                counter += replacement.size()-1;
            }

        }

        counter = 0;
        replacement = "_";

        for(NOU::sizeType i = 0; i < s.size(); i++)
        {
            if(counter != 0){
                counter--;
                continue;
            }
            if(s[i] == ' ')
            {
                s.remove(i, i+1);
                s.insert(i, replacement);
                counter += replacement.size()-1;
            }

        }

        std::cout << s.rawStr() << std::endl;
        std::cout << "------" << std::endl;
    }
#   define NOT_PRINT_FILE(ARG) dbgPrintFile(ARG)
#   define NOT_PRINT_CODE NOT_PRINT_FILE(m_sourceCode)
#else
#   define NOT_PRINT(ARG)
#   define NOT_PRINT_FILE(ARG)
#   define NOT_PRINT_CODE
#endif

namespace NOT
{

    const NOU::NOU_DAT_ALG::HashMap<PreProcessor::ErrorCode, NOU::NOU_DAT_ALG::String8> PreProcessor::s_errors;
    const NOU::NOU_DAT_ALG::HashMap<PreProcessor::WarningCode, NOU::NOU_DAT_ALG::String8> PreProcessor::s_warnings;
    const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> PreProcessor::s_tokenSeperators;

    // -------PRE PROCESSOR KEYWORDS-------
    const NOU::NOU_DAT_ALG::StringView8 PreProcessor::PRE_PROCESSOR_DIRECTIVE_PREFIX = "#";
    const NOU::NOU_DAT_ALG::StringView8 PreProcessor::PRE_PROCESSOR_INCLUDE = "include";
    const NOU::NOU_DAT_ALG::StringView8 PreProcessor::PRE_PROCESSOR_DEFINE = "define";
    

    PreProcessor::PreProcessor(NOU::NOU_FILE_MNGT::File &f, const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &args):
    m_targetCode(""),
    m_currState(States::DEFAULT),
    m_sourcePath(f.getPath()),
    m_defineVars(100)
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
                    // defaultDirective(it);
                    break;
                case States::INCLUDE:
                    // include(it);
                    break;
                case States::DEFINE:
                    // define(it);
                    break;
            }
        }
    }

    void PreProcessor::initializeStaticMembers()
    {
        if(s_errors.size() == 0)
        {
            ErrorCode i = 0;
            NOU::NOU_DAT_ALG::HashMap<ErrorCode, NOU::NOU_DAT_ALG::String8> *ec = const_cast<NOU::NOU_DAT_ALG::HashMap<ErrorCode, NOU::NOU_DAT_ALG::String8>*>(&s_errors);
            ec->map(i++, "Test");
            NOT_PRINT(s_errors.size());
        }

        if(s_warnings.size() == 0)
        {
            WarningCode i = 0;
            NOU::NOU_DAT_ALG::HashMap<WarningCode, NOU::NOU_DAT_ALG::String8> *wc = const_cast<NOU::NOU_DAT_ALG::HashMap<WarningCode, NOU::NOU_DAT_ALG::String8>*>(&s_errors);
            wc->map(i++, "Test");
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

        if(s.find(PRE_PROCESSOR_INCLUDE) == 0)
        {
            m_currState = States::INCLUDE;
        } else if(s.find(PRE_PROCESSOR_DEFINE) == 0) 
        {
            m_currState = States::DEFINE;
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
                NOT_PRINT(m_sourceCode.rawStr());
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

        NOT_PRINT_CODE;

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

    void PreProcessor::define(Iterator &it)
    {

        /*
        TODO:
        - Add Error for missing ")"
        - Add Error for incorrect syntax
        - Add Warning for allready defined names
        - Add actual replacing of defines in the src Code
        */
        NOU::sizeType pos, s;
        NOU::NOU_DAT_ALG::String8 currLine, tmp;
        NOT_PRINT_FILE(m_sourceCode);
        currLine = it.getCurrentToken();
        s = currLine.size();
        currLine.trim();
        currLine.remove(0, PRE_PROCESSOR_DIRECTIVE_PREFIX.size());
        currLine.trim();
        currLine.remove(0, PRE_PROCESSOR_DEFINE.size());
        currLine.trim();

        pos = currLine.find(" ");
        if(currLine.find("(") > pos){
            NOU::NOU_DAT_ALG::String8 name, value;
            currLine.copySubstringTo(name, 0, pos);
            currLine.remove(0, pos+1);
            value = currLine;
            s--;
            for(NOU::sizeType i = 0; i < s; i++)
            {
                tmp.append(" ");
            }
            pos = it.getCurrentPosition() - it.getCurrentToken().size() - 1;
            m_sourceCode.replace(pos, tmp.size(), tmp);
        }
    }

    void PreProcessor::defaultDirective(Iterator &it)
    {
        NOU::NOU_DAT_ALG::String8 line;
        NOU::sizeType s;

        line = it.getCurrentPosition();
        s = m_defineVars.size();
        for(NOU::sizeType i = 0; i < s; i++)
        {
            m_defineVars[i];
        }

        m_targetCode.append(line);
    }
    // ------------------------HELPER-FUNCTIONS------------------

    NOU::boolean PreProcessor::addDefineVar(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_DAT_ALG::String8 &value)
    {
        /* TODO:
        - if var is allready contained throw warning
        */
        
        NOU::sizeType s;

        s = m_defineVars.size();
        for (auto &s : m_defineVars)
        {
            if(s.name == name)
            {
                // add warning throw here
                return false;
            }
            m_defineVars.emplaceBack(name, value);
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
        NOU::sizeType s = m_currString.size();
        /* #ifdef DEBUG_STUFF
        if(m_currPos > 60)
        {   
            const NOU::char8 *tmp = m_currString.rawStr();
            std::cout << m_currString.rawStr() << std::endl;
        }
        #endif */
        b = m_currPos < s;
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
        NOT_PRINT("Iterator.position: " << m_currPos);
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

    // ------------------------EXCEPTION-SYSTEM-------------------------------

    // Message

    PreProcessor::Message::Message(const NOU::NOU_DAT_ALG::String8 &message, const NOU::uint64 line):
    m_message(message),
    m_line(line)
    { }

    const NOU::NOU_DAT_ALG::String8& PreProcessor::Message::getMessage() const
    {
        return m_message;
    }

    NOU::uint64 PreProcessor::Message::getLine() const
    {
        return m_line;
    }

    PreProcessor::ErrorCode PreProcessor::Error::getID() const
    {
        return m_id;
    }

    const NOU::NOU_DAT_ALG::String8& PreProcessor::Error::getErrorMessage() const
    {
        static NOU::NOU_DAT_ALG::String8 tmp("");
        /* if (s_errors.containsKey(m_id))
        {
            return s_errors.get(m_id);
        }*/
        return tmp;
    }

    PreProcessor::WarningCode PreProcessor::Warning::getID() const
    {
        return m_id;
    }

}