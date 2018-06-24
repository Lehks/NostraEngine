#ifndef NOE_MATSYS_MATERIAL_HPP
#define NOE_MATSYS_MATERIAL_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/NostraEngine.hpp"
#include "nostraengine/material_system/Program.hpp"

namespace NOE::NOE_MATSYS
{
	class NOU_CLASS Material
	{
	private:
		/**
		\brief A Program that creates the shader.
		*/
		Program m_shader;

		/**
		\brief A boolean to check if the shader is already compiled or not.
		*/
		NOU::boolean alreadyCompiled;

		/**
		\brief A function to call the createShader() method.

		\detail This method should be called in the constructor if there is a shader given as well as in loadMaterial().
		*/
		virtual NOU::boolean compileMaterial() = 0;
	public:
		/**
		\brief A default destructor.
		*/
		virtual ~Material() = default;

		/**
		\brief A Method to bin the material to the corresponding program.
		*/
		virtual NOU::boolean bindMaterial() = 0;

		/**
		\brief A Method to save a material.
		*/
		virtual NOU::boolean saveMaterial() = 0;

		/**
		\brief A Method to load a material.
		*/
		virtual NOU::boolean loadMaterial() = 0;
	}
}
#endif