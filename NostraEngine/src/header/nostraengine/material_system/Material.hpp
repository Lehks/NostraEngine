#ifndef NOE_MATSYS_MATERIAL_HPP
#define NOE_MATSYS_MATERIAL_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/NostraEngine.hpp"

/**
\author	 Dennis Franz
\version 1.0.0
\since   1.0.0
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

		NOU::boolean m_parrallaxMappingisActive;
		NOU::boolean m_normalMappingisActive;
		NOU::boolean m_bumpMappingisActive;

		NOU::boolean createShader();
		NOU::boolean createTexture();
	public:
		Material(const NOU::NOU_DAT_ALG::String8 &materialName);
		Material(const NOU::NOU_DAT_ALG::String8 &materialName, const Program &shader);
		Material(const NOU::NOU_DAT_ALG::String8 &materialName, const Program &shader, const Texture &texture);
		Material(const NOU::NOU_DAT_ALG::String8 &materialName, const Program &shader, const Texture &texture, const NOU::NOU_MATH::Color32f &color);

		NOU::boolean bindShader();
		NOU::boolean unbindShader();

		NOU::boolean bindTexture();
		NOU::boolean unbindTexture();

		NOU::boolean createUniform();
		NOU::boolean setUniform();

		NOU::boolean enableParrallaxMapping();
		NOU::boolean enableNormalMapping();
		NOU::boolean enableBumpMapping();

		NOU::boolean enableLightning();

		NOU::boolean generateMipmap();

		NOU::boolean saveMaterial();
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

		NOU::NOU_DAT_ALG::String8 getMaterialName();

		NOU::NOU_MATH::Color32f getColor();
		NOU::NOU_MATH::Color32f getAmbientColor();
		NOU::NOU_MATH::Color32f getDiffuseColor();
		NOU::NOU_MATH::Color32f getSpecularColor();
		NOU::NOU_MATH::Color32f getEmissionColor();
	};
}
#endif