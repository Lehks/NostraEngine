#ifndef NOE_WINDOW_DEVICE_HPP
#define NOE_WINDOW_DEVICE_HPP

#include "GLFW/glfw3.h"

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"
/**
\file window/Device.hpp

\author  Lukas Gross
\version 0.0.1
\since   0.0.1

\brief A file that provides the functionality for accessing monitor meta data.
*/
namespace NOE::NOE_WINDOW
{
	class NOU_CLASS Device 
	{
	private:
		NOU::sizeType width;
		NOU::sizeType height;

	public:

		Device();
		Device& getPrimaryDevice();
		Device& getResolution();
	};
}

#endif