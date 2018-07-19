// #include "GLSLGenerator.hpp"

// namespace GLSLGeneratorPlugin
// {

        NOU::sizeType GLSLGenerator::processState(const NOT::AbstractSyntaxTree::ASTNode::Types &STATE)
        {
            NOU::sizeType retVal = 0;

            switch(STATE)
            {
                case NOT::AbstractSyntaxTree::ASTNode::Types::VAR_DEC:
                    retVal = varDecState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::BODY:
                    retVal = bodyState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::RET_TYPE:
                    retVal = retTypeState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::VAR:
                    retVal = varState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::ARR_DEF:
                    retVal = arrDefState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::ASSIGN:
                    retVal = assignState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::BREAK:
                    retVal = breakState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::COND:
                    retVal = condState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::CONST_VAL:
                    retVal = constValueState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::CONTINUE:
                    retVal = continueState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::ELSE:
                    retVal = elseState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::ENTRY:
                    retVal = entryState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::EXTERN:
                    retVal = externState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::FOR:
                    retVal = forState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::FUNC_CALL:
                    retVal = funcCallState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::FUNC_DEC:
                    retVal = funcDecState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::ID:
                    retVal = idState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::IF:
                    retVal = ifState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::OPERATOR:
                    retVal = operatorState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::PARAM:
                    retVal = paramState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::PARAM_LIST:
                    retVal = paramListState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::RETURN:
                    retVal = returnState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::RUN_VAR:
                    retVal = runVarState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::SIZE:
                    retVal = sizeState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::STRUCT_DEF:
                    retVal = structDefState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::VAR_CALL:
                    retVal = varCallState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::WHILE:
                    retVal = whileState();
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::STRUCT_CALL:
                    retVal = structCallState();
                    break;
                default:
                    break;
            }
            return retVal;
        }

    NOU::sizeType  GLSLGenerator::varDecState()
        {
            if(currentNode->getChildCount() > 1)
            {
                m_outputSourceString.append(currentNode->getChild(1)->getValue() + " ");
            }else {
                m_outputSourceString.append(currentNode->getChild(0)->getValue() + ";");
            }

            return 1;
        }

        NOU::sizeType  GLSLGenerator::bodyState()
        {}

        NOU::sizeType  GLSLGenerator::retTypeState()
        {}

        NOU::sizeType  GLSLGenerator::varState()
        {}

        NOU::sizeType  GLSLGenerator::arrDefState()
        {}

        NOU::sizeType  GLSLGenerator::assignState()
        {}

        NOU::sizeType  GLSLGenerator::breakState()
        {}

        NOU::sizeType  GLSLGenerator::condState()
        {}

        NOU::sizeType  GLSLGenerator::constValueState()
        {}

        NOU::sizeType  GLSLGenerator::continueState()
        {}

        NOU::sizeType  GLSLGenerator::elseState()
        {}

        NOU::sizeType  GLSLGenerator::entryState()
        {}

        NOU::sizeType  GLSLGenerator::externState()
        {}

        NOU::sizeType  GLSLGenerator::forState()
        {}

        NOU::sizeType  GLSLGenerator::funcCallState()
        {}

        NOU::sizeType  GLSLGenerator::funcDecState()
        {}

        NOU::sizeType  GLSLGenerator::idState()
        {}

        NOU::sizeType  GLSLGenerator::ifState()
        {}

        NOU::sizeType  GLSLGenerator::operatorState()
        {}

        NOU::sizeType  GLSLGenerator::paramState()
        {}

        NOU::sizeType  GLSLGenerator::paramListState()
        {}

        NOU::sizeType  GLSLGenerator::returnState()
        {}

        NOU::sizeType  GLSLGenerator::runVarState()
        {}

        NOU::sizeType  GLSLGenerator::sizeState()
        {}

        NOU::sizeType  GLSLGenerator::structDefState()
        {}

        NOU::sizeType  GLSLGenerator::varCallState()
        {}

        NOU::sizeType  GLSLGenerator::whileState()
        {}

        NOU::sizeType  GLSLGenerator::structCallState()
        {}

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

        NOU::boolean GLSLGenerator::processTree(NOT::AbstractSyntaxTree::ASTNode *nextNode)
        {
            NOU::sizeType stateIsFinished;

            if(nextNode->isRoot())
            {
                currentNode = nextNode;
                for(NOU::sizeType j = 0; j < currentNode->getChildCount(); j++)
                {
                    processTree(currentNode->getChild(j));
                }
            } else{

                currentNode = nextNode;
                for(NOU::sizeType i = 0; i < currentNode->getChildCount(); i++)
                {
                    stateIsFinished = processState(currentNode->getType());
                    if (stateIsFinished == 1)
                    {
                        break;
                    } else
                    {
                        processTree(currentNode->getChild(i));
                    }
                }
            }

//             return true;
//         }

//         NOU::boolean GLSLGenerator::generateSource()
//         {
//             return true;
//         }

// }