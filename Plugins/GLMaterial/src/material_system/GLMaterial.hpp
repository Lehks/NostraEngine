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

namespace GLMaterialPlugin
{
	class Material : public NOE::NOE_MATSYS::Material.hpp
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

		NOE_PLUGIN_FUNC virtual NOU::boolean bindShader() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean unbindShader() override;

		NOE_PLUGIN_FUNC virtual NOU::boolean bindTexture() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean unbindTexture() override;
	public:
		NOE_PLUGIN_FUNC Material(const NOU::NOU_DAT_ALG::String8 &materialName);
		NOE_PLUGIN_FUNC Material(const NOU::NOU_DAT_ALG::String8 &materialName, const Program &shader);
		NOE_PLUGIN_FUNC Material(const NOU::NOU_DAT_ALG::String8 &materialName, const Program &shader, const Texture &texture);
		NOE_PLUGIN_FUNC Material(const NOU::NOU_DAT_ALG::String8 &materialName, const Program &shader, const Texture &texture, const NOU::NOU_MATH::Color32f &color);

        NOE_PLUGIN_FUNC virtual ~Material() override;

		NOE_PLUGIN_FUNC virtual NOU::boolean bindMaterial() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean unbindMaterial() override;

		NOE_PLUGIN_FUNC virtual NOU::boolean enableNormalMapping(const NOE::NOE_MATSYS::Texture &normalMap) override;
		NOE_PLUGIN_FUNC virtual NOU::boolean enableParrallaxMapping(const NOE::NOE_MATSYS::Texture &displacementMap) override;

		NOE_PLUGIN_FUNC virtual NOU::boolean enableLightning() override;

		NOE_PLUGIN_FUNC virtual NOU::boolean generateMipmap() override;

		NOE_PLUGIN_FUNC virtual NOU::boolean saveMaterial(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_DAT_ALG::String8 &pathToMaterial) override;
		NOE_PLUGIN_FUNC virtual NOU::boolean loadMaterial(const NOU::NOU_DAT_ALG::String8 &pathToMaterial) override;

		NOE_PLUGIN_FUNC virtual void setMaterialName(const NOU::NOU_DAT_ALG::String8 &materialName) override;

		NOE_PLUGIN_FUNC virtual void setShader(const NOE::NOE_MATSYS::Program &shader) override;
		NOE_PLUGIN_FUNC virtual void setTexture(const NOE::NOE_MATSYS::Texture &texture) override;

		NOE_PLUGIN_FUNC virtual void setColor(const NOU::NOU_MATH::Color32f &color) override;
		NOE_PLUGIN_FUNC virtual void setColor(NOU::float32 r, NOU::float32 g, NOU::float32 b, NOU::byte a = 255) override;

		NOE_PLUGIN_FUNC virtual void setAmbientColor(const NOU::NOU_MATH::Color32f &color) override;
		NOE_PLUGIN_FUNC virtual void setAmbientColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255) override;
		NOE_PLUGIN_FUNC virtual void setDiffuseColor(const NOU::NOU_MATH::Color32f &color) override;
		NOE_PLUGIN_FUNC virtual void setDiffuseColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255) override;
		NOE_PLUGIN_FUNC virtual void setSpecularColor(const NOU::NOU_MATH::Color32f &color) override;
		NOE_PLUGIN_FUNC virtual void setSpecularColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255) override;
		NOE_PLUGIN_FUNC virtual void setEmissionColor(const NOU::NOU_MATH::Color32f &color) override;
		NOE_PLUGIN_FUNC virtual void setEmissionColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255) override;

		NOE_PLUGIN_FUNC virtual NOU::NOU_DAT_ALG::String8 getMaterialName() const override;

		NOE_PLUGIN_FUNC virtual NOU::NOU_MATH::Color32f getColor() const override;
		NOE_PLUGIN_FUNC virtual NOU::NOU_MATH::Color32f getAmbientColor() const override;
		NOE_PLUGIN_FUNC virtual NOU::NOU_MATH::Color32f getDiffuseColor() const override;
		NOE_PLUGIN_FUNC virtual NOU::NOU_MATH::Color32f getSpecularColor() const override;
		NOE_PLUGIN_FUNC virtual NOU::NOU_MATH::Color32f getEmissionColor() const override;

		NOE_PLUGIN_FUNC virtual NOE::NOE_MATSYS::Program getProgram() const override;
	};
}
#endif
