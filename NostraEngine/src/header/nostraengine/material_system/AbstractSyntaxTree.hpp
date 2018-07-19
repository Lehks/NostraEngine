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
            AbstractSyntaxTree(const AbstractSyntaxTree& other);

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
                friend AbstractSyntaxTree::AbstractSyntaxTree(const AbstractSyntaxTree& other);

            public:
                /**
                \brief Enum representing all Types of Tokens found analysing the structure of the source code.

                \detail The types get's stored in a tuple.


                 Meaning of the Types:

                -ENTRY:
                 Entry defines the start of the tree, typically it is root.

                -FUNC_DEC:
                 Func_dec defines a function declaration. It's value attribute is the function name.
                 In the same order its childnodes are: BODY, RET_TYPE, PARAM_LIST.

                -PARAM_LIST:
                 Param_list contains one or several other PARAM child nodes.

                -RET_TYPE:
                 Ret_type defines the return type of the function (FUNC_DEC). It's value
                 is the actual return type (int, float, custom, ...).

                -TYPE:
                 Type defines the type of an attribute. It's value is
                 the actual type (int, float, custom, ...).

                -BODY:
                 Body defines the actual body of a function (FUNC_DEC). It's child node's are the body block of code.
                 Each Expression/Statement is in the correct order from left to right as the original order from top to bottom.

                -VAR_DEC:
                 Var_dec defines a variable declaration. It contains a TYPE child node in the first child position and
                 maybe some KEYWORD (e.g. const) nodes. Its value is the variable name.

                -ASSIGN:
                 Assign defines a assign operation (=). It contains a VAR child node in first position and a
                 "passable value" node (e.g CONST_VALUE or VAR_CALL) in the second child node.

                -VAR:
                 Var defines a variable name the is mostly used as a child node of ASSIGN. It's value is
                 the var name.
                 NOTE that this node doesn't declare , define or initialise a variable.

                -OPERATOR:
                 Operator defines an operator operation (e.g. + or -). It usually contains a VAR_CALL or CONST_VALUE
                 child node. It's value is the actual operator.

                -VAR_CALL:
                 Var_call defines a "variable call" similar to a function call or an lvalue in C++. Its value is
                 the actual name of the variable.
                 NOTE that this node doesn't declare , define or initialise a variable.

                -RETURN:
                 Return defines the return value. IT can have one "passable value" child node (e.g VAR_CALL or
                 CONST_VALUE).

                -CONST_VALUE:
                 Const_value defines a constant value in terms either a constant variable call or a literal. 
                 Its value is the actual value (e.g 12.0f, 1222).

                -FUNC_CALL:
                 Func_call defines a "function call" similar to the variable call or a standard function call (c++, java).
                 Its value is the name of the called function.
                 Its childnodes are either CONST_VALUE, VAR_CALL, or FUNC_CALL nodes 
                 in the same order as they appear in the corresponding FUNC_DEF PARAM_LIST node.

                -BREAK:
                 Represents the `break` keyword.

                -CONTINUE:
                 Represents the `continue` keyword.

                -WHILE:
                 While defines the typically while loop. In the following order its childnodes are:
                 BODY, COND

                -COND:
                 Cond defines the condition of a loop or an if statement. It has usually a operator as a child node.
                 This has to be evaluatable to either true or false.

                -If:
                 If defines the typically if statement. In the following order its childnodes are:
                 BODY, COND

                -ELSE:
                 Else defines the typical else statement.It contains a single Node BODY.

                -KEYWORD:
                 Keyword defines a keyword for e.g a VAR_DEC and acts as a child node of it. Its value
                 is the actual keyword.

                -ARR_DEF:
                 Arr_def defines an array. Its value is the name of the Array 
                 In the following order its childnodes are:
                 SIZE, TYPE, KEYWORD(optional)

                -SIZE:
                 Size defines a size and its usually used as a child node of the ARR_DEF type.

                -STRUCT_DEF:
                 Struct_def defines a struct. Its value is the name of the struct. It usually contains a BODY node.

                -EXTERN:
                 Extern defines an extern variable (in GLSL uniform). Its value is the call name of the variable
                 It contains a single child node ID.

                -ID:
                 Id defines the ID of the EXTERN node and is usually a child node of EXTERN.
                 Its value is the numeric id.

                -FOR:
                 For defines the typically for loop. In the following order its childnodes are:
                 BODY(Actual body of the loop),
                 RUN_VAR(optional),
                 COND(optional),
                 ASSIGN(optional)

                -RUN_VAR:
                 Run_var defines the run variable. In the following order its childnodes are:
                 VAR_DEC(optional, only valid when ASSIGN also exists), ASSIGN(optional),

                -ARRAY_CALL:
                 Array_call defines a call to an array. Its value is the name of the called array.
                 It has a single child node SIZE(the position where a member will be accessed).

                -STRUCT_CALL:
                 Struct_call defines a call to an allready defined struct variable or a member of a struct variable.
                 Its value is the name of the struct. 
                 If this node contains a childnode VAR_CALL its member variable will be called instead.
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
                    RUN_VAR,
                    ARRAY_CALL,
                    STRUCT_CALL
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
                
                \detail This constructor is set to private since it works closely 
                        together with the surrounding Abstract Syntax Tree class.
                */
                ASTNode(Types type, const NOU::NOU_DAT_ALG::String8& value = "");

                /**
                \brief Copy constructor of the ASTNode class.
                \param The other ASTNode from which will be copied.

                \detail This constructor is private since it has to be used very carefully, 
                        without proper external handling from/with an AST the created object 
                        will be in an unusable state.
                */
                ASTNode(const ASTNode& other);
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
                \brief Appends an allready existing Tree to the current node in the most right spot.
                \param other An existring thee that will be appended.
                */
                void appendNode(const AbstractSyntaxTree& other);

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