#ifndef MATERIAL_SYSTEM_GENERATOR_HPP
#define MATERIAL_SYSTEM_GENERATOR_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/material_system/AbstractSyntaxTree.hpp"

#include "nostrautils/NostraUtils.hpp"

namespace NOE::NOE_MATSYS
{
    class Generator
    {
    private:

        virtual NOU::boolean processState(const NOT::AbstractSyntaxTree::ASTNode::Types & STATE) = 0;

    public:

        virtual ~Generator() = default;

        virtual NOU::boolean start(const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &paramArgs) = 0;

        virtual NOU::boolean processTree(NOT::AbstractSyntaxTree::ASTNode *m_ast) = 0;

        virtual NOU::boolean generateSource() = 0;

    };
}

#endif MATERIAL_SYSTEM_GENERATOR_HPP