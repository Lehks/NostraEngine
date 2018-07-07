#include "nostraengine/material_system/AbstractSyntaxTree.hpp"

namespace NOT
{
        ASTNode::ASTNode(Types type, const NOU::NOU_DAT_ALG::String8& value) :
        m_type(type),
        m_value(value),
        m_parent(nullptr)
        { }

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


        const ASTNode* const ASTNode::getChild(NOU::sizeType pos) const
        {
            if(pos > m_childs.size())
            {
                return nullptr;
            } else
            {
                return &m_childs[pos];
            }
        }
        
        ASTNode* ASTNode::getChild(NOU::sizeType pos)
        {
            if(pos > m_childs.size())
            {
                return nullptr;
            } else
            {
                return &m_childs[pos];
            }
        }
        
        NOU::sizeType ASTNode::getChildCount()
        {
            return m_childs.size();
        }
        

        NOU::boolean ASTNode::hasChild() const
        {
            return m_childs.size() != 0;
        }


        const ASTNode* const ASTNode::getParent() const
        {
            return m_parent;
        }
        
        ASTNode* ASTNode::getParent()
        {
            return m_parent;
        }
        
        NOU::boolean ASTNode::hasParent() const
        {
            return m_parent != nullptr;
        }

        NOU::boolean ASTNode::isLeaf() const
        {
            return hasChild();
        }

        NOU::boolean ASTNode::isRoot() const
        {
            return hasParent();
        }

        NOU::boolean ASTNode::insertNode(NOU::sizeType pos, Types type, const NOU::NOU_DAT_ALG::String8& value)
        {
            ASTNode tmp(type, value);
            tmp.m_parent = this;
            if(pos >= m_childs.size())
            {
                m_childs.emplaceBack(NOU::NOU_CORE::move(tmp));
                return false;
            } else
            {
                m_childs.insert(pos, NOU::NOU_CORE::move(tmp));
                return true;
            }
        }


        void ASTNode::appendNode(Types type, const NOU::NOU_DAT_ALG::String8& value)
        {
            ASTNode tmp(type, value);
            tmp.m_parent = this;

            m_childs.emplaceBack(NOU::NOU_CORE::move(tmp));
        }
        
        NOU::boolean ASTNode::removeNode(NOU::sizeType pos, ASTNode* n)
        {
            if(pos < m_childs.size())
            {
                if(n != nullptr)
                {
                    *n = m_childs[pos];
                }
                m_childs.remove(pos);
                return true;
            }
            return false;
        }
        

}