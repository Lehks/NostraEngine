#ifndef MATERIAL_SYSTEM_ABSTRACT_SYNTAX_TREE_HPP
#define MATERIAL_SYSTEM_ABSTRACT_SYNTAX_TREE_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOT
{
    class NOE_FUNC AbstractSyntaxTree
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
            class NOE_FUNC ASTNode{
                friend AbstractSyntaxTree::AbstractSyntaxTree();
                friend AbstractSyntaxTree::AbstractSyntaxTree(AbstractSyntaxTree&& other);

            public:
                /**
                \brief Enum representing all Types of Tokens found analysing the structure of the source code.

                \detail The types get's stored in a tuple.


                 Meaning of the Types:

                -ENTRY:
                 Entry defines the start of the tree, typically it is root.

                -FUNC_DEC:
                 Func_dec defines a function declaration. It's second attribute is the function name.
                 usually it contains a BODY, RET_TYPE and a PARAM_LIST child node.

                -PARAM_LIST:
                 Param_list contains on or several other PARAM child nodes. It has no second attribute.

                -RET_TYPE:
                 Ret_type defines the return type of the function (FUNC_DEC). It's second attribute
                 is the actual return type (int, float, custom...).

                -TYPE:
                 Type defines the type of an attribute. It's second attribute is usually
                 the actual return type (int, float, custom...).

                -BODY:
                 Body defines the actual body of a function (FUNC_DEC). It's child node's are the body block of code.
                 It has no second attribute.

                -VAR_DEC:
                 Var_dec defines a variable declaration. It contains a TYPE child node and
                 maybe a KEYWORD (e.g const) node. It's second attribute is the variable name.

                -ASSIGN:
                 Assign defines a assign operation (=). It usually contains a VAR child node and a
                 "passable value" node (e.g CONST_VALUE or VAR_CALL). It has no second attribute.

                -VAR:
                 Var defines a variable name the is mostly used as a child node of ASSIGN. It's second attribute is
                 the var name.
                 NOTE that this node don't declare , defines or initialise a variable.

                -OPERATOR:
                 Operator defines an operator operation (e.g += , + or -). It usually contains a VAR_CALL or CONST_VALUE
                 child node. It's second attribute is the actual operator.

                -VAR_CALL:
                 Var_call defines a "variable call" similar to a function call or an rvalue. It's second attribute is
                 the actual name of the variable.
                 NOTE that this node don't declare , defines or initialise a variable.

                -RETURN:
                 Return defines the return type. IT can have different "passable value" child node's (e.g VAR_CALL or
                 CONST_VALUE). It has no second attribute.

                -CONST_VALUE:
                 Const_value defines a constant value. It' second type is the actual value (e.g '5' '463' "Hello").

                -FUNC_CALL:
                 Func_call defines a "function call" similar to the variable call or a standard function call (c++, java).

                -BREAK:
                 Break defines a break. It behaves like the break everyone knows. It has no second attribute.

                -CONTINUE:
                 Continue defines the typically continue. It behaves like the continue everyone knows.
                 It has no second attribute.

                -WHILE:
                 While defines the typically while loop. It has a COND child node, and no second attribute.

                -COND:
                 Cond defines the condition of a loop or an if statement. It has usually a operator as a child node.
                 IT has no second attributes.

                -If:
                 If defines the typically if statement. It has a COND child node, and no second attribute.

                -ELSE:
                 Else defines the typically else statement. It has no second attribute.

                -KEYWORD:
                 Keyword defines a keyword for e.g a VAR_DEC and act's as a child node of it. It's second attribute
                 is the actual keyword.

                -ARR_DEF:
                 Arr_def defines an array. It can have up to 3 child nodes two necessary (SIZE , TYPE) and the KEYWORD type
                 It's second attribute is the array name.

                -SIZE:
                 Size defines a size and it's usually used as a child node of the ARR_DEF type.

                -STRUCT_DEF:
                 Struct_def defines a struct. It's second name is the name of the struct. It usually contains a BODY node.

                -EXTERN:
                 Extern defines an extern variable (in GLSL uniform). It has no second attribute.

                -ID:
                 Id defines the ID of the EXTERN node and is usually a child node of EXTERN.

                -FOR:
                 For defines the typically for loop. It has a COND child node, and no second attribute.

                -RUN_VAR:
                 Run_var defines the run variable. It has no second attribute.
                */
                enum class Types
                {
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
                    ELSE,
                    KEYWORD,
                    ARR_DEF,
                    SIZE,
                    STRUCT_DEF,
                    EXTERN,
                    ID,
                    FOR,
                    RUN_VAR
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