#ifndef MATERIAL_SYSTEM_ABSTRACT_SYNTAX_TREE_HPP
#define MATERIAL_SYSTEM_ABSTRACT_SYNTAX_TREE_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOT
{
    class NOU_CLASS ASTNode{
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
            Types m_type;
            NOU::NOU_DAT_ALG::String8 m_value;
            NOU::NOU_DAT_ALG::Vector<ASTNode> m_childs;
            ASTNode* m_parent:
        public:
            ASTNode(Types type,const NOU::NOU_DAT_ALG::String8& value);

            Types getType() const;
            void setType(Types type);

            const NOU::NOU_DAT_ALG::String8& getValue() const;
            void setValue(const NOU::NOU_DAT_ALG::String8& value);
            NOU::boolean hasValue() const;

            const ASTNode* const getChild(NOU::sizeType pos) const;
            ASTNode* getChild(NOU::sizeType pos);
            NOU::sizeType getChildCount();
            const NOU::NOU_DAT_ALG::Vector<const ASTNode*>& getChilds() const;
            NOU::NOU_DAT_ALG::Vector<const ASTNode*>& getChilds();
            NOU::boolean hasChild() const;

            const ASTNode* const getParent() const;
            ASTNode* getParent();
            NOU::boolean hasParent() const;

            NOU::boolean isLeaf() const;
            NOU::boolean isRoot() const;

            NOU::boolean insertNode(NOU::sizeType pos, const ASTNode& n);
            void appendNode(const ASTNode& n);
            NOU::boolean removeNode(NOU::sizeType pos, ASTNode* n = nullptr);



    };

    // for easier usage
    using AbstractSyntaxTree = ASTNode;

}





#endif