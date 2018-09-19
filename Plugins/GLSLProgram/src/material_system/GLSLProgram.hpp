#ifndef PLUGIN_GLSL_PROGRAM_HPP
#define PLUGIN_GLSL_PROGRAM_HPP

#include "nostraengine/NostraEngine.hpp"
#include "nostrautils/NostraUtils.hpp"

#include "../../../GLAD/include/glad/glad.h"

/**
\file material_system/GLSLProgram.hpp

\author  Dennis Franz
\version 0.0.1
\since   0.0.1

\brief A file that provides the functionality for the shader accsessability.
*/
namespace GLSLProgramPlugin
{
	class GLSLProgram : public NOE::NOE_MATSYS::Program
	{
    private:
	/**
	 * brief To identify the Program.
	 */
		NOU::sizeType m_ID;
	/**
	 * brief To identify the vertex shader.
	 */
		NOU::sizeType m_vertexShaderId;
	/**
	 * brief To identify the fragment shader.
	 */
		NOU::sizeType m_fragmentShaderId;	
	/**
	 * brief To identify the geometry shader.
	 */
		NOU::sizeType m_geometryShaderId;

	/**
	 * brief Holds the vertex shader code.
	 */
		NOU::NOU_DAT_ALG::String8 m_vertexShader;
	/**
	 * brief Holds the frgament shader code.
	 */
		NOU::NOU_DAT_ALG::String8 m_fragmentShader;
	/**
	 * brief Holds the geometry shader code.
	 */
		NOU::NOU_DAT_ALG::String8 m_geometryShader;

	/**
	 * brief Hash map dor storing the uniform names as a key and theier locations.
	 */
		NOU::NOU_DAT_ALG::HashMap<NOU::NOU_DAT_ALG::String8, NOU::sizeType> m_uniforms;

	/**
	 * return 	NOU::boolean.
	 * 
	 * brief Method to link the different shader programs.
	 */
		NOE_PLUGIN_FUNC virtual NOU::boolean linkShader() override;
	/**
	 * return	NOU::boolean.
	 * 
	 * brief Method to create the vertex shader.
	 */
		NOE_PLUGIN_FUNC virtual NOU::boolean createVertexShader() override;
	/**
	 * return	NOU::boolean.
	 * 
	 * brief Method to create the fragment shader.
	 */
		NOE_PLUGIN_FUNC virtual NOU::boolean createFragmetShader() override;
	/**
	 * return	NOU::boolean.
	 * 
	 * brief Method to create the geometry shader.
	 */
		NOE_PLUGIN_FUNC virtual NOU::boolean createGeometryShader() override;

	public:
	/**
	 * param	NOU::sizeType mapSize, to set a specific hash map size.
	 * 
	 * brief A constructor for the standard GLSLProgram.
	 */
		NOE_PLUGIN_FUNC GLSLProgram(NOU::sizeType mapSize = 100);
	/**	 
	 * brief Default constructor.
	 */
		NOE_PLUGIN_FUNC virtual ~GLSLProgram() = default;
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &shadersource, the path to the shader source.
	 * 
	 * return	NOU::boolean.
	 * 
	 * brief A Function for loading the shader in the m_vertexshader variable.
	 */
		NOE_PLUGIN_FUNC NOU::boolean loadVertexShader(const NOU::NOU_DAT_ALG::String8 &shaderSource);
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &shadersource, the path to the shader source.
	 * 
	 * return	NOU::boolean.
	 * 
	 * brief A Function for loading the shader in the m_fragmentshader variable.
	 */
		NOE_PLUGIN_FUNC NOU::boolean loadFragmentShader(const NOU::NOU_DAT_ALG::String8 &shaderSource);
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &shadersource, the path to the shader source.
	 * 
	 * return	NOU::boolean.
	 * 
	 * brief A Function for loading the shader in the m_geometryshader variable.
	 */
		NOE_PLUGIN_FUNC NOU::boolean loadGeometryShader(const NOU::NOU_DAT_ALG::String8 &shaderSource);
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &vertexshadersource, the path to the vertx shader source.
	 * param	const NOU::NOU_DAT_ALG::String8 &fragmenthadersource, the path to the fragment shader source.
	 * param	const NOU::NOU_DAT_ALG::String8 &geometryshadersource, the path to the geometry shader source.
	 * 
	 * return	NOU::boolean.
	 * 
	 * brief This function creats the shader and calls the different loadfunction aswell as the creat and link methods.
	 */
		NOE_PLUGIN_FUNC virtual NOU::boolean createShader(const NOU::NOU_DAT_ALG::String8 &vertexShaderSource, const NOU::NOU_DAT_ALG::String8 &fragmentShaderSource, const NOU::NOU_DAT_ALG::String8 &geometryShaderSource = nullptr) override;
	/** 
	 * return	NOU::boolean.
	 * 
	 * brief Bind's the shader to the corresponding program.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean bind() override;
	/** 
	 * return	NOU::boolean.
	 * 
	 * brief Unbind's the shader from the corresponding program.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean unbind() override;
	/** 
	 * param	const NOU::NOU_DAT_ALG::String8 &name, the name of the uniform.
	 * 
	 * return	NOU::boolean.
	 * 
	 * brief This function creates the uniform with the given name and stores their <name,location> values in the map.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean createUniform(const NOU::NOU_DAT_ALG::String8 &name) override;
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &name, the name of the uniform.
	 * param	NOU::boolean value, the value that the uniform should get.
	 *  
	 * return	NOU::boolean.
	 * 
	 * brief Gives the value to the corresponding uniform location that is stored in the map to the corresponding name.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::boolean value)override;
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &name, the name of the uniform.
	 * param	NOU::sizeType value, the value that the uniform should get.
	 *  
	 * return	NOU::boolean.
	 * 
	 * brief Gives the value to the corresponding uniform location that is stored in the map to the corresponding name.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::sizeType value)override;
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &name, the name of the uniform.
	 * param	NOU::float32 value, the value that the uniform should get.
	 *  
	 * return	NOU::boolean.
	 * 
	 * brief Gives the value to the corresponding uniform location that is stored in the map to the corresponding name.
	 */		
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 value)override;
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &name, the name of the uniform.
	 * param	NOU::float32 xvalue, the x-value of the vector that the uniform should get.
	 * param	NOU::float32 yvalue, the y-value of the vector that the uniform should get.
	 *  
	 * return	NOU::boolean.
	 * 
	 * brief Gives the value to the corresponding uniform location that is stored in the map to the corresponding name.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue)override;
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &name, the name of the uniform.
	 * param	const NOU::NOU_MATH::Vec2 &vec, the value that the uniform should get.
	 *  
	 * return	NOU::boolean.
	 * 
	 * brief Gives the value to the corresponding uniform location that is stored in the map to the corresponding name.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec2 &vec)override;
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &name, the name of the uniform.
	 * param	NOU::float32 xvalue, the x-value of the vector that the uniform should get.
	 * param	NOU::float32 yvalue, the y-value of the vector that the uniform should get.
	 * param	NOU::float32 zvalue, the z-value of the vector that the uniform should get.
	 * 
	 * return	NOU::boolean.
	 * 
	 * brief Gives the value to the corresponding uniform location that is stored in the map to the corresponding name.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue)override;
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &name, the name of the uniform.
	 * param	const NOU::NOU_MATH::Vec3 &vec, the value that the uniform should get.
	 *  
	 * return	NOU::boolean.
	 * 
	 * brief Gives the value to the corresponding uniform location that is stored in the map to the corresponding name.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec3 &vec)override;
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &name, the name of the uniform.
	 * param	NOU::float32 xvalue, the x-value of the vector that the uniform should get.
	 * param	NOU::float32 yvalue, the y-value of the vector that the uniform should get.
	 * param	NOU::float32 zvalue, the z-value of the vector that the uniform should get.
	 * param	NOU::float32 wvalue, the w-value of the vector that the uniform should get.
	 * 
	 * return	NOU::boolean.
	 * 
	 * brief Gives the value to the corresponding uniform location that is stored in the map to the corresponding name.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue, NOU::float32 wvalue)override;
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &name, the name of the uniform.
	 * param	const NOU::NOU_MATH::Vec4 &vec, the value that the uniform should get.
	 *  
	 * return	NOU::boolean.
	 * 
	 * brief Gives the value to the corresponding uniform location that is stored in the map to the corresponding name.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec4 &vec)override;
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &name, the name of the uniform.
	 * param	const NOU::NOU_MATH::Mat2 &mat, the value that the uniform should get.
	 *  
	 * return	NOU::boolean.
	 * 
	 * brief Gives the value to the corresponding uniform location that is stored in the map to the corresponding name.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat2 &mat)override;
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &name, the name of the uniform.
	 * param	const NOU::NOU_MATH::Mat3 &mat, the value that the uniform should get.
	 *  
	 * return	NOU::boolean.
	 * 
	 * brief Gives the value to the corresponding uniform location that is stored in the map to the corresponding name.
	 */		
	    NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat3 &mat)override;
	/**
	 * param	const NOU::NOU_DAT_ALG::String8 &name, the name of the uniform.
	 * param	const NOU::NOU_MATH::Mat4 &mat, the value that the uniform should get.
	 *  
	 * return	NOU::boolean.
	 * 
	 * brief Gives the value to the corresponding uniform location that is stored in the map to the corresponding name.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat4 &mat)override;
	/**
	 * return	NOU::boolean.
	 * 
	 * brief This function enables lightning.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean enableLightning() override;
	/**
	 * return	NOU::boolean.
	 * 
	 * brief This function disables lightning.
	 */	
		NOE_PLUGIN_FUNC virtual NOU::boolean disableLightning() override;
	};
}
#endif
