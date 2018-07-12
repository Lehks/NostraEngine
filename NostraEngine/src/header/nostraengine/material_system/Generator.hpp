#ifndef MATERIAL_SYSTEM_GENERATOR_HPP
#define MATERIAL_SYSTEM_GENERATOR_HPP

#include "nostraengine/core/StdIncludes.hpp"

#include "nostrautils/NostraUtils.hpp"

namespace NOT
{
    class NOE_CLASS Generator
    {
    private:
        NOT::AbstractSyntaxTree     m_ast;

        NOU::NOU_FILE_MNGT::File    m_source;

        NOU::boolean processState(const NOT::AbstractSyntaxTress::ASTNodes::Types & STATE);

    public:

        Generator();

        const NOT::AbstractSyntaxTree & loadAbstractSyntaxTree();

        NOU::boolean processTree(const NOT::AbstractSyntaxTree & AST);

        NOU::boolean generateSource();

    };
}

#endif MATERIAL_SYSTEM_GENERATOR_HPP