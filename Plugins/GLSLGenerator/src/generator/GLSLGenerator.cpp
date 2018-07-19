// #include "GLSLGenerator.hpp"

// namespace GLSLGeneratorPlugin
// {

//         NOU::sizeType GLSLGenerator::processState(const NOT::AbstractSyntaxTree::ASTNode::Types &STATE)
//         {
//             switch(STATE)
//             {
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::VAR_DEC:
//                     varDecState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::BODY:
//                     bodyState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::RET_TYPE:
//                     retTypeState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::VAR:
//                     varState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::ARR_DEF:
//                     arrDefState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::ASSIGN:
//                     assignState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::BREAK:
//                     breakState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::COND:
//                     condState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::CONST_VAL:
//                     constValueState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::CONTINUE:
//                     continueState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::ELSE:
//                     elseState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::ENTRY:
//                     entryState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::EXTERN:
//                     externState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::FOR:
//                     forState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::FUNC_CALL:
//                     funcCallState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::FUNC_DEC:
//                     funcDecState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::ID:
//                     idState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::IF:
//                     ifState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::OPERATOR:
//                     operatorState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::PARAM:
//                     paramState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::PARAM_LIST:
//                     paramListState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::RETURN:
//                     returnState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::RUN_VAR:
//                     runVarState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::SIZE:
//                     sizeState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::STRUCT_DEF:
//                     structDefState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::VAR_CALL:
//                     varCallState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::WHILE:
//                     whileState();
//                     break;
//                 case NOT::AbstractSyntaxTree::ASTNode::Types::STRUCT_CALL:
//                     structCallState();
//                     break;
//                 default:
//                     break;
//             }
//             return true;
//         }

//     NOU::sizeType  GLSLGenerator::varDecState()
//         {
//             if(currentNode->getChildCount() > 1)
//             {
//                 m_outputSourceString.append(currentNode->getChild(1)->getValue() + " ");
//             }else {
//                 m_outputSourceString.append(currentNode->getChild(0)->getValue() + ";");
//             }
//         }

//     NOU::sizeType  GLSLGenerator::bodyState()
//         {

//         }

//     NOU::sizeType  GLSLGenerator::retTypeState()
//         {}

//     NOU::sizeType  GLSLGenerator::varState()
//         {}

//     NOU::sizeType  GLSLGenerator::arrDefState()
//         {}

//     NOU::sizeType  GLSLGenerator::assignState()
//         {}

//     NOU::sizeType  GLSLGenerator::breakState()
//         {}

//     NOU::sizeType  GLSLGenerator::condState()
//         {}

//     NOU::sizeType  GLSLGenerator::constValueState()
//         {}

//     NOU::sizeType  GLSLGenerator::continueState()
//         {}

//     NOU::sizeType  GLSLGenerator::elseState()
//         {}

//     NOU::sizeType  GLSLGenerator::entryState()
//         {}

//     NOU::sizeType  GLSLGenerator::externState()
//         {}

//     NOU::sizeType  GLSLGenerator::forState()
//         {}

//     NOU::sizeType  GLSLGenerator::funcCallState()
//         {}

//     NOU::sizeType  GLSLGenerator::funcDecState()
//         {}

//     NOU::sizeType  GLSLGenerator::idState()
//         {}

//     NOU::sizeType  GLSLGenerator::ifState()
//         {}

//     NOU::sizeType  GLSLGenerator::operatorState()
//         {}

//     NOU::sizeType  GLSLGenerator::paramState()
//         {}

//     NOU::sizeType  GLSLGenerator::paramListState()
//         {}

//     NOU::sizeType  GLSLGenerator::returnState()
//         {}

//     NOU::sizeType  GLSLGenerator::runVarState()
//         {}

//     NOU::sizeType  GLSLGenerator::sizeState()
//         {}

//     NOU::sizeType  GLSLGenerator::structDefState()
//         {}

//     NOU::sizeType  GLSLGenerator::varCallState()
//         {}

//     NOU::sizeType  GLSLGenerator::whileState()
//         {}

//     NOU::sizeType  GLSLGenerator::structCallState()
//         {}

//         GLSLGenerator::GLSLGenerator(NOT::AbstractSyntaxTree &ast) :
//         m_outputSourceFile(nullptr),
//         m_outputSourceString("")
//         {
//             m_ast = NOU::NOU_CORE::move(ast);

//         }

//         NOU::boolean GLSLGenerator::start(const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &paramArgs)
//         {
//             if(paramArgs.size() == 0)
//             {
//                 m_root = m_ast.getRoot();
//                 m_outputSourceFile = NOU::NOU_FILE_MNGT::File(NOU::NOU_FILE_MNGT::Path::currentWorkingDirectory().getAbsolutePath());
//                 processTree(m_root);
//             }else if (paramArgs.size() == 1)
//             {
//                 m_root = m_ast.getRoot();
//                 m_outputSourceFile = NOU::NOU_FILE_MNGT::File(paramArgs.at(0));
//                 processTree(m_root);
//             }
//         }

//         NOU::boolean GLSLGenerator::processTree(NOT::AbstractSyntaxTree::ASTNode *nextNode)
//         {
//             NOU::boolean isFinished;

//             if(nextNode->isRoot())
//             {
//                 currentNode = nextNode;
//             }

//             for(NOU::sizeType i = 0; i < currentNode->getChildCount(); i++)
//             {
//                 if(currentNode->isLeaf())
//                 {
//                     processState(currentNode->getChild(i)->getType());
//                     currentNode = currentNode->getChild(i);
//                     processTree(currentNode);
//                     prevNode = currentNode;
//                     currentNode = nextNode;
//                 }
//             }

//             return true;
//         }

//         NOU::boolean GLSLGenerator::generateSource()
//         {
//             return true;
//         }

// }