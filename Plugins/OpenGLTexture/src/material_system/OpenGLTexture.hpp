#ifndef PLUGIN_OPENGL_TEXTURE_HPP
#define PLUGIN_OPENGL_TEXTURE_HPP

#include "nostraengine/NostraEngine.hpp"
#include "nostrautils/NostraUtils.hpp"

#include "../../../GLAD/include/glad/glad.h"

/**
\author	 Dennis Franz
\version 1.0.0
\since   1.0.0
*/

namespace OpenGLTexturePlugin
{
	class OpenGLTexture : public NOE::NOE_MATSYS::Texture
	{
	private:
		NOU::sizeType m_ID;
		NOU::uint32 m_textureId;

		NOU::NOU_DAT_ALG::String8 m_pathToTexture;
		NOU::NOU_DAT_ALG::String8 m_Texture;

		NOU::boolean m_activateMipmaps;
		NOU::boolean m_textureIsFliped;

	public:
		NOE_PLUGIN_FUNC OpenGLTexture(NOU::sizeType ID);
		NOE_PLUGIN_FUNC OpenGLTexture(NOU::sizeType ID, const NOU::NOU_DAT_ALG::String8 &pathToTexture);

		NOE_PLUGIN_FUNC virtual ~OpenGLTexture() = default;

		NOE_PLUGIN_FUNC virtual NOU::boolean bind() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean unbind() override;

		NOE_PLUGIN_FUNC virtual NOU::boolean GenerateMipmap(NOU::boolean mbool) override;
		NOE_PLUGIN_FUNC virtual NOU::boolean FlipTexture(NOU::boolean mbool) override;

		NOE_PLUGIN_FUNC virtual NOU::boolean loadTexture(const NOU::NOU_DAT_ALG::String8 &pathToTexture, NOU::sizeType width, NOU::sizeType heigth) override;

		NOE_PLUGIN_FUNC virtual NOU::NOU_DAT_ALG::String8 getTexture() override;

		NOE_PLUGIN_FUNC virtual NOU::sizeType getID() override;
	};

}
#endif
