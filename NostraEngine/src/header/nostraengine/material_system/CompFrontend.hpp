#ifndef MATERIAL_SYSTEM_COMP_FRONTEND_HPP
#define MATERIAL_SYSTEM_COMP_FRONTEND_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/material_system/AbstractSyntaxTree.hpp"

namespace NOT
{
    class NOE_FUNC CompFrontend final
    {
        using String = NOU::NOU_DAT_ALG::String<NOU::char8>;

        template<typename T>
        using Vector = NOU::NOU_DAT_ALG::Vector<T>;

        using Path = NOU::NOU_FILE_MNGT::Path;

        static CompFrontend* m_instance;
        Path m_source;
        Vector<String> m_options;
        Vector<String> m_errors;
        AbstractSyntaxTree m_ast;

        CompFrontend()
        { }

        CompFrontend(Path &source, Vector<String> &options) :
            m_options(options),
            m_source(source)
        { }

        CompFrontend(const CompFrontend& other) = delete;
        CompFrontend(CompFrontend&& other) = delete;
    public:

        static CompFrontend& getInstance();

        static CompFrontend& getInstance(Path &source, Vector<String> &options = Vector<String>());

        static void createInstance(Path &source, Vector<String> &options);

        ~CompFrontend();

        NOU::boolean start(); 

        const Vector<String>& getErrors();

        Path& getSource();

        Vector<String>& getOptions();

        const AbstractSyntaxTree& getAbstractSyntaxTree();

    };
}

#endif