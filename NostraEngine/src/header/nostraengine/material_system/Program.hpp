#ifndef NOE_MATSYS_PROGRAM_HPP
#define NOE_MATSYS_PROGRAM_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"


/**
\author	 Dennis Franz
\version 1.0.0
\since   1.0.0
*/

namespace NOE::NOE_MATSYS
{
	class Program
	{
	protected:
		virtual NOU::boolean linkShader() = 0;
		virtual NOU::boolean createVertexShader() = 0;
		virtual NOU::boolean createFragmetShader() = 0;
		virtual NOU::boolean createGeometryShader() = 0;
	public:
		enum class Variables
		{
			INT,
			FLOAT,
			BOOLEAN,
			VEC1,
			VEC2,
			VEC3,
			VEC4,
			MAT1,
			MAT2,
			MAT3,
			MAT4
		};

	public:
		virtual ~Program() = default;
		virtual NOU::boolean createShader() = 0;
		virtual NOU::boolean bind() = 0;
		virtual NOU::boolean unbind() = 0;
	};
}
#endif