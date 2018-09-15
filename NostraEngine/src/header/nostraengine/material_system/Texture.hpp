#ifndef NOE_MATSYS_TEXTURE_HPP
#define NOE_MATSYS_TEXTURE_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/NostraEngine.hpp"
#include "nostraengine/core/StdIncludes.hpp"

/**
\author	 Dennis Franz
\version 1.0.0
\since   1.0.0
*/

namespace NOE::NOE_MATSYS
{
	class Texture
	{
		NOU::sizeType m_ID;

		NOU::NOU_DAT_ALG::String8 m_pathToTexture;
		NOU::NOU_DAT_ALG::String8 m_Texture;

	public:
		Texture(NOU::sizeType ID);
		Texture(NOU::sizeType ID, const NOU::NOU_DAT_ALG::String8 &pathToTexture);

		NOU::boolean loadTexture(const NOU::NOU_DAT_ALG::String8 &pathToTexture = m_pathToTexture);

		NOU::NOU_DAT_ALG::String8 getTexture();

		NOU::sizeType getID();
	};

}
#endif
