#include "nostraengine/material_system/Texture.hpp"

namespace NOE::NOE_MATSYS
{
	Texture::Texture(NOU::sizeType ID) :
		m_ID(ID) // ID -> m_ID
	{}

	Texture::Texture(NOU::sizeType ID, const NOU::NOU_DAT_ALG::String8 &pathToTexture) :
		m_ID(ID), // ID -> m_ID
		m_pathToTexture(pathToTexture) // pathoToTexture -> m_pathToTexture
	{}

	NOU::boolean Texture::loadTexture(const NOU::NOU_DAT_ALG::String8 &pathToTexture)
	{
		return true;
	}

	NOU::sizeType Texture::getID()
	{
		
		return this->m_ID;
	}

}
