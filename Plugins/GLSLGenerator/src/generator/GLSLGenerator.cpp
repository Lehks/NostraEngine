#include "GLSLGenerator.hpp"

namespace GLSLGeneratorPlugin
{

        NOU::boolean GLSLGenerator::processState(const NOT::AbstractSyntaxTree::ASTNode::Types &STATE)
        {
            switch(STATE)
            {
                case NOT::AbstractSyntaxTree::ASTNode::Types::VAR_DEC:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::BODY:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::RET_TYPE:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::VAR:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::ARR_DEF:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::ASSIGN:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::BREAK:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::COND:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::CONST_VAL:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::CONTINUE:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::ELSE:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::ENTRY:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::EXTERN:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::FOR:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::FUNC_CALL:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::FUNC_DEC:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::ID:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::IF:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::KEYWORD:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::OPERATOR:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::PARAM:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::PARAM_LIST:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::RETURN:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::RUN_VAR:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::SIZE:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::STRUCT_DEF:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::TYPE:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::VAR_CALL:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::WHILE:
                    break;
                case NOT::AbstractSyntaxTree::ASTNode::Types::STRUCT_CALL:
                    break;
                default:
                    break;
            }
            return true;
        }

        void GLSLGenerator::varDecState()
        {}

        void GLSLGenerator::bodyTypeState()
        {}

        void GLSLGenerator::retTypeState()
        {}

        void GLSLGenerator::varState()
        {}

        void GLSLGenerator::arrDefState()
        {}

        void GLSLGenerator::assignState()
        {}

        void GLSLGenerator::breakState()
        {}

        void GLSLGenerator::condState()
        {}

        void GLSLGenerator::constValueState()
        {}

        void GLSLGenerator::continueState()
        {}

        void GLSLGenerator::elseState()
        {}

        void GLSLGenerator::entryState()
        {}

        void GLSLGenerator::externState()
        {}

        void GLSLGenerator::forState()
        {}

        void GLSLGenerator::funcCallState()
        {}

        void GLSLGenerator::funcDecState()
        {}

        void GLSLGenerator::idState()
        {}

        void GLSLGenerator::ifState()
        {}

        void GLSLGenerator::keywordState()
        {}

        void GLSLGenerator::operatorState()
        {}

        void GLSLGenerator::paramState()
        {}

        void GLSLGenerator::paramListState()
        {}

        void GLSLGenerator::returnState()
        {}

        void GLSLGenerator::runVarState()
        {}

        void GLSLGenerator::sizeState()
        {}

        void GLSLGenerator::structDefState()
        {}

        void GLSLGenerator::typeState()
        {}

        void GLSLGenerator::varCallState()
        {}

        void GLSLGenerator::whileState()
        {}

        void GLSLGenerator::structCallState()
        {}

        NOU::boolean GLSLGenerator::start(const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &paramArgs)
        {
            if(paramArgs.size() == 0)
            {
                m_root = NOT::AbstractSyntaxTree::getRoot();
                processTree(m_root);
            }
        }

        NOU::boolean GLSLGenerator::processTree(NOT::AbstractSyntaxTree::ASTNode *m_ast)
        {
            NOT::AbstractSyntaxTree::ASTNode *currentNode = m_ast;

            for(NOU::sizeType i = 0; i < currentNode->getChildCount(); i++)
            {
                processState(currentNode->getChild(i)->getType());
                currentNode = currentNode->getChild(i);
                processTree(currentNode);
            }

            return true;
        }

        NOU::boolean GLSLGenerator::generateSource()
        {
            return true;
        }

}