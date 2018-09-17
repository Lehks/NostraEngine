#include "OpenGLTexture.hpp"

namespace OpenGLTexturePlugin
{
	OpenGLTexture::OpenGLTexture(NOU::sizeType ID) :
		m_ID(ID), // ID -> m_ID
		m_activateMipmaps(true),
		m_textureIsFliped(true)
	{}

	OpenGLTexture::OpenGLTexture(NOU::sizeType ID, const NOU::NOU_DAT_ALG::String8 &pathToTexture) :
		m_ID(ID), // ID -> m_ID
		m_pathToTexture(pathToTexture), // pathoToTexture -> m_pathToTexture
		m_activateMipmaps(true),
		m_textureIsFliped(true)
	{}

	NOU::boolean OpenGLTexture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	NOU::boolean OpenGLTexture::unbind()
	{

	}

	NOU::boolean OpenGLTexture::GenerateMipmap(NOU::boolean mbool)
	{
		if (mbool == true)
		{
			m_activateMipmaps = true;
			return true;
		}
		else {
			m_activateMipmaps = false;
			return true;
		}
	}

	NOU::boolean OpenGLTexture::FlipTexture(NOU::boolean mbool)
	{
		if (mbool == true)
		{
			m_textureIsFliped = true;
			return true;
		}
		else {
			m_textureIsFliped = false;
			return true;
		}
	}

	NOU::boolean OpenGLTexture::loadTexture(const NOU::NOU_DAT_ALG::String8 &pathToTexture, NOU::sizeType width, NOU::sizeType heigth)
	{
		NOU::char32 *data = nullptr;

		glGenTextures(1, &m_textureId);

		glBindTexture(GL_TEXTURE_2D, m_textureId);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		if (m_activateMipmaps == true)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		return true;
	}

	NOU::sizeType OpenGLTexture::getID()
	{
		return this->m_ID;
	}

	NOU::NOU_DAT_ALG::String8 OpenGLTexture::getTexture()
	{
		return m_Texture;
	}

}
