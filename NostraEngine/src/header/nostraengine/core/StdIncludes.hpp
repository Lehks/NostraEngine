#ifndef NOE_CORE_STD_INCLUDES_HPP
#define NOE_CORE_STD_INCLUDES_HPP

#include "nostrautils/NostraUtils.hpp"

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

/*
\brief The name of the namespace that contains all rendering components.
*/
#ifndef NOE_RENDERER
#define NOE_RENDERER renderer
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
#define NOE_VERSION NOE_VERSION_0_0_1
#endif

namespace NOE::internal
{
	/**
	\brief A function that has no functionality, but because of StdIncludes.cpp will always force a compiler
	       to generate a library file.
	*/
	NOU_FUNC void forceLibGen();
}

#endif