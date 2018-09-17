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

		NOU::boolean m_activateMipmaps;
		NOU::boolean m_textureIsFliped;

	public:
		Texture(NOU::sizeType ID);
		Texture(NOU::sizeType ID, const NOU::NOU_DAT_ALG::String8 &pathToTexture);

		NOU::boolean bind();
		NOU::boolean unbind();

		NOU::boolean GenerateMipmap(NOU::boolean mbool);
		NOU::boolean FlipTexture(NOU::boolean mbool);

		NOU::boolean loadTexture(const NOU::NOU_DAT_ALG::String8 &pathToTexture);

		NOU::NOU_DAT_ALG::String8 getTexture();

		NOU::sizeType getID();
	};

}
#endif
