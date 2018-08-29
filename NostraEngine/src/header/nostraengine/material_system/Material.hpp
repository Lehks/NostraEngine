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

		NOU::NOU_MATH::Color m_color;
		NOU::NOU_MATH::Color m_ambientColor;
		NOU::NOU_MATH::Color m_diffuseColor;
		NOU::NOU_MATH::Color m_specularColor;
		NOU::NOU_MATH::Color m_emissionColor;

		NOU::boolean m_parrallaxMappingisActive;
		NOU::boolean m_normalMappingisActive;
		NOU::boolean m_bumpMappingisActive;

		NOU::boolean createShader();
		NOU::boolean createTexture();
	public:
		Material(const NOU_DAT_ALG::String8 &materialName);
		Material(const NOU_DAT_ALG::String8 &materialName, const Program &shader);
		Material(const NOU_DAT_ALG::String8 &materialName, const Program &shader, const Texture &texture);
		Material(const NOU_DAT_ALG::String8 &materialName, const Program &shader, const Texture &texture, const NOU::NOU_MATH::Color &color);

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

		void setColor(const NOU::NOU_MATH::Color &color);
		void setColor(NOU::float32 r, NOU::float32 g, NOU::float32 b, NOU::float32 a = 1.0f);

		void setAmbientColor(const NOU::NOU_MATH::Color &color);
		void setAmbientColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::float32 a = 1.0f);
		void setDiffuseColor(const NOU::NOU_MATH::Color &color);
		void setDiffuseColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::float32 a = 1.0f);
		void setSpecularColor(const NOU::NOU_MATH::Color &color);
		void setSpecularColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::float32 a = 1.0f);
		void setEmissionColor(const NOU::NOU_MATH::Color &color);
		void setEmissionColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::float32 a = 1.0f);

		NOU::NOU_DAT_ALG::String8 getMaterialName();

		NOU::NOU_MATH::Color getColor();
		NOU::NOU_MATH::Color getAmbientColor();
		NOU::NOU_MATH::Color getDiffuseColor();
		NOU::NOU_MATH::Color getSpecularColor();
		NOU::NOU_MATH::Color getEmissionColor();
	}
}
#endif