#include "GLSLGenerator.hpp"

namespace GLSLGeneratorPlugin
{

        NOU::boolean GLSLGenerator::processState(const NOT::AbstractSyntaxTree::ASTNode::Types &STATE)
        {
            return true;
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