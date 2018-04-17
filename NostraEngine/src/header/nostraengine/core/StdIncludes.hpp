#ifndef NOE_CORE_STD_INCLUDES_HPP
#define NOE_CORE_STD_INCLUDES_HPP

#include "nostrautils/core/StdIncludes.hpp"

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
\brief The name of the namespace that contains all components that are related for operating a window.
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