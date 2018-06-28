#ifndef NOU_CORE_CONFIGURATION_SOURCE_FACTORY_HPP
#define NOU_CORE_CONFIGURATION_SOURCE_FACTORY_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/configuration_mngt/ConfigurationSource.hpp"

/**
\file    core/configuration_mngt/ConfigurationSource.hpp
\author  Lukas Reichmann
\version 1.0.0
\since   0.0.1

\brief A file that contains the base class of any configuration source factory in the configuration 
       management system.
*/

namespace NOE::NOE_CORE
{
	/**
	\brief A class that is used to construct child classes of the class ConfigurationSource. See the class 
	documentation of ConfigurationManager for further details.
	*/
	class ConfigurationSourceFactory
	{
	protected:
		/**
		\tparam T    The child class type of ConfigurationSource.
		\tparam ARGS The types of the parameters that will be passed to the constructor of \p T.

		\param args The parameters that will be passed to the constructor of \p T.

		\return A pointer to the allocated object.

		\brief Dynamically allocates and constructs an instance of \p T.

		\details
		Dynamically allocates and constructs an instance of \p T. This function should always be used to
		allocate instances of child classes of ConfigurationSource.
		*/
		template<typename T, typename... ARGS>
		static ConfigurationSource* allocateSource(ARGS&&... args);

	public:
		virtual ~ConfigurationSourceFactory() = default;

		/**
		\param source A pointer to the instance to deallocate.

		\brief Deallocates the passed ConfigurationSource.

		\details
		Deallocates the passed ConfigurationSource. This function is the opposite to allocateSource() and it
		is always able to deallocate objects that were allocated with that function. 
		This function is used by the configuration manager to deallocate configuration sources.
		*/
		NOU_FUNC static void deallocateSource(ConfigurationSource *source);

		/**
		\return The file extension as a string.

		\brief Returns the file extension that the configuration source that is constructed by this factory
		       is associated with.
		*/
		virtual const NOU::NOU_DAT_ALG::StringView8& getAssociatedExtension() const = 0;

		/**
		\param path The path to the configuration source file that should be constructed.

		\return A pointer to the constructed instance.

		\brief Constructs a new instance to the child class of ConfigurationSource that associated with this 
		       factory.

		\details
		Constructs a new instance to the child class of ConfigurationSource that associated with this factory.

		This method is <b>not</b> supposed to call ConfigurationSource::initialize() or any other member 
		function that the constructor. This is later done by the configuration manger itself.
		*/
		virtual ConfigurationSource* build(const NOU::NOU_FILE_MNGT::Path &path) = 0;
	};

	template<typename T, typename... ARGS>
	ConfigurationSource* ConfigurationSourceFactory::allocateSource(ARGS&&... args)
	{
		static_assert(NOU::NOU_CORE::IsBaseOf<ConfigurationSource, T>::value);
	
		return new T(NOU::NOU_CORE::forward<ARGS>(args)...);
	}
}

#endif