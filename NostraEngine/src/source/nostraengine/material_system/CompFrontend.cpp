#include "nostraengine/material_system/CompFrontend.hpp"
#include <stdlib.h>

#include <iostream>
using namespace std;


extern "C"{
    void setInput(char* code);
    void yyparse();
    char* syntaxErrorMsg;
}

using String = NOU::NOU_DAT_ALG::String<NOU::char8>;

template<typename T>
using Vector = NOU::NOU_DAT_ALG::Vector<T>;

using Path = NOU::NOU_FILE_MNGT::Path;

using File = NOU::NOU_FILE_MNGT::File;

namespace NOT
{
    CompFrontend* CompFrontend::m_instance = nullptr;

    CompFrontend::CompFrontend(Path &source, Vector<String> &options) :
            m_options(options),
            m_source(source)
            {
            }

    CompFrontend::CompFrontend()
    {
    }

    CompFrontend& CompFrontend::getInstance()
    {
        if(!m_instance){
            m_instance = new CompFrontend();
        }
        return *m_instance;
    }

    CompFrontend& CompFrontend::getInstance(Path &source, Vector<String> &options)
    {
        createInstance(source, options);
        return *m_instance;
    }

    void CompFrontend::createInstance(Path &source, Vector<String> &options)
    {
        if(!m_instance){
            delete m_instance;
        }

        m_instance = new CompFrontend(source, options);

    }

    Path& CompFrontend::getSource()
    {
        return m_source;
    }

    Vector<String>& CompFrontend::getOptions()
    {
        return m_options;
    }

    CompFrontend::~CompFrontend()
    {
        if(syntaxErrorMsg != 0){
            free(syntaxErrorMsg);
        }
    }

    NOU::boolean CompFrontend::start()
    {
        m_errorsFetched = false;
        File f(m_source);
        String code;
        f.open(NOU::NOU_FILE_MNGT::AccessMode::READ);
        f.read(code);
        f.close();

        code.append(' ');
        code.append('\0');

        char* codeRaw = const_cast<char*>(code.rawStr());

        setInput(codeRaw);

        yyparse();


        return syntaxErrorMsg == 0;
    }

    const AbstractSyntaxTree& CompFrontend::getAbstractSyntaxTree()
    {
        return m_ast;
    }

    const Vector<String>& CompFrontend::getErrors()
    {
        if(!m_errorsFetched){
            fetchErrors();
        }

        return m_errors;
    }

    void CompFrontend::fetchErrors()
    {
        m_errorsFetched = true;

        if(syntaxErrorMsg == 0){
            return;
        }
        String raw(syntaxErrorMsg);

        NOU::sizeType pos;

        while(raw.size() != 0){
            pos = raw.find('|');
            m_errors.emplaceBack(raw.substring(0, pos));
            raw.remove(0, pos+1);
        }
    }
}   