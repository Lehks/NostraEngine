#include "nostraengine/material_system/AbstractSyntaxTree.hpp"

namespace NOT
{
        ASTNode::ASTNode(Types type, const NOU::NOU_DAT_ALG::String8& value) :
        m_type(type),
        m_value(value),
        m_parent(nullptr)
        { }

        ASTNode::ASTNode(ASTNode&& other):
        m_type(NOU::NOU_CORE::move(other.m_type)),
        m_value(NOU::NOU_CORE::move(other.m_value)),
        m_parent(other.m_parent),
        m_childs(NOU::NOU_CORE::move(other.m_childs))
        {
            other.m_parent = nullptr;
        }




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
                    *n = NOU::NOU_CORE::move(m_childs[pos]);
                }
                m_childs.remove(pos);
                return true;
            }
            return false;
        }

        NOU::boolean ASTNode::operator==(const ASTNode& other) const
        {
            NOU::boolean r;
            r = m_type == other.m_type;
            r &= m_value == other.m_value;
            return r;
        }

        void ASTNode::operator=(const ASTNode& other)
        {
            m_type = other.m_type;
            m_value = other.m_value;
            m_childs = other.m_childs;
        }

        const ASTNode* const ASTNode::operator[](NOU::sizeType i) const
        {
            return getChild(i);
        }

        ASTNode* ASTNode::operator[](NOU::sizeType i)
        {
            return getChild(i);
        }

        void ASTNode::operator+=(const ASTNode& other)
        {
            appendNode(other.getType(), other.getValue());
            getChild(getChildCount() - 1)->m_childs = other.m_childs;

        }
        
        

}