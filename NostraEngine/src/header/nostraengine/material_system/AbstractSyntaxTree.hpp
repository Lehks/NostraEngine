#ifndef MATERIAL_SYSTEM_ABSTRACT_SYNTAX_TREE_HPP
#define MATERIAL_SYSTEM_ABSTRACT_SYNTAX_TREE_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOT
{
    class ASTNode{
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
        public:
            const Types& getType() const;
            void setType(Types type);

            const NOU::NOU_DAT_ALG::String8& getValue() const;
            void setValue(NOU::NOU_DAT_ALG::String8 value);
            NOU::boolean hasValue() const;

            const ASTNode* const getChild() const;
            const NOU::NOU_DAT_ALG::Vector<const ASTNode* const> getChilds() const;
            NOU::boolean hasChild();

            const ASTNode* const getParent() const;
            NOU::boolean hasParent() const;

            NOU::boolean isLeaf() const;
            NOU::boolean isRoot() const;

            NOU::boolean insertNode(NOU::sizeType pos, const ASTNode& n);
            void appendNode(ASTNode n);
            removeNode(NOU::sizeType pos, ASTNode* n = nullptr);



    };

}





#endif