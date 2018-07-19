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
        NOT::AbstractSyntaxTree::ASTNode *m_root;
        NOU::NOU_FILE_MNGT::File outputSourceFile;
        NOU::NOU_DAT_ALG::String8 outputSourceString;
        NOE_PLUGIN_FUNC virtual NOU::boolean processState(const NOT::AbstractSyntaxTree::ASTNode::Types & STATE) override;

        NOE_PLUGIN_FUNC void varDecState();
        NOE_PLUGIN_FUNC void bodyTypeState();
        NOE_PLUGIN_FUNC void retTypeState();
        NOE_PLUGIN_FUNC void varState();
        NOE_PLUGIN_FUNC void arrDefState();
        NOE_PLUGIN_FUNC void assignState();
        NOE_PLUGIN_FUNC void breakState();
        NOE_PLUGIN_FUNC void condState();
        NOE_PLUGIN_FUNC void constValueState();
        NOE_PLUGIN_FUNC void continueState();
        NOE_PLUGIN_FUNC void elseState();
        NOE_PLUGIN_FUNC void entryState();
        NOE_PLUGIN_FUNC void externState();
        NOE_PLUGIN_FUNC void forState();
        NOE_PLUGIN_FUNC void funcCallState();
        NOE_PLUGIN_FUNC void funcDecState();
        NOE_PLUGIN_FUNC void idState();
        NOE_PLUGIN_FUNC void ifState();
        NOE_PLUGIN_FUNC void keywordState();
        NOE_PLUGIN_FUNC void operatorState();
        NOE_PLUGIN_FUNC void paramState();
        NOE_PLUGIN_FUNC void paramListState();
        NOE_PLUGIN_FUNC void returnState();
        NOE_PLUGIN_FUNC void runVarState();
        NOE_PLUGIN_FUNC void sizeState();
        NOE_PLUGIN_FUNC void structDefState();
        NOE_PLUGIN_FUNC void typeState();
        NOE_PLUGIN_FUNC void varCallState();
        NOE_PLUGIN_FUNC void whileState();
        NOE_PLUGIN_FUNC void structCallState();

    public:
        NOE_PLUGIN_FUNC virtual NOU::boolean start(const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &paramArgs) override;
        NOE_PLUGIN_FUNC virtual NOU::boolean processTree(NOT::AbstractSyntaxTree::ASTNode *m_ast) override;
        NOE_PLUGIN_FUNC virtual NOU::boolean generateSource() override;

    };

}
#endif