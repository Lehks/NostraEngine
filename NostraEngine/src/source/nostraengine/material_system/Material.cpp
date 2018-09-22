#include "nostraengine/material_system/Material.hpp"

namespace NOE::NOE_MATSYS
{
	NOU::boolean Material::bindShader()
	{
		m_shader->bind();
		return true;
	}

	NOU::boolean Material::unbindShader()
	{
		m_shader->unbind();
		return true;
	}

	NOU::boolean Material::bindTexture()
	{
		m_texture->bind();
		return true;
	}

	NOU::boolean Material::unbindTexture()
	{
		m_texture->unbind();
		return true;
	}

	NOU::boolean Material::Init()
	{
		setColorUniform();

		setAmbientColorLightningUniform();
		setEmissionColorLightningUniform();
		setSpecularColorLightningUniform();
		setDiffuseColorLightningUniform();

		setAmbientColorMaterialUniform();
		setEmissionColorMaterialUniform();
		return true;
	}

	NOU::boolean Material::setTextureUniform()
	{

		return true;
	}

	NOU::boolean Material::setColorUniform()
	{
		NOU::NOU_DAT_ALG::String8 uname("m_color");
		setUniform(uname, this->m_color.getRed(), this->m_color.getGreen(), this->m_color.getBlue(), this->m_color.getAlpha());
		return true;

	}

	NOU::boolean Material::setAmbientColorMaterialUniform()
	{
		NOU::NOU_DAT_ALG::String8 uname("m_ambientColorMaterial");
		setUniform(uname, this->m_color.getRed(), this->m_color.getGreen(), this->m_color.getBlue(), this->m_color.getAlpha());
		return true;
	}

	NOU::boolean Material::setEmissionColorMaterialUniform()
	{
		NOU::NOU_DAT_ALG::String8 uname("m_emissionColorMaterial");
		setUniform(uname, this->m_color.getRed(), this->m_color.getGreen(), this->m_color.getBlue(), this->m_color.getAlpha());
		return true;
	}

	NOU::boolean Material::setAmbientColorLightningUniform()
	{
		NOU::NOU_DAT_ALG::String8 uname("m_ambientColorLightning");
		setUniform(uname, this->m_color.getRed(), this->m_color.getGreen(), this->m_color.getBlue(), this->m_color.getAlpha());
		return true;
	}

	NOU::boolean Material::setEmissionColorLightningUniform()
	{
		NOU::NOU_DAT_ALG::String8 uname("m_emissionColorLightning");
		setUniform(uname, this->m_color.getRed(), this->m_color.getGreen(), this->m_color.getBlue(), this->m_color.getAlpha());
		return true;
	}

	NOU::boolean Material::setSpecularColorLightningUniform()
	{
		NOU::NOU_DAT_ALG::String8 uname("m_specularColorLightning");
		setUniform(uname, this->m_color.getRed(), this->m_color.getGreen(), this->m_color.getBlue(), this->m_color.getAlpha());
		return true;
	}

	NOU::boolean Material::setDiffuseColorLightningUniform()
	{
		NOU::NOU_DAT_ALG::String8 uname("m_diffuseColorLightning");
		setUniform(uname, this->m_color.getRed(), this->m_color.getGreen(), this->m_color.getBlue(), this->m_color.getAlpha());
		return true;
	}
	//-------------------- public ---------------------

	Material::Material(const NOU::NOU_DAT_ALG::String8 &materialName) :
		m_materialName(materialName),
		m_shader(nullptr),
		m_texture(nullptr),
		m_normalMappingIsActive(true),
		m_parrallaxMappingIsActive(false),
		m_lightningIsActive(false),
		m_mipMappingIsActive(false)
	{
		NOU::NOU_MATH::Color32f tmpColor;
		tmpColor.setRed(255);
		tmpColor.setGreen(255);
		tmpColor.setBlue(255);
		tmpColor.setAlpha(255);

		this->m_color = tmpColor;

		this->m_emissionColorMaterial = tmpColor;
		this->m_ambientColorMaterial = tmpColor;

		this->m_emissionColorLightning = tmpColor;
		this->m_ambientColorLightning = tmpColor;
		this->m_diffuseColorLightning = tmpColor;
		this->m_specularColorLightning = tmpColor;

		createUniform("m_texture");

		createUniform("m_color");
		createUniform("m_ambientColorMaterial");
		createUniform("m_emissionColorMaterial");
		createUniform("m_ambientColorLightning");
		createUniform("m_emissionColorLightning");
		createUniform("m_specularColorLightning");
		createUniform("m_diffuesColorLightning");

		Init();

	}

	Material::Material(const NOU::NOU_DAT_ALG::String8 &materialName, NOE::NOE_MATSYS::Program *shader) :
		m_materialName(materialName),
		m_shader(shader),
		m_texture(nullptr),
		m_normalMappingIsActive(true),
		m_parrallaxMappingIsActive(false),
		m_lightningIsActive(false),
		m_mipMappingIsActive(false)
	{
		NOU::NOU_MATH::Color32f tmpColor;
		tmpColor.setRed(255);
		tmpColor.setGreen(255);
		tmpColor.setBlue(255);
		tmpColor.setAlpha(255);

		this->m_color = tmpColor;

		this->m_emissionColorMaterial = tmpColor;
		this->m_ambientColorMaterial = tmpColor;

		this->m_emissionColorLightning = tmpColor;
		this->m_ambientColorLightning = tmpColor;
		this->m_diffuseColorLightning = tmpColor;
		this->m_specularColorLightning = tmpColor;

		createUniform("m_texture");

		createUniform("m_color");
		createUniform("m_ambientColorMaterial");
		createUniform("m_emissionColorMaterial");
		createUniform("m_ambientColorLightning");
		createUniform("m_emissionColorLightning");
		createUniform("m_specularColorLightning");
		createUniform("m_diffuesColorLightning");

		Init();

	}

	Material::Material(const NOU::NOU_DAT_ALG::String8 &materialName, NOE::NOE_MATSYS::Program *shader, NOE::NOE_MATSYS::Texture *texture) :
		m_materialName(materialName),
		m_shader(shader),
		m_texture(texture),
		m_normalMappingIsActive(true),
		m_parrallaxMappingIsActive(false),
		m_lightningIsActive(false),
		m_mipMappingIsActive(false)
	{
		NOU::NOU_MATH::Color32f tmpColor;
		tmpColor.setRed(255);
		tmpColor.setGreen(255);
		tmpColor.setBlue(255);
		tmpColor.setAlpha(255);

		this->m_color = tmpColor;

		this->m_emissionColorMaterial = tmpColor;
		this->m_ambientColorMaterial = tmpColor;

		this->m_emissionColorLightning = tmpColor;
		this->m_ambientColorLightning = tmpColor;
		this->m_diffuseColorLightning = tmpColor;
		this->m_specularColorLightning = tmpColor;

		createUniform("m_texture");

		createUniform("m_color");
		createUniform("m_ambientColorMaterial");
		createUniform("m_emissionColorMaterial");
		createUniform("m_ambientColorLightning");
		createUniform("m_emissionColorLightning");
		createUniform("m_specularColorLightning");
		createUniform("m_diffuesColorLightning");

		Init();

	}

	Material::Material(const NOU::NOU_DAT_ALG::String8 &materialName, NOE::NOE_MATSYS::Program *shader, NOE::NOE_MATSYS::Texture *texture, const NOU::NOU_MATH::Color32f &color) :
		m_materialName(materialName),
		m_shader(shader),
		m_texture(texture),
		m_color(color),
		m_normalMappingIsActive(true),
		m_parrallaxMappingIsActive(false),
		m_lightningIsActive(false),
		m_mipMappingIsActive(false)
	{
		NOU::NOU_MATH::Color32f tmpColor;
		tmpColor.setRed(255);
		tmpColor.setGreen(255);
		tmpColor.setBlue(255);
		tmpColor.setAlpha(255);

		this->m_emissionColorMaterial = tmpColor;
		this->m_ambientColorMaterial = tmpColor;

		this->m_emissionColorLightning = tmpColor;
		this->m_ambientColorLightning = tmpColor;
		this->m_diffuseColorLightning = tmpColor;
		this->m_specularColorLightning = tmpColor;

		createUniform("m_texture");

		createUniform("m_color");
		createUniform("m_ambientColorMaterial");
		createUniform("m_emissionColorMaterial");
		createUniform("m_ambientColorLightning");
		createUniform("m_emissionColorLightning");
		createUniform("m_specularColorLightning");
		createUniform("m_diffuesColorLightning");

		Init();
	}

	Material::~Material() 
	{}

	NOU::boolean Material::bindMaterial()
	{
		
		if (m_texture == nullptr && m_shader == nullptr)
		{
			return false;
		}
		else if(m_texture == nullptr)
		{
			bindShader();
			return true;
		}
		else {
			bindShader();
			bindTexture();
			return true;
		}
	}

	NOU::boolean Material::unbindMaterial()
	{
		if (m_texture == nullptr && m_shader == nullptr)
		{
			return false;
		}
		else if (m_texture == nullptr)
		{
			unbindShader();
			return true;
		}
		else {
			unbindShader();
			unbindTexture();
			return true;
		}
	}

	NOU::boolean Material::enableLightning()
	{
		m_lightningIsActive = true;
		m_shader->enableLightning();
		return true;
	}

	NOU::boolean Material::disableLightning()
	{
		m_lightningIsActive = false;
		m_shader->disableLightning();
		return true;
	}

	NOU::boolean Material::GenerateMipmap(NOU::boolean mbool)
	{
		if (mbool == true)
		{
			m_texture->GenerateMipmap(true);
			return true;
		}
		else {
			m_texture->GenerateMipmap(false);
			return true;
		}
	}

	NOU::boolean Material::FlipTexture(NOU::boolean mbool)
	{
		if (mbool == true)
		{
			m_texture->FlipTexture(true);
			return true;
		}
		else {
			m_texture->FlipTexture(false);
			return true;
		}

	}

	NOU::boolean Material::enableNormalMapping(const NOE::NOE_MATSYS::Texture &normalMap)
	{
		m_normalMappingIsActive = true;
		m_parrallaxMappingIsActive = false;
		return true;
	}

	NOU::boolean Material::enableParrallaxMapping(const NOE::NOE_MATSYS::Texture &displacementMap)
	{
		m_normalMappingIsActive = false;
		m_parrallaxMappingIsActive = true;
		return true;
	}

	NOU::boolean Material::saveMaterial(const NOU::NOU_DAT_ALG::String8 &pathToSave)
	{
		return true;
	}

	NOU::boolean Material::loadMaterial(const NOU::NOU_DAT_ALG::String8 &pathToMaterial)
	{
		return true;
	}

	void Material::setMaterialName(const NOU::NOU_DAT_ALG::String8 &materialName)
	{
		this->m_materialName = materialName;
	}

	void Material::setShader(NOE::NOE_MATSYS::Program *shader)
	{
		this->m_shader = shader;
	}

	void Material::setTexture(NOE::NOE_MATSYS::Texture *texture)
	{
		this->m_texture = texture;
	}

	void Material::setColor(const NOU::NOU_MATH::Color32f &color)
	{
		this->m_color = color;
	}

	void Material::setColor(NOU::float32 r, NOU::float32 g, NOU::float32 b, NOU::byte a)
	{
		NOU::NOU_MATH::Color32f tmpColor;
		tmpColor.setRed(r);
		tmpColor.setGreen(g);
		tmpColor.setBlue(b);
		tmpColor.setAlpha(a);
		this->m_color = tmpColor;

		setColorUniform();
	}

	//Material / Mesh
	void Material::setAmbientColorMaterial(const NOU::NOU_MATH::Color32f &color)
	{
		this->m_ambientColorMaterial = color;

		setAmbientColorMaterialUniform();
	}

	void Material::setAmbientColorMaterial(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a)
	{
		NOU::NOU_MATH::Color32f tmpColor;
		tmpColor.setRed(r);
		tmpColor.setGreen(g);
		tmpColor.setBlue(b);
		tmpColor.setAlpha(a);
		this->m_ambientColorMaterial = tmpColor;

		setAmbientColorMaterialUniform();
	}

	void Material::setEmissionColorMaterial(const NOU::NOU_MATH::Color32f &color)
	{
		this->m_emissionColorMaterial = color;

		setEmissionColorMaterialUniform();
	}

	void Material::setEmissionColorMaterial(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a)
	{
		NOU::NOU_MATH::Color32f tmpColor;
		tmpColor.setRed(r);
		tmpColor.setGreen(g);
		tmpColor.setBlue(b);
		tmpColor.setAlpha(a);
		this->m_emissionColorMaterial = tmpColor;

		setEmissionColorMaterialUniform();

	}

	//Lightning
	void Material::setAmbientColorLightning(const NOU::NOU_MATH::Color32f &color)
	{
		this->m_ambientColorLightning = color;

		setAmbientColorLightningUniform();
	}

	void Material::setAmbientColorLightning(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a)
	{
		NOU::NOU_MATH::Color32f tmpColor;
		tmpColor.setRed(r);
		tmpColor.setGreen(g);
		tmpColor.setBlue(b);
		tmpColor.setAlpha(a);
		this->m_ambientColorLightning = tmpColor;

		setAmbientColorLightningUniform();

	}

	void Material::setDiffuseColorLightning(const NOU::NOU_MATH::Color32f &color)
	{
		this->m_diffuseColorLightning = color;

		setDiffuseColorLightningUniform();

	}

	void Material::setDiffuseColorLightning(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a)
	{
		NOU::NOU_MATH::Color32f tmpColor;
		tmpColor.setRed(r);
		tmpColor.setGreen(g);
		tmpColor.setBlue(b);
		tmpColor.setAlpha(a);
		this->m_diffuseColorLightning = tmpColor;

		setDiffuseColorLightningUniform();

	}

	void Material::setSpecularColorLightning(const NOU::NOU_MATH::Color32f &color)
	{
		this->m_specularColorLightning = color;

		setSpecularColorLightningUniform();
	}

	void Material::setSpecularColorLightning(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a)
	{
		NOU::NOU_MATH::Color32f tmpColor;
		tmpColor.setRed(r);
		tmpColor.setGreen(g);
		tmpColor.setBlue(b);
		tmpColor.setAlpha(a);
		this->m_specularColorLightning = tmpColor;

		setSpecularColorLightningUniform();

	}

	NOU::boolean Material::createUniform(const NOU::NOU_DAT_ALG::String8 &name)
	{
		this->m_shader->createUniform(name);
		return true;
	}

	NOU::boolean Material::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::boolean value)
	{
		this->m_shader->setUniform(name, value);
		return true;
	}

	NOU::boolean Material::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::sizeType value)
	{
		this->m_shader->setUniform(name, value);
		return true;
	}

	NOU::boolean Material::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 value)
	{
		this->m_shader->setUniform(name, value);
		return true;
	}

	NOU::boolean Material::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue)
	{
		this->m_shader->setUniform(name, xvalue, yvalue);
		return true;
	}

	NOU::boolean Material::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec2 &vec)
	{
		this->m_shader->setUniform(name, vec);
		return true;
	}

	NOU::boolean Material::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue)
	{
		this->m_shader->setUniform(name, xvalue, yvalue, zvalue);
		return true;
	}

	NOU::boolean Material::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec3 &vec)
	{
		this->m_shader->setUniform(name, vec);
		return true;
	}

	NOU::boolean Material::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue, NOU::float32 wvalue)
	{
		this->m_shader->setUniform(name, xvalue, yvalue, zvalue, wvalue);
		return true;
	}

	NOU::boolean Material::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec4 &vec)
	{
		this->m_shader->setUniform(name, vec);
		return true;
	}

	NOU::boolean Material::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat2 &mat)
	{
		this->m_shader->setUniform(name, mat);
		return true;
	}

	NOU::boolean Material::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat3 &mat)
	{
		this->m_shader->setUniform(name, mat);
		return true;
	}

	NOU::boolean Material::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat4 &mat)
	{
		this->m_shader->setUniform(name, mat);
		return true;
	}

	NOU::NOU_DAT_ALG::String8 Material::getMaterialName() const
	{
		return this->m_materialName;
	}

	NOU::NOU_MATH::Color32f Material::getColor() const
	{
		return this->m_color;
	}

	NOU::NOU_MATH::Color32f Material::getAmbientColorMaterial() const
	{
		return this->m_ambientColorMaterial;
	}

	NOU::NOU_MATH::Color32f Material::getEmissionColorMaterial() const
	{
		return this->m_emissionColorMaterial;
	}

	NOU::NOU_MATH::Color32f Material::getAmbientColorLightning() const
	{
		return this->m_ambientColorLightning;
	}

	NOU::NOU_MATH::Color32f Material::getDiffuseColorLightning() const
	{
		return this->m_diffuseColorLightning;
	}

	NOU::NOU_MATH::Color32f Material::getSpecularColorLightning() const
	{
		return this->m_specularColorLightning;
	}

	NOU::NOU_MATH::Color32f Material::getEmissionColorLightning() const
	{
		return this->m_emissionColorLightning;
	}

	Program* Material::getProgram() const
	{
		return m_shader;
	}

	Texture* Material::getTexture() const
	{
		return m_texture;
	}
}