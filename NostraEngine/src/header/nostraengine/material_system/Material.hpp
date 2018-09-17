#ifndef NOE_MATSYS_MATERIAL_HPP
#define NOE_MATSYS_MATERIAL_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/NostraEngine.hpp"

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
		NOU::NOU_MATH::Color32f m_ambientColor;
		NOU::NOU_MATH::Color32f m_diffuseColor;
		NOU::NOU_MATH::Color32f m_specularColor;
		NOU::NOU_MATH::Color32f m_emissionColor;

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
	 	Material(const NOU::NOU_DAT_ALG::String8 &materialName, const Program &shader);
	 	Material(const NOU::NOU_DAT_ALG::String8 &materialName, const Program &shader, const Texture &texture);
	 	Material(const NOU::NOU_DAT_ALG::String8 &materialName, const Program &shader, const Texture &texture, const NOU::NOU_MATH::Color32f &color);

     	~Material();

	 	NOU::boolean bindMaterial();
	 	NOU::boolean unbindMaterial();

		NOU::boolean enableNormalMapping(const NOE::NOE_MATSYS::Texture &normalMap);
	 	NOU::boolean enableParrallaxMapping(const NOE::NOE_MATSYS::Texture &displacementMap);

	 	NOU::boolean enableLightning();

	 	NOU::boolean generateMipmap();

	 	NOU::boolean saveMaterial(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_DAT_ALG::String8 &pathToMaterial);
	 	NOU::boolean loadMaterial(const NOU::NOU_DAT_ALG::String8 &pathToMaterial);

	 	void setMaterialName(const NOU::NOU_DAT_ALG::String8 &materialName);

	 	void setShader(const NOE::NOE_MATSYS::Program &shader);
	 	void setTexture(const NOE::NOE_MATSYS::Texture &texture);

		void setColor(const NOU::NOU_MATH::Color32f &color);
	 	void setColor(NOU::float32 r, NOU::float32 g, NOU::float32 b, NOU::byte a = 255);

	    void setAmbientColor(const NOU::NOU_MATH::Color32f &color);
	 	void setAmbientColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255);
	  	void setDiffuseColor(const NOU::NOU_MATH::Color32f &color);
	  	void setDiffuseColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255);
	 	void setSpecularColor(const NOU::NOU_MATH::Color32f &color);
		void setSpecularColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255);
	  	void setEmissionColor(const NOU::NOU_MATH::Color32f &color);
	  	void setEmissionColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255);

	  	NOU::NOU_DAT_ALG::String8 getMaterialName() const;

	  	NOU::NOU_MATH::Color32f getColor() const;
	  	NOU::NOU_MATH::Color32f getAmbientColor() const;
	  	NOU::NOU_MATH::Color32f getDiffuseColor() const;
	  	NOU::NOU_MATH::Color32f getSpecularColor() const;
	  	NOU::NOU_MATH::Color32f getEmissionColor() const;

	  	NOE::NOE_MATSYS::Program getProgram() const;
	};
}
#endif
