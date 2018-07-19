// #ifndef PLUGIN_GLSL_GENERATOR_HPP
// #define PLUGIN_GLSL_GENERATOR_HPP

// #include "nostrautils/NostraUtils.hpp"
// #include "nostraengine/NostraEngine.hpp"
// #include "nostraengine/material_system/Generator.hpp"

// /**
// \file generator/GLSLGenerator.hpp

// \author  Dennis Franz
// \version 0.0.1
// \since   0.0.1

// \brief A Generator that generate GLSL code from a given AST.
// */
// namespace GLSLGeneratorPlugin
// {

//     class GLSLGenerator : public NOE::NOE_MATSYS::Generator
//     {
//     private:
//         NOT::AbstractSyntaxTree::ASTNode    *m_root;
//         NOT::AbstractSyntaxTree::ASTNode    *currentNode;
//         NOT::AbstractSyntaxTree::ASTNode    *prevNode;
//         NOT::AbstractSyntaxTree             m_ast;
//         NOU::NOU_FILE_MNGT::File            m_outputSourceFile;
//         NOU::NOU_DAT_ALG::String8           m_outputSourceString;
//         NOE_PLUGIN_FUNC NOU::sizeType processState(const NOT::AbstractSyntaxTree::ASTNode::Types & STATE) override;

//         NOE_PLUGIN_FUNC NOU::sizeType  varDecState();
//         NOE_PLUGIN_FUNC NOU::sizeType  bodyState();
//         NOE_PLUGIN_FUNC NOU::sizeType  retTypeState();
//         NOE_PLUGIN_FUNC NOU::sizeType  varState();
//         NOE_PLUGIN_FUNC NOU::sizeType  arrDefState();
//         NOE_PLUGIN_FUNC NOU::sizeType  assignState();
//         NOE_PLUGIN_FUNC NOU::sizeType  breakState();
//         NOE_PLUGIN_FUNC NOU::sizeType  condState();
//         NOE_PLUGIN_FUNC NOU::sizeType  constValueState();
//         NOE_PLUGIN_FUNC NOU::sizeType  continueState();
//         NOE_PLUGIN_FUNC NOU::sizeType  elseState();
//         NOE_PLUGIN_FUNC NOU::sizeType  entryState();
//         NOE_PLUGIN_FUNC NOU::sizeType  externState();
//         NOE_PLUGIN_FUNC NOU::sizeType  forState();
//         NOE_PLUGIN_FUNC NOU::sizeType  funcCallState();
//         NOE_PLUGIN_FUNC NOU::sizeType  funcDecState();
//         NOE_PLUGIN_FUNC NOU::sizeType  idState();
//         NOE_PLUGIN_FUNC NOU::sizeType  ifState();
//         NOE_PLUGIN_FUNC NOU::sizeType  operatorState();
//         NOE_PLUGIN_FUNC NOU::sizeType  paramState();
//         NOE_PLUGIN_FUNC NOU::sizeType  paramListState();
//         NOE_PLUGIN_FUNC NOU::sizeType  returnState();
//         NOE_PLUGIN_FUNC NOU::sizeType  runVarState();
//         NOE_PLUGIN_FUNC NOU::sizeType  sizeState();
//         NOE_PLUGIN_FUNC NOU::sizeType  structDefState();
//         NOE_PLUGIN_FUNC NOU::sizeType  varCallState();
//         NOE_PLUGIN_FUNC NOU::sizeType  whileState();
//         NOE_PLUGIN_FUNC NOU::sizeType  structCallState();

//     public:
//         NOE_PLUGIN_FUNC GLSLGenerator(NOT::AbstractSyntaxTree &ast);
//         NOE_PLUGIN_FUNC NOU::boolean start(const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &paramArgs) override;
//         NOE_PLUGIN_FUNC NOU::boolean processTree(NOT::AbstractSyntaxTree::ASTNode *m_ast) override;
//         NOE_PLUGIN_FUNC NOU::boolean generateSource() override;

//     };

// }
// #endif