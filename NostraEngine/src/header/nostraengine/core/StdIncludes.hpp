#ifndef NOE_CORE_STD_INCLUDES_HPP
#define NOE_CORE_STD_INCLUDES_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/Config.hpp"

/**
\file core/StdIncludes.hpp

\author  Lukas Reichmann
\version 0.0.1
\since   0.0.1

\brief A file that is usually included by all other files of the Nostra Engine.
*/

/**
\brief The name of the main namespace of the Nostra Engine.
*/
#ifndef NOE
#define NOE nostra::engine
#endif

/**
\brief The name of the namespace that contains all core components.
*/
#ifndef NOE_CORE
#define NOE_CORE core
#endif

/**
\brief The name of the utility namespace of the Nostra Engine.
*/
#ifndef NOE_UTILITY
#define NOE_UTILITY utility
#endif

/*
\brief The name of the namespace that contains all window components.
*/
#ifndef NOE_WINDOW
#define NOE_WINDOW window
#endif

#ifndef NOE_PLUGIN_FUNC
#define NOE_PLUGIN_FUNC NOU_EXPORT_FUNC
#endif

/**
\brief The version 0.0.1 of NOE.
*/
#ifndef NOE_VERSION_0_0_1
#define NOE_VERSION_0_0_1 NOU_MAKE_VERSION(0, 0, 1)
#endif

/**
\brief The current version of NOE.
*/
#ifndef NOE_VERSION
#define NOE_VERSION NOU_MAKE_VERSION(NOE_INTERNAL_VERSION_MAJOR, \
													NOE_INTERNAL_VERSION_MINOR, NOE_INTERNAL_VERSION_PATCH)
#endif

/**
\brief A macro that either exports or imports a function from a library.

\details
A macro that either exports or imports a function from a library.

This macro will import, if NOE_DLL is defined and export if it is not. NOE_DLL definitions should always be
correctly handled by CMake and does not need user-interaction.
*/
#ifndef NOE_FUNC
#    ifdef NOE_DLL
#        define NOE_FUNC NOU_IMPORT_FUNC
#    else
#        define NOE_FUNC NOU_EXPORT_FUNC
#    endif
#endif

namespace NOE::internal
{
	/**
	\brief A function that has no functionality, but because of StdIncludes.cpp will always force a compiler
	       to generate a library file.
	*/
	NOE_FUNC void forceLibGen();
}

#endif