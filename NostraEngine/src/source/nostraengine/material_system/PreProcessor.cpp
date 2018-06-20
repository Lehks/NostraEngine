#include "nostraengine/material_system/PreProcessor.hpp"


/**
TODO:
- Refactoring
- Add method for adding DefineVars
- Add argument to add defines before starting the preprocessor
- make NOT expand to nostra::tools
- start making more terrible jokes
- use exceptions for warnings and Errors.
- rebame DEBUG_STUFF
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
    const NOU::NOU_DAT_ALG::StringView8 PreProcessor::PRE_PROCESSOR_ERROR = "error";
    

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
                    // includeDirective(it);
                    break;
                case States::DEFINE:
                    // defineDirective(it);
                    break;
                case States::ERROR:
                    errorDirective(it);
            }
        }
    }

    void PreProcessor::initializeStaticMembers()
    {
        if(s_errors.size() == 0)
        {
            ErrorCode i = 0;
            NOU::NOU_DAT_ALG::HashMap<ErrorCode, NOU::NOU_DAT_ALG::String8> *ec = const_cast<NOU::NOU_DAT_ALG::HashMap<ErrorCode, NOU::NOU_DAT_ALG::String8>*>(&s_errors);
            ec->map(i++, "User Defined");
            NOT_PRINT(s_errors.size());
        }

        if(s_warnings.size() == 0)
        {
            WarningCode i = 0;
            NOU::NOU_DAT_ALG::HashMap<WarningCode, NOU::NOU_DAT_ALG::String8> *wc = const_cast<NOU::NOU_DAT_ALG::HashMap<WarningCode, NOU::NOU_DAT_ALG::String8>*>(&s_errors);
            wc->map(i++, "User Defined");
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
        if(m_currState != States::DEFAULT){ 
            return;
        }
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
        } else if(s.find(PRE_PROCESSOR_ERROR) == 0){
            m_currState = States::ERROR;
        } else {
            m_currState = States::DEFAULT;
        }
    }

    void PreProcessor::includeDirective(Iterator &it)
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

    void PreProcessor::defineDirective(Iterator &it)
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

    void PreProcessor::errorDirective(Iterator &it)
    {
        NOU::NOU_DAT_ALG::String8 tmp(it.getCurrentToken());
        
        // temporary solution until new NOU Release
        tmp.trim();
        tmp.remove(0, PRE_PROCESSOR_ERROR.size());
        tmp.trim();
        emitError(Error(0, tmp));
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
    m_line(line),
    m_constructedMessage((line == NO_LINE_DISPLAY ? NOU::NOU_DAT_ALG::String8("") : 
    (NOU::NOU_DAT_ALG::String8("(") + NOU::NOU_DAT_ALG::String8(m_line) + NOU::NOU_DAT_ALG::String8(")"))) + 
    NOU::NOU_DAT_ALG::String8(message))
    { }

    const NOU::NOU_DAT_ALG::String8& PreProcessor::Message::getMessage() const
    {
        return m_message;
    }

    NOU::uint64 PreProcessor::Message::getLine() const
    {
        return m_line;
    }

    NOU::boolean PreProcessor::Message::operator==(const Message &other) const
    {
        NOU::boolean b;
        b = getLine() == other.getLine();
        b &= getMessage() == other.getMessage();
        return b;
    }

    const NOU::NOU_DAT_ALG::String8& PreProcessor::Message::getConstructedMessage() const
    {
        return m_constructedMessage;
    }

    // Error

    PreProcessor::Error::Error(ErrorCode id, const NOU::NOU_DAT_ALG::String8 &message, NOU::uint64 line):
    Message(message, line),
    m_id(id)
    {
        NOU::NOU_DAT_ALG::String8 *tmp = const_cast<NOU::NOU_DAT_ALG::String8*>(&m_constructedMessage);
        tmp->clear();
        if(getLine() != NO_LINE_DISPLAY)
        {
            tmp->append("(");
            tmp->append(getLine());
            tmp->append(")");
        }
        tmp->append("PPE");
        tmp->append(getID());
        tmp->append(" ");
        tmp->append(getErrorMessage());
        if(getMessage() != "")  // TODO: Change to String::EMPTY STRING
        {
            tmp->append(" : ");
            tmp->append(getMessage());
        }
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

    NOU::boolean PreProcessor::Error::operator==(const Error &other) const
    {
        NOU::boolean b;
        b = this->Message::operator==(other);
        b &= getID() == other.getID();
        return b;
    }

    // Warning

    PreProcessor::Warning::Warning(WarningCode id, const NOU::NOU_DAT_ALG::String8 &message, NOU::uint64 line):
    Message(message, line),
    m_id(id)
    {
        NOU::NOU_DAT_ALG::String8 *tmp = const_cast<NOU::NOU_DAT_ALG::String8*>(&m_constructedMessage);
        tmp->clear();
        if(getLine() != NO_LINE_DISPLAY)
        {
            tmp->append("(");
            tmp->append(getLine());
            tmp->append(")");
        }
        tmp->append("PPW");
        tmp->append(getID());
        tmp->append(" ");
        tmp->append(getWarningMessage());
        if(getMessage() != "")  // TODO: Change to String::EMPTY STRING
        {
            tmp->append(" : ");
            tmp->append(getMessage());
        }
        
    }

    PreProcessor::WarningCode PreProcessor::Warning::getID() const
    {
        return m_id;
    }

    const NOU::NOU_DAT_ALG::String8& PreProcessor::Warning::getWarningMessage() const
    {
        static NOU::NOU_DAT_ALG::String8 tmp("testWarningMessage");
        /* if (s_warnings.containsKey(m_id))
        {
            return s_warnings.get(m_id);
        }*/
        return tmp;
    }

    NOU::boolean PreProcessor::Warning::operator== (const Message &other) const
    {
        NOU::boolean b;

        b = this->Message::operator==(other);
        b &= getID(), getID();

        return b; 
    }

    // emmitting Messages

    void PreProcessor::emitMessage(const Message &m)
    {
        m_messages.pushBack(m);
    }

    void PreProcessor::emitError(const Error &e)
    {
        m_errors.pushBack(e);
        // throw e; // Disabled because of debugging
    }

    void PreProcessor::emitWarning(const Warning &w)
    {
        m_warnings.pushBack(w);
    }

    const NOU::NOU_DAT_ALG::Vector<PreProcessor::Warning>& PreProcessor::getThrownWarnings()
    {
        return m_warnings;
    }

    const NOU::NOU_DAT_ALG::Vector<PreProcessor::Error>& PreProcessor::getThrownErrors()
    {
        return m_errors;
    }

    const NOU::NOU_DAT_ALG::Vector<PreProcessor::Message>& PreProcessor::getThrownMessages()
    {
        return m_messages;
    }

    const NOU::NOU_DAT_ALG::Vector<const PreProcessor::Message*> PreProcessor::getAllThrownMessages()
    {
        NOU::NOU_DAT_ALG::Vector<const PreProcessor::Message*> ret;
        NOU::sizeType s;

        // errors
        s = m_errors.size();
        for(NOU::sizeType i = 0; i < s; i++)
        {
            ret.pushBack(&m_errors[i]);
        }

        // warnings
        s = m_warnings.size();
        for(NOU::sizeType i = 0; i < s; i++)
        {
            ret.pushBack(&m_warnings[i]);
        }

        // messages
        s = m_messages.size();
        for(NOU::sizeType i = 0; i < s; i++)
        {
            ret.pushBack(&m_messages[i]);
        }

        return ret;
    }

}