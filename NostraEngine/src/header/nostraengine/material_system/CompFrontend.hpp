#ifndef MATERIAL_SYSTEM_COMP_FRONTEND_HPP
#define MATERIAL_SYSTEM_COMP_FRONTEND_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/material_system/AbstractSyntaxTree.hpp"

/**
\author Leslie Marxen
\brief Compilerfrontend implemented as Singleton.
\detail This class is used to analyse a given source shaderfile for 
    its syntactical correctnes. Later also semantical analysis and 
    generation of an Abstract Syntax Tree representing the input 
    sourcecode.
    In the following context AST = Abstract Syntax Tree
*/

namespace NOT
{
    class NOE_FUNC CompFrontend final
    {
        using String = NOU::NOU_DAT_ALG::String<NOU::char8>;

        template<typename T>
        using Vector = NOU::NOU_DAT_ALG::Vector<T>;

        using Path = NOU::NOU_FILE_MNGT::Path;

        /**
        \brief The instance of the Singleton.
        */
        static CompFrontend* m_instance;

        /**
        \brief The path to the input shader sourcefile.
        */
        Path m_source;

        /**
        \brief A Vector containing possible compile options
        */
        Vector<String> m_options;

        /**
        \brief A Vector containing compile-errors that occured while compiling
        */
        Vector<String> m_errors;

        /**
        \brief A bool representing if the compile-errors have allready been loaded into m_errors
        */
        NOU::boolean m_errorsFetched;

        /**
        \brief Sucessfully compiled Abstract Syntax Tree.
        \detail The AST will only contain nodes if the compilation was successfull.
        */
        AbstractSyntaxTree m_ast;

        /**
        \brief Private default constructor of the CompFrontend class
        */
        CompFrontend();

        /**
        \brief Deleted cpy ctor.
        */
        CompFrontend(const CompFrontend& other) = delete;

        /**
        \brief Deleted mv ctor.
        */
        CompFrontend(CompFrontend&& other) = delete;


        /**
        \brief Reads the compileerrors from Bison.
        */
        void fetchErrors();
    public:

        /**
        \brief Creates and returns an instance of the compilerfrontend.
        \return A reference to the active instance.
        */
        static CompFrontend& getInstance();

        /**
        \brief Destructor of the compilerfrontend
        */
        ~CompFrontend();

        /**
        \brief Starts the AST generation.
        \detail Starts Bison and the whole analyse process.
        \return true if no compile-errors occured. False otherwise.
        */
        NOU::boolean start(); 

        /**
        \brief Returns a vector of all occured compile-errors
        \return A vector containing all compile errors.
        */
        const Vector<String>& getErrors();

        /**
        \brief Getter/Setter for m_source.
        \return A reference to m_source.
        */
        Path& getSource();

        /**
        \brief Getter/Setter for m_options.
        \return A reference to m_options.
        */
        Vector<String>& getOptions();

        /**
        \brief Returns the generated AST from the given source code.
        \detail If the compilation process resultes in any count of errors. 
            This will just return a default constructed AST with no nodes.
        \return an AST representing the given source.
        */
        const AbstractSyntaxTree& getAbstractSyntaxTree();

    };
}
#endif