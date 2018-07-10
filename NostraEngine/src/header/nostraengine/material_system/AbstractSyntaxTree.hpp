#ifndef MATERIAL_SYSTEM_ABSTRACT_SYNTAX_TREE_HPP
#define MATERIAL_SYSTEM_ABSTRACT_SYNTAX_TREE_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOT
{
    class NOU_CLASS AbstractSyntaxTree
    {


        public:
            AbstractSyntaxTree();
            AbstractSyntaxTree(const AbstractSyntaxTree& other) = delete;
            AbstractSyntaxTree(AbstractSyntaxTree&& other) = delete;


            class NOU_CLASS ASTNode{
                friend AbstractSyntaxTree::AbstractSyntaxTree();
                friend AbstractSyntaxTree::AbstractSyntaxTree(AbstractSyntaxTree&& other);

            public:

                enum class Types{
                    ENTRY,
                    FUNC_DEC,
                    PARAM_LIST,
                    PARAM,
                    RET_TYPE,
                    TYPE,
                    BODY,
                    VAR_DEC,
                    ASSIGN,
                    VAR,
                    OPERATOR,
                    VAR_CALL,
                    RETURN,
                    CONST_VAL,
                    FUNC_CALL,
                    BREAK,
                    CONTINUE,
                    WHILE,
                    COND,
                    IF,
                    ELSE    
                };

            private:

                AbstractSyntaxTree* m_assignedTree;
                NOU::sizeType m_ownIndex;
                NOU::sizeType m_parent;
                Types m_type;
                NOU::NOU_DAT_ALG::String8 m_value;
                NOU::NOU_DAT_ALG::Vector<NOU::sizeType> m_children;

                ASTNode(Types type, const NOU::NOU_DAT_ALG::String8& value = "");
            public:
                Types getType() const;
                void setType(Types type);

                const NOU::NOU_DAT_ALG::String8& getValue() const;
                void setValue(const NOU::NOU_DAT_ALG::String8& value);
                NOU::boolean hasValue() const;

                const ASTNode* const getChild(NOU::sizeType pos) const;
                ASTNode* getChild(NOU::sizeType pos);
                NOU::sizeType getChildCount() const;
                NOU::boolean hasChild() const;

                const ASTNode* const getParent() const;
                ASTNode* getParent();
                NOU::boolean hasParent() const;

                NOU::boolean isLeaf() const;
                NOU::boolean isRoot() const;

                void appendNode(Types type, const NOU::NOU_DAT_ALG::String8& value = "");

                NOU::boolean operator==(const ASTNode& other) const;
        };
        friend ASTNode;

        private:
            NOU::NOU_DAT_ALG::Vector<NOU::NOU_MEM_MNGT::UniquePtr<ASTNode>>m_childPool;
        public:

            ASTNode* getRoot();
            const ASTNode* const getRoot() const;
    };

    
}





#endif