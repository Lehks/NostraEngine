#ifndef PLUGIN_GLSL_GENERATOR_HPP
#define PLUGIN_GLSL_GENERATOR_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/NostraEngine.hpp"
#include "nostraengine/material_system/Generator.hpp"

/**
\file generator/GLSLGenerator.hpp

\author  Dennis Franz
\version 0.0.1
\since   0.0.1

\brief A Generator that generate GLSL code from a given AST.
*/
namespace GLSLGeneratorPlugin
{

    class GLSLGenerator : public NOE::NOE_MATSYS::Generator
    {
    private:
        NOE_PLUGIN_FUNC virtual NOU::boolean processState(const NOT::AbstractSyntaxTree::ASTNode::Types & STATE) override;
    public:
        NOE_PLUGIN_FUNC virtual NOU::boolean processTree(NOT::AbstractSyntaxTree::ASTNode *m_ast) override;
        NOE_PLUGIN_FUNC virtual NOU::boolean generateSource() override;
    };

}
#endif