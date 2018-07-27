#include "nostraengine/material_system/AbstractSyntaxTree.hpp"
#include "nostrautils/NostraUtils.hpp"
#define NOT_AST AbstractSyntaxTree
#define NOT_ENTRY NOT_AST::ASTNode::Types::ENTRY
namespace NOT
{
    NOT_AST::AbstractSyntaxTree()
    {
        NOU::NOU_MEM_MNGT::UniquePtr<ASTNode> tmp(new ASTNode(NOT_ENTRY), NOU::NOU_MEM_MNGT::defaultDeleter);
        m_childPool.emplaceBack(NOU::NOU_CORE::move(tmp));
        m_childPool[0]->m_parent = 0;
        m_childPool[0]->m_ownIndex = 0;
        m_childPool[0]->m_assignedTree = this;
    }

    NOT_AST::AbstractSyntaxTree(AbstractSyntaxTree&& other) :
        m_childPool(NOU::NOU_CORE::move(other.m_childPool))
    {
        NOU::sizeType s = m_childPool.size();
        for(NOU::sizeType i = 0; i < s; i++)
        {
            m_childPool[i]->m_assignedTree = this;
        }
    }

    NOT_AST::AbstractSyntaxTree(const AbstractSyntaxTree& other)
    {
        for(NOU::sizeType i = 0; i < other.m_childPool.size(); i++)
        {
            m_childPool.emplaceBack(NOU::NOU_MEM_MNGT::UniquePtr<ASTNode>(
                new ASTNode(*other.m_childPool[i]), 
                NOU::NOU_MEM_MNGT::defaultDeleter));
            m_childPool[i]->m_assignedTree = this;
        }
    }

    NOT_AST::ASTNode* NOT_AST::getRoot()
    {
        return m_childPool[0].rawPtr();
    }
    const AbstractSyntaxTree::ASTNode* const NOT_AST::getRoot() const
    {
        return m_childPool[0].rawPtr();
    }
    
    NOT_AST::ASTNode::ASTNode(NOT_AST::ASTNode::Types type, const NOU::NOU_DAT_ALG::String8& value) :
    m_type(type),
    m_value(value) { }

    NOT_AST::ASTNode::ASTNode(const NOT_AST::ASTNode& other) : 
    m_assignedTree(nullptr),
    m_ownIndex(other.m_ownIndex),
    m_parent(other.m_parent),
    m_type(other.m_type),
    m_value(other.m_value),
    m_children(other.m_children) { }

    NOT_AST::ASTNode::Types NOT_AST::AbstractSyntaxTree::ASTNode::getType() const
    {
        return m_type;
    }

    void NOT_AST::ASTNode::setType(NOT_AST::ASTNode::Types type)
    {
        m_type = type;
    }

    const NOU::NOU_DAT_ALG::String8& NOT_AST::ASTNode::getValue() const
    {
        return m_value;
    }

    NOU::boolean NOT_AST::ASTNode::hasValue() const
    {
        return m_value.size() != 0;
    }


    const NOT_AST::ASTNode* const NOT_AST::ASTNode::getChild(NOU::sizeType pos) const
    {
        if(pos >= m_children.size())
        {
            return nullptr;
        }
        return m_assignedTree->m_childPool[m_children[pos]].rawPtr();
    }

    NOT_AST::ASTNode* NOT_AST::ASTNode::getChild(NOU::sizeType pos)
    {
        if(pos >= m_children.size())
        {
            return nullptr;
        }
        return m_assignedTree->m_childPool[m_children[pos]].rawPtr();
    }

    NOU::sizeType NOT_AST::ASTNode::getChildCount() const
    {
        return m_children.size();
    }

    NOU::boolean NOT_AST::ASTNode::hasChild() const
    {
        return m_children.size() != 0;
    }

    const NOT_AST::ASTNode* const NOT_AST::ASTNode::getParent() const
    {
        return m_assignedTree->m_childPool[m_parent].rawPtr();
    }

    NOT_AST::ASTNode* NOT_AST::ASTNode::getParent()
    {
        if(!hasParent())
        {
            return nullptr;
        }
        ASTNode* ret;
        auto& tmpVec = m_assignedTree->m_childPool;
        auto& tmpPtr = tmpVec[m_parent];
        ret = tmpPtr.rawPtr();
        return ret;
    }

    NOU::boolean NOT_AST::ASTNode::hasParent() const
    {
        return m_ownIndex != m_parent;
    }

    NOU::boolean NOT_AST::ASTNode::isLeaf() const
    {
        return !hasChild();
    }

    NOU::boolean NOT_AST::ASTNode::isRoot() const
    {
        return !hasParent();
    }

    NOT_AST::ASTNode* NOT_AST::ASTNode::appendNode(Types type, const NOU::NOU_DAT_ALG::String8& value)
    {
        NOU::NOU_MEM_MNGT::UniquePtr<ASTNode> tmp(new ASTNode(type, value), NOU::NOU_MEM_MNGT::defaultDeleter);
        NOU::sizeType pos;

        m_assignedTree->m_childPool.emplaceBack(NOU::NOU_CORE::move(tmp));
        pos = m_assignedTree->m_childPool.size()-1;

        m_assignedTree->m_childPool[pos]->m_ownIndex = pos;
        m_assignedTree->m_childPool[pos]->m_parent = m_ownIndex;
        m_assignedTree->m_childPool[pos]->m_assignedTree = m_assignedTree;
        m_children.emplaceBack(pos);
        return m_assignedTree->m_childPool[pos].rawPtr();
    }

    NOU::boolean NOT_AST::ASTNode::operator==(const NOT_AST::ASTNode& other) const
    {
        NOU::boolean b;

        b = m_type == other.m_type;
        b &= m_value == other.m_value;

        return b;
    }

    void NOT_AST::ASTNode::appendNode(const NOT_AST& other)
    {
        NOU::sizeType newIdx, size, childCount;
        ASTNode* tmp;
        

        newIdx = m_assignedTree->m_childPool.size();    // Getting start idx of the newly appended Nodes.
        size = other.m_childPool.size();
        auto& childPool = m_assignedTree->m_childPool;

        for(NOU::sizeType i = 0; i < size; i++)
        {
            NOU::NOU_MEM_MNGT::UniquePtr<ASTNode> tmpPtr(new ASTNode(*other.m_childPool[i].rawPtr()),  NOU::NOU_MEM_MNGT::defaultDeleter);  // Copying each element from other.
            childPool.emplaceBack(NOU::NOU_CORE::move(tmpPtr)); 

            tmp = childPool[i + newIdx].rawPtr();       // newly added node.

            tmp->m_assignedTree = this->m_assignedTree;    // Setting the assigned tree accordingly.
            tmp->m_parent += newIdx;  // Setting parents accordingly.
            tmp->m_ownIndex += newIdx;    // Setting the own idx in the childpool.
            
            childCount = tmp->getChildCount();
            for(NOU::sizeType j = 0; j < childCount; j++)
            {
                tmp->m_children[j] += newIdx;   // Setting the children indices to match them.
            }
        }

        size = other.getRoot()->getChildCount();
        tmp = m_assignedTree->getRoot();
        for(NOU::sizeType i = 0; i < size; i++)
        {
            tmp->m_children.emplaceBack(other.getRoot()->m_children[i] + newIdx); // Adding new root nodes to current root
        }
    }

    NOT_AST::ASTNode* NOT_AST::ASTNode::appendNode(const NOT_AST::ASTNode& other)
    {
        if(other.m_type == NOT_ENTRY)   //Cant have multiple entry points
        {
            return nullptr;
        }
        return nullptr;

    }

    const NOU::NOU_DAT_ALG::Vector<NOT_AST::ASTNode*> NOT_AST::ASTNode::getAllChildren() const
    {
        NOU::NOU_DAT_ALG::Vector<NOT_AST::ASTNode*> ret;
        NOU::NOU_DAT_ALG::FastQueue<NOU::sizeType> q;
        ASTNode *tmp;
        NOU::sizeType size;

        q.push(m_ownIndex);

        while(!q.empty())
        {
            tmp = m_assignedTree->m_childPool[q.pop()].rawPtr();
            size = tmp->getChildCount();
            for(NOU::sizeType i = 0; i < size; i++)
            {
                ret.emplaceBack(tmp->getChild(i));
                q.push(tmp->getChild(i)->m_ownIndex);
            }
        }

        return ret;
    }




}

#undef NOT_AST