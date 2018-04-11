#ifndef NOE_WINDOW_DEVICE_HPP
#define NOE_WINDOW_DEVICE_HPP

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"

/**
\file window/Device.hpp

\author  Lukas Gross
\version 0.0.1
\since   0.0.1

\brief A file that provides the functionality for accessing monitor meta data.
*/
namespace NOE_WINDOW
{
	class Device
	{
	private:
		using sizeType = NOU::sizeType;
		sizeType width;
		sizeType height;

	public:

		Device();
		Device& getResolution();
	};
}

#endif