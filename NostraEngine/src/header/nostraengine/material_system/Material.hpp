#ifndef NOE_MATSYS_MATERIAL_HPP
#define NOE_MATSYS_MATERIAL_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/NostraEngine.hpp"
#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/material_system/Program.hpp"
#include "nostraengine/material_system/Texture.hpp"

/**
\author	 Dennis Franz
\version 1.0.0
\since   1.0.0
*/

namespace NOE::NOE_MATSYS
{
	
	class Material
	{
		virtual NOU::boolean bindShader() = 0;
		virtual NOU::boolean unbindShader() = 0;

		virtual NOU::boolean bindTexture() = 0;
		virtual NOU::boolean unbindTexture() = 0;
	public:

		virtual NOU::boolean bindMaterial() = 0;
		virtual NOU::boolean unbindMaterial() = 0;

		virtual NOU::boolean enableNormalMapping(const NOE::NOE_MATSYS::Texture& normalMap) = 0;
		virtual NOU::boolean enableParrallaxMapping(const NOE::NOE_MATSYS::Texture& displacementMap) = 0;

		virtual NOU::boolean enableLightning() = 0;

		virtual NOU::boolean generateMipmap() = 0;

		virtual NOU::boolean saveMaterial(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_DAT_ALG::String8 &pathToMaterial) = 0;
		virtual NOU::boolean loadMaterial(const NOU::NOU_DAT_ALG::String8 &pathToMaterial) = 0;

		virtual void setMaterialName(const NOU::NOU_DAT_ALG::String8 &materialName) = 0;

		virtual void setShader(const Program &shader) = 0; // same namespace no need to fully qualify the namespace name
		virtual void setTexture(const NOE::NOE_MATSYS::Texture &texture) = 0;

		virtual void setColor(const NOU::NOU_MATH::Color32f &color) = 0;
		virtual void setColor(NOU::float32 r, NOU::float32 g, NOU::float32 b, NOU::byte a = 255) = 0;

		virtual void setAmbientColor(const NOU::NOU_MATH::Color32f &color) = 0;
		virtual void setAmbientColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255) = 0;
		virtual void setDiffuseColor(const NOU::NOU_MATH::Color32f &color) = 0;
		virtual void setDiffuseColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255) = 0;
		virtual void setSpecularColor(const NOU::NOU_MATH::Color32f &color) = 0;
		virtual void setSpecularColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255) = 0;
		virtual void setEmissionColor(const NOU::NOU_MATH::Color32f &color) = 0;
		virtual void setEmissionColor(NOU::byte r, NOU::byte g, NOU::byte b, NOU::byte a = 255) = 0;

		virtual NOU::NOU_DAT_ALG::String8 getMaterialName() const = 0;

		virtual NOU::NOU_MATH::Color32f getColor() const = 0;
		virtual NOU::NOU_MATH::Color32f getAmbientColor() const  = 0;
		virtual NOU::NOU_MATH::Color32f getDiffuseColor() const = 0;
		virtual NOU::NOU_MATH::Color32f getSpecularColor() const = 0;
		virtual NOU::NOU_MATH::Color32f getEmissionColor() const = 0;


		virtual Program& getProgram() const = 0; // same namespace no need to fully qualify the name, also cannot construct an abstract class


		virtual ~Material() = default; // Was Monitor before -> Material
	};
}
#endif
