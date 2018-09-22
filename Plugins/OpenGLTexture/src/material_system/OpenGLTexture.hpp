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
	/**
	 * brief To identify the Program.
	 */
		NOU::sizeType m_ID;
	/**
	 * brief To identify the texture id.
	 */
		NOU::uint32 m_textureId;

	/**
	 * brief Stores the path of the texture.
	 */
		NOU::NOU_DAT_ALG::String8 m_pathToTexture;
	/**
	 * brief Streos the whole texture.
	 */
		NOU::NOU_DAT_ALG::String8 m_Texture;

	/**
	 * brief Boolean to activate and deactivate the mipmap's.
	 */
		NOU::boolean m_activateMipmaps;
	/**
	 * brief Boolean to controll if the texture should be flipped or not.
	 */
		NOU::boolean m_textureIsFliped;

	public:
	/**
	 * param	NOU::sizeType ID, the id of the program.
	 * 
	 * brief The Constructor.
	 */
		NOE_PLUGIN_FUNC OpenGLTexture(NOU::sizeType ID);
	/**
	 * param	NOU::sizeType ID, the id of the program.
	 * param	const NOU::NOU_DAT_ALG::String8 &pathToTexture, the path to the texture.
	 * 
	 * brief Boolean to controll if the texture should be flipped or not.
	 */
		NOE_PLUGIN_FUNC OpenGLTexture(NOU::sizeType ID, const NOU::NOU_DAT_ALG::String8 &pathToTexture);

	/**
	 * brief Standard constructor.
	 */
		NOE_PLUGIN_FUNC virtual ~OpenGLTexture() = default;

	/**
	 * return	NOU::boolean.
	 * 
	 * brief Binds the texture to the corresponding program.
	 */
		NOE_PLUGIN_FUNC virtual NOU::boolean Bind() override;
	/**
	 * return	NOU::boolean.
	 * 
	 * brief Unbinds the texture to the corresponding program.
	 */
		NOE_PLUGIN_FUNC virtual NOU::boolean Unbind() override;

	/**
	 * param	NOU::boolean mbool.
	 * 
	 * return	NOU::boolean.
	 * 
	 * brief Function to controll wether the texture should generate mipmaps or not.
	 */
		NOE_PLUGIN_FUNC virtual NOU::boolean GenerateMipmap(NOU::boolean mbool) override;
	/**
	 * param	NOU::boolean mbool.
	 * 
	 * return	NOU::boolean.
	 * 
	 * brief Function to controll wether the texture should generate mipmaps or not.
	 */
		NOE_PLUGIN_FUNC virtual NOU::boolean FlipTexture(NOU::boolean mbool) override;

	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &pathToTexture, path to the texture.
	 * param	NOU::sizeType width, width of the texture.
	 * param	NOU::sizeType heigth, heigth of the texture.
	 * 
	 * return	NOU::boolean.
	 * 
	 * brief Function that loads a texture in a string.
	 */
		NOE_PLUGIN_FUNC virtual NOU::boolean LoadTexture(const NOU::NOU_DAT_ALG::String8 &pathToTexture, NOU::sizeType width, NOU::sizeType heigth) override;

	/**
	 * return	NOU::NOU_DAT_ALG::String8.
	 * 
	 * brief Returns texture of the Object.
	 */
		NOE_PLUGIN_FUNC virtual NOU::NOU_DAT_ALG::String8 getTexture() override;

	/**
	 * return	NOU::sizeType.
	 * 
	 * brief Returns the ID.
	 */
		NOE_PLUGIN_FUNC virtual NOU::sizeType getID() override;
	};

}
#endif
