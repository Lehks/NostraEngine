#ifndef NOE_MATSYS_MATERIAL_HPP
#define NOE_MATSYS_MATERIAL_HPP

#include "nostraengine/NostraEngine.hpp"
#include "nostrautils/NostraUtils.hpp"
/**
\file material_system/GLMaterial.hpp

\author  Dennis Franz
\version 0.0.1
\since   0.0.1

\brief A file that provides the functionality for the Material.
*/

namespace NOE::NOE_MATSYS
{
	class Material
	{
	private:
	/**
	 * brief The name of the material.
	 */
		NOU::NOU_DAT_ALG::String8 m_materialName;

	/**
	 * brief A pointer to the Shader Program.
	 */
		NOE::NOE_MATSYS::Program *m_shader;
	/**
	 * brief A pointer to the texture.
	 */
		NOE::NOE_MATSYS::Texture *m_texture;

	/**
	 * brief A Variable the stores a color for the Mesh.
	 */
		NOU::NOU_MATH::Color32f m_color;
	/**
	 * brief A Variable the stores the ambiente color of the mesh.
	 */
		NOU::NOU_MATH::Color32f m_ambientColorMaterial;
	/**
	 * brief A Variable the stores the emission color of the mesh.
	 */
		NOU::NOU_MATH::Color32f m_emissionColorMaterial;
	/**
	 * brief A Variable the stores the ambient color of the lightning.
	 */
		NOU::NOU_MATH::Color32f m_ambientColorLightning;
	/**
	 * brief A Variable the stores the diffuse color of the lightning.
	 */
		NOU::NOU_MATH::Color32f m_diffuseColorLightning;
	/**
	 * brief A Variable the stores the specular color of the lightning.
	 */
		NOU::NOU_MATH::Color32f m_specularColorLightning;
	/**
	 * brief A Variable the stores the emission color of the lightning.
	 */
		NOU::NOU_MATH::Color32f m_emissionColorLightning;


	/**
	 * brief A boolean that controlls if normalmapping should be active or not.
	 */
		NOU::boolean m_normalMappingIsActive;
	/**
	 * brief A boolean that controlls if parrallaxmapping should be active or not.
	 */
		NOU::boolean m_parrallaxMappingIsActive;

	/**
	 * brief A boolean that controlls if lightning should be active or not.
	 */
		NOU::boolean m_lightningIsActive;
	/**
	 * brief A boolean that controlls if mipmapping should be active or not.
	 */
		NOU::boolean m_mipMappingIsActive;

	/**
	 * return	NOU::boolean.
	 * 
	 * brief A function that binds the shader.
	 */
	 	NOU::boolean bindShader();
	/**
	 * return	NOU::boolean.
	 * 
	 * brief A function that unbinds the shader.
	 */
	 	NOU::boolean unbindShader();

	/**
	 * return	NOU::boolean.
	 * 
	 * brief A function that binds the texture.
	 */
	 	NOU::boolean bindTexture();
		 	/**
	 * return	NOU::boolean.
	 * 
	 * brief A function that unbinds the texture.
	 */
	 	NOU::boolean unbindTexture();
	public:
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &materialName, the name of the material.
	 * 
	 * brief A constructor for the material.
	 */
		Material(const NOU::NOU_DAT_ALG::String8 &materialName);
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &materialName, the name of the material.
	 * param	const NOE::NOE_MATSYS::Program *shader, a pointer to a shader progam class.
	 * 
	 * brief A constructor for the material.
	 */
	 	Material(const NOU::NOU_DAT_ALG::String8 &materialName, NOE::NOE_MATSYS::Program *shader);
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &materialName, the name of the material.
	 * param	const NOE::NOE_MATSYS::Program *shader, a pointer to a shader progam class.
	 * param	const NOE::NOE_MATSYS::Texture *texture, a pionter to a texture class.
	 * 
	 * brief A constructor for the material.
	 */
	 	Material(const NOU::NOU_DAT_ALG::String8 &materialName, NOE::NOE_MATSYS::Program *shader, NOE::NOE_MATSYS::Texture *texture);
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &materialName, the name of the material.
	 * param	const NOE::NOE_MATSYS::Program *shader, a pointer to a shader progam class.
	 * param	const NOE::NOE_MATSYS::Texture *texture, a pionter to a texture class.
	 * param	const NOU::NOU_MATH::Color32f &color, a color for the mesh / material.
	 * 
	 * brief A constructor for the material.
	 */
	 	Material(const NOU::NOU_DAT_ALG::String8 &materialName, NOE::NOE_MATSYS::Program *shader, NOE::NOE_MATSYS::Texture *texture, const NOU::NOU_MATH::Color32f &color);

	/**
	 * brief A standard destructor for the material..
	 */
     	~Material();

	 	NOU::boolean bindMaterial();
	 	NOU::boolean unbindMaterial();

	 	NOU::boolean enableLightning();
		NOU::boolean disableLightning();

		//Texture
	 	NOU::boolean GenerateMipmap(NOU::boolean mbool);
		NOU::boolean FlipTexture(NOU::boolean mbool);

		NOU::boolean enableNormalMapping(const NOE::NOE_MATSYS::Texture &normalMap);
		NOU::boolean enableParrallaxMapping(const NOE::NOE_MATSYS::Texture &displacementMap);

	 	NOU::boolean saveMaterial(const NOU::NOU_DAT_ALG::String8 &pathToSave);
	 	NOU::boolean loadMaterial(const NOU::NOU_DAT_ALG::String8 &pathToMaterial);

	 	void setMaterialName(const NOU::NOU_DAT_ALG::String8 &materialName);

	 	void setShader(NOE::NOE_MATSYS::Program *shader);
		void setTexture(NOE::NOE_MATSYS::Texture *texture);

		void setColor(const NOU::NOU_MATH::Color32f &color);
	 	void setColor(NOU::float32 r, NOU::float32 g, NOU::float32 b, NOU::byte a = 255);

		//Material / Mesh
	    void setAmbientColorMaterial(const NOU::NOU_MATH::Color32f &color);
	 	void setAmbientColorMaterial(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255);
	  	void setEmissionColorMaterial(const NOU::NOU_MATH::Color32f &color);
		void setEmissionColorMaterial (NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255);

		//Lightning
		void setAmbientColorLightning(const NOU::NOU_MATH::Color32f &color);
		void setAmbientColorLightning(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255);
		void setDiffuseColorLightning(const NOU::NOU_MATH::Color32f &color);
		void setDiffuseColorLightning(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255);
		void setSpecularColorLightning(const NOU::NOU_MATH::Color32f &color);
		void setSpecularColorLightning(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255);

		NOU::boolean createUniform(const NOU::NOU_DAT_ALG::String8 &name);
		NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::boolean value);
		NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::sizeType value);
		NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 value);
		NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue);
		NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec2 &vec);
		NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue);
		NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec3 &vec);
		NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue, NOU::float32 wvalue);
		NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec4 &vec);
		NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat2 &mat);
		NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat3 &mat);
		NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat4 &mat);

	  	NOU::NOU_DAT_ALG::String8 getMaterialName() const;

	  	NOU::NOU_MATH::Color32f getColor() const;
	  	NOU::NOU_MATH::Color32f getAmbientColorMaterial() const;
		NOU::NOU_MATH::Color32f getEmissionColorMaterial() const;

		NOU::NOU_MATH::Color32f getAmbientColorLightning() const;
	  	NOU::NOU_MATH::Color32f getDiffuseColorLightning() const;
	  	NOU::NOU_MATH::Color32f getSpecularColorLightning() const;
		NOU::NOU_MATH::Color32f getEmissionColorLightning() const;

		NOE::NOE_MATSYS::Program* getProgram() const;
		NOE::NOE_MATSYS::Texture* getTexture() const;

	};
}
#endif
