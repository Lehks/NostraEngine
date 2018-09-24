#include "nostraengine/material_system/CompFrontend.hpp"
extern "C"{
    void setInput(char* code);
    void yyparse();
}

using String = NOU::NOU_DAT_ALG::String<NOU::char8>;

template<typename T>
using Vector = NOU::NOU_DAT_ALG::Vector<T>;

using Path = NOU::NOU_FILE_MNGT::Path;

using File = NOU::NOU_FILE_MNGT::File;

namespace NOT
{
    CompFrontend* CompFrontend::m_instance = nullptr;

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
        delete m_instance;
    }

    NOU::boolean CompFrontend::start()
    {
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


        return m_errors.empty();
    }

    const AbstractSyntaxTree& CompFrontend::getAbstractSyntaxTree()
    {
        return m_ast;
    }
}   