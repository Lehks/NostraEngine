#ifndef NOE_MATSYS_MATERIAL_HPP
#define NOE_MATSYS_MATERIAL_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"


namespace NOE::NOE_MATSYS
{
	class Material
	{
	private:
		/**
		\brief A Program that creates the shader.
		*/
		Program *m_shader;

		/**
		\brief A function to call the createShader() method.

		\detail This method should be called in the constructor if there is a shader given as well as in loadMaterial().
		*/
		virtual NOU::boolean createShader();
	public:
		/**
		\brief A default destructor.
		*/
		virtual ~Material() = default;

		/**
		\brief A Method to bin the shader of the material to the corresponding program.
		*/
		NOU::boolean bindShader();

		/**
		\brief A Method to save a material.
		*/
		NOU::boolean saveMaterial();

		/**
		\brief A Method to load a material.
		*/
		NOU::boolean loadMaterial();
	}
}
#endif