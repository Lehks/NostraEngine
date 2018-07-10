#ifndef MATERIAL_SYSTEM_ABSTRACT_SYNTAX_TREE_HPP
#define MATERIAL_SYSTEM_ABSTRACT_SYNTAX_TREE_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOT
{
    class NOU_CLASS AbstractSyntaxTree
    {


        public:
            /**
            \brief Default constructor of the Abstract Syntax Tree. 
            */
            AbstractSyntaxTree();

            /**
            \brief Copy constructor of the Abstract Syntax Tree. Deleted function.
            */
            AbstractSyntaxTree(const AbstractSyntaxTree& other) = delete;

            /**
            \brief Move constructor of the Abstract Syntax Tree.
            */
            AbstractSyntaxTree(AbstractSyntaxTree&& other);

            /**
            \brief A class that represents a Node inside the Abstract Syntax Tree.
            */
            class NOU_CLASS ASTNode{
                friend AbstractSyntaxTree::AbstractSyntaxTree();
                friend AbstractSyntaxTree::AbstractSyntaxTree(AbstractSyntaxTree&& other);

            public:
                /**
                \brief Enum representing all Types of Tokens found analysing the structure of the source code.
                */
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

                /**
                \brief A pointer that points the the Abstract Syntax Tree instance containing this node.
                */
                AbstractSyntaxTree* m_assignedTree;

                /**
                \brief Describes the position inside the child pool of the Abstract Syntax Tree containing this node.
                */
                NOU::sizeType m_ownIndex;

                /**
                \brief Describes the position of the parent node inside the child pool of the Abstract Syntax Tree containing this node.
                */
                NOU::sizeType m_parent;

                /**
                \brief Stores the type of the current node.
                */
                Types m_type;

                /**
                \brief Stores a string containing the value of the current node.
                */
                NOU::NOU_DAT_ALG::String8 m_value;

                /**
                \brief A vector containing indices that point to the actual allocated child in the child pool.
                */
                NOU::NOU_DAT_ALG::Vector<NOU::sizeType> m_children;

                /**
                \brief Constructor of the ASTNode class.
                \param type The type of token that this Node will represent.
                \param value The value assigned to this Node.
                
                \detail This constructor is set to private since it works closely together with the surrounding Abstract Syntax Tree class.
                */
                ASTNode(Types type, const NOU::NOU_DAT_ALG::String8& value = "");
            public:
                /**
                \brief Getter for the m_type attribute.
                \return The assigned type.
                */
                Types getType() const;

                /**
                \brief Setter for the m_type attribute.
                \param type The new type of this instance.
                */
                void setType(Types type);

                /**
                \brief Getter for the m_value attribute.
                \return The assigned value.
                */
                const NOU::NOU_DAT_ALG::String8& getValue() const;

                /**
                \brief Setter for the m_value attribute.
                \param value The new value assigned to this node.
                */
                void setValue(const NOU::NOU_DAT_ALG::String8& value);

                /**
                \brief Checks if this node has any children assigned.
                \return true if children are assigned, false if not.
                */
                NOU::boolean hasValue() const;

                /**
                \brief Returns a pointer to the requested Child.
                \return Pointer to the children node, given the current node has a child in this position. 
                        Returns nullptr if the requested position contains no child.
                */
                const ASTNode* const getChild(NOU::sizeType pos) const;

                /**
                \brief Returns a pointer to the requested Child.
                \return Pointer to the children node, given the current node has a child in this position. 
                        Returns nullptr if the requested position contains no child.
                */
                ASTNode* getChild(NOU::sizeType pos);

                /**
                \brief Returns the count of children this node contains.
                \return Children count of this node.
                */
                NOU::sizeType getChildCount() const;

                /**
                \brief Checks if this node has any children.
                \return True if this node contauns children. False if not.
                */
                NOU::boolean hasChild() const;

                /**
                \brief Returns a pointer to the parent node of this node.
                \return Pointer to the parent node or nullptr if this node has no parent.
                */
                const ASTNode* const getParent() const;

                /**
                \brief Returns a pointer to the parent node of this node.
                \return Pointer to the parent node or nullptr if this node has no parent.
                */
                ASTNode* getParent();

                /**
                \brief Checks if this node has a parent node.
                \return True if this node has a parent, false if not.
                */
                NOU::boolean hasParent() const;

                /**
                \brief Checks if this node is a leaf node.
                \return True if this node is a leaf node, false if not.
                */
                NOU::boolean isLeaf() const;

                /**
                \brief Checks if this node is a Root node.
                \return True if this node is a root nodem false if not.
                */
                NOU::boolean isRoot() const;

                /**
                \brief Appends a child node to the current node in the most right spot.
                \param type The type of the newly created node.
                \param value The value of the newly created node. Defaults to an empty string.
                */
                void appendNode(Types type, const NOU::NOU_DAT_ALG::String8& value = "");

                /**
                \brief Checks if the type and value are equal.
                \return True if both type and value are equal, false if not.
                */
                NOU::boolean operator==(const ASTNode& other) const;
        };
        friend ASTNode;

        private:
            /**
            \brief A pool containing all children used in the tree.
            */
            NOU::NOU_DAT_ALG::Vector<NOU::NOU_MEM_MNGT::UniquePtr<ASTNode>>m_childPool;
        public:
            /**
            \brief Getter for the root node of this tree.
            \return A pointer to the root node.
            */
            ASTNode* getRoot();

            /**
            \brief Getter for the root node of this tree.
            \return A pointer to the root node.
            */
            const ASTNode* const getRoot() const;
    };

    
}





#endif