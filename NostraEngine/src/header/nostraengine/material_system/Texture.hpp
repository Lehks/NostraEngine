#ifndef NOE_MATSYS_TEXTURE_HPP
#define NOE_MATSYS_TEXTURE_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"

namespace NOE::NOE_MATSYS
{
	class Texture
	{
	private:

	public:
		virtual ~Texture() = default;

		virtual bind() = 0;

		virtual loadTexture() = 0;
	};

}
#endif