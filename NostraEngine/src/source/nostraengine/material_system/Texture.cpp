#include "nostraengine/material_system/Texture.hpp"

namespace NOE::NOE_MATSYS
{
	Texture::Texture(NOU::sizeType ID) :
		m_ID(ID), // ID -> m_ID
		m_activateMipmaps(true),
		m_textureIsFliped(true)
	{}

	Texture::Texture(NOU::sizeType ID, const NOU::NOU_DAT_ALG::String8 &pathToTexture) :
		m_ID(ID), // ID -> m_ID
		m_pathToTexture(pathToTexture), // pathoToTexture -> m_pathToTexture
		m_activateMipmaps(true),
		m_textureIsFliped(true)
	{}

	NOU::boolean Texture::bind()
	{

	}

	NOU::boolean Texture::unbind()
	{

	}

	NOU::boolean Texture::GenerateMipmap(NOU::boolean mbool)
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

	NOU::boolean Texture::FlipTexture(NOU::boolean mbool)
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

	NOU::boolean Texture::loadTexture(const NOU::NOU_DAT_ALG::String8 &pathToTexture)
	{
		return true;
	}

	NOU::sizeType Texture::getID()
	{
		return this->m_ID;
	}

	NOU::NOU_DAT_ALG::String8 Texture::getTexture()
	{
			return m_Texture;
	}

}
