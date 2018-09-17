#ifndef NOE_MATSYS_TEXTURE_HPP
#define NOE_MATSYS_TEXTURE_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/NostraEngine.hpp"
/**
\author	 Dennis Franz
\version 1.0.0
\since   1.0.0
*/

namespace NOE::NOE_MATSYS
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual NOU::boolean bind() = 0;
		virtual NOU::boolean unbind() = 0;

		virtual NOU::boolean GenerateMipmap(NOU::boolean mbool) = 0;
		virtual NOU::boolean FlipTexture(NOU::boolean mbool) = 0;

		virtual NOU::boolean loadTexture(const NOU::NOU_DAT_ALG::String8 &pathToTexture, NOU::sizeType width, NOU::sizeType heigth) = 0;

		virtual NOU::NOU_DAT_ALG::String8 getTexture() = 0;

		virtual NOU::sizeType getID() = 0;
	};

}
#endif
