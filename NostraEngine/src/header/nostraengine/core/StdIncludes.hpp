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
\brief The name of the namespace that contains all window components.
*/
#ifndef NOE_WINDOW
#define NOE_WINDOW window
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