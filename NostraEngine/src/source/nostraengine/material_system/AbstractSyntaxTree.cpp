#include "nostraengine/material_system/AbstractSyntaxTree.hpp"

namespace NOT
{
        ASTNode::ASTNode(Types type, const NOU::NOU_DAT_ALG::String8& value) :
        m_type(type),
        m_value(value) { }



    	ASTNode::Types ASTNode::getType() const
        {
            return m_type;
        }

        void ASTNode::setType(Types type)
        {
            m_type = type;
        }


        const NOU::NOU_DAT_ALG::String8& ASTNode::getValue() const
        {
            return m_value;
        }

        void ASTNode::setValue(const NOU::NOU_DAT_ALG::String8& value)
        {
            m_value = value;
        }

        NOU::boolean ASTNode::hasValue() const
        {
            return m_value.size() != 0;
        }

        // needs to be implemented
        const ASTNode* const ASTNode::getChild(NOU::sizeType pos) const
        {
            return nullptr;
        }
        // needs to be implemented
        ASTNode* ASTNode::getChild(NOU::sizeType pos)
        {
            return nullptr;
        }
        // needs to be implemented
        NOU::sizeType ASTNode::getChildCount()
        {
            return 0;
        }
        // needs to be implemented
        const NOU::NOU_DAT_ALG::Vector<const ASTNode*>& ASTNode::getChilds() const
        {
            static NOU::NOU_DAT_ALG::Vector<const ASTNode*> r;
            return r;
        }
        // needs to be implemented
        NOU::NOU_DAT_ALG::Vector<const ASTNode*>& ASTNode::getChilds()
        {
            static NOU::NOU_DAT_ALG::Vector<const ASTNode*> r;
            return r;
        }
        // needs to be implemented
        NOU::boolean ASTNode::hasChild() const
        {
            return false;
        }

        // needs to be implemented
        const ASTNode* const ASTNode::getParent() const
        {
            return nullptr;
        }
        // needs to be implemented
        ASTNode* ASTNode::getParent()
        {
            return nullptr;
        }
        // needs to be implemented
        NOU::boolean ASTNode::hasParent() const
        {
            return nullptr;
        }

        NOU::boolean ASTNode::isLeaf() const
        {
            return hasChild();
        }

        NOU::boolean ASTNode::isRoot() const
        {
            return hasParent();
        }

        // needs to be implemented
        NOU::boolean ASTNode::insertNode(NOU::sizeType pos, const ASTNode& n)
        {
            return false;
        }

        // needs to be implemented
        void appendNode(const ASTNode& n)
        {

        }
        // needs to be implemented
        NOU::boolean removeNode(NOU::sizeType pos, ASTNode* n)
        {
            return false;
        }
        

}