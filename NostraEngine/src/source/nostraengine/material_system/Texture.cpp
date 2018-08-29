#include "nostraengine/material_system/Texture.hpp"

namespace NOE::NOE_MATSYS
{
	Texture::Texture(NOU::sizeType ID) : 
		ID(ID) 
	{}

	Texture::Texture(NOU::sizeType ID, const NOU::NOU_DAT_ALG::String8 &pathToTexture) :
		ID(ID),
		pathToTexture(pathToTexture)
	{}

	NOU::boolean Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	NOU::boolean Texture::unbind()
	{
		glDeleteTextures(id);
	}

	NOU::boolean Texture::loadTexture(const NOU::NOU_DAT_ALG::String8 &pathToTexture = nullptr)
	{

	}

	NOU::sizeType Texture::getID()
	{
		return this.m_ID;
	}

}