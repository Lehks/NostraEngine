#ifndef NOE_MATSYS_PROGRAM_HPP
#define NOE_MATSYS_PROGRAM_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/NostraEngine.hpp"

/**
\author	 Dennis Franz
\version 1.0.0
\since   1.0.0
*/

namespace NOE::NOE_MATSYS
{
	class Program
	{
	private:
		virtual NOU::boolean LinkShader() = 0;
		virtual NOU::boolean CreateVertexShader() = 0;
		virtual NOU::boolean CreateFragmetShader() = 0;
		virtual NOU::boolean CreateGeometryShader() = 0;

	public:
		virtual ~Program() = default;
		virtual NOU::boolean CreateShader(const NOU::NOU_DAT_ALG::String8 &vertexShaderSource, const NOU::NOU_DAT_ALG::String8 &fragmentShaderSource, const NOU::NOU_DAT_ALG::String8 &geometryShaderSource = nullptr) = 0;
		virtual NOU::boolean Bind() = 0;
		virtual NOU::boolean Unbind() = 0;
		virtual NOU::boolean CreateUniform(const NOU::NOU_DAT_ALG::String8 &name)  = 0;
		virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::boolean value) = 0;
		virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::sizeType value) = 0;
		virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 value) = 0;
		virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvlaue, NOU::float32 yvalue) = 0;
		virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec2 &vec) = 0;
		virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue) = 0;
		virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec3 &vec) = 0;
		virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue, NOU::float32 wvalue) = 0;
		virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec4 &vec) = 0;
		virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat2 &mat) = 0;
		virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat3 &mat) = 0;
		virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat4 &mat) = 0;
		virtual NOU::boolean EnableLightning() = 0;
		virtual NOU::boolean DisableLightning() = 0;
	};
}
#endif
