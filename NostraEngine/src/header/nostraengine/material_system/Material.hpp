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
		NOU::NOU_DAT_ALG::String8 m_materialName;

		Program *m_shader;
		Texture *m_texture;

		NOU::NOU_MATH::Color32f m_color;
		NOU::NOU_MATH::Color32f m_ambientColorMaterial;
		NOU::NOU_MATH::Color32f m_emissionColorMaterial;
		NOU::NOU_MATH::Color32f m_ambientColorLightning;
		NOU::NOU_MATH::Color32f m_diffuseColorLightning;
		NOU::NOU_MATH::Color32f m_specularColorLightning;
		NOU::NOU_MATH::Color32f m_emissionColorLightning;

		NOU::boolean m_normalMappingIsActive;
		NOU::boolean m_parrallaxMappingIsActive;

		NOU::boolean m_lightningIsActive;
		NOU::boolean m_mipMappingIsActive;

	 	NOU::boolean bindShader();
	 	NOU::boolean unbindShader();

	 	NOU::boolean bindTexture();
	 	NOU::boolean unbindTexture();
	public:
		Material(const NOU::NOU_DAT_ALG::String8 &materialName);
	 	Material(const NOU::NOU_DAT_ALG::String8 &materialName, Program *shader);
	 	Material(const NOU::NOU_DAT_ALG::String8 &materialName, Program *shader, Texture *texture);
	 	Material(const NOU::NOU_DAT_ALG::String8 &materialName, Program *shader, Texture *texture, const NOU::NOU_MATH::Color32f &color);

     	~Material();

	 	NOU::boolean bindMaterial();
	 	NOU::boolean unbindMaterial();

	 	NOU::boolean enableLightning();
		NOU::boolean disableLightning();

		//Texture
	 	NOU::boolean GenerateMipmap(NOU::boolean mbool);
		NOU::boolean FlipTexture(NOU::boolean mbool);

		NOU::boolean enableNormalMapping(const Texture &normalMap);
		NOU::boolean enableParrallaxMapping(const Texture &displacementMap);

	 	NOU::boolean saveMaterial(const NOU::NOU_DAT_ALG::String8 &pathToSave);
	 	NOU::boolean loadMaterial(const NOU::NOU_DAT_ALG::String8 &pathToMaterial);

	 	void setMaterialName(const NOU::NOU_DAT_ALG::String8 &materialName);

	 	void setShader(Program *shader);
	 	void setTexture(Texture *texture);

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

		Program* getProgram() const;
		Texture* getTexture() const;

	};
}
#endif
