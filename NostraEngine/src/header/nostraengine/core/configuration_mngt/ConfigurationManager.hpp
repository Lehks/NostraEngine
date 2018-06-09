#ifndef NOU_CORE_CONFIGURATION_MANAGER_HPP
#define NOU_CORE_CONFIGURATION_MANAGER_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/Initializable.hpp"
#include "nostraengine/core/configuration_mngt/ConfigurationSource.hpp"
#include "nostraengine/core/configuration_mngt/ConfigurationSourceFactory.hpp"

/**
\file    core/configuration_mngt/ConfigurationManager.hpp
\author  Lukas Reichmann
\version 1.0.0
\since   0.0.1

\brief A file that contains central class of the configuration management.
*/

namespace NOE::NOE_CORE
{
	/**
	\brief The central class of the configuration management.
	*/
	class NOU_CLASS ConfigurationManager final : public Initializable
	{
	public:
		
		enum class LoadMode
		{
			LOAD_ON_INITIALIZE,
			LOAD_ON_DEMAND
		};

		/**
		\brief The name of this initializable. Returned by getName().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 INITIALIZABLE_NAME;

		/**
		\brief The load mode used by default.
		*/
		static const LoadMode DEFAULT_LOAD_MODE;

	private:
		/**
		\brief A bundle of data that is always stored with a configuration source.
		*/
		struct ConfigurationSourceData
		{
			/**
			\brief The configuration source.
			*/
			ConfigurationSource *m_sourcePtr;

			/**
			\brief The path to the source.
			*/
			NOU::NOU_FILE_MNGT::Path m_path;

			/**
			\brief The factory that was used to construct the source.
			*/
			ConfigurationSourceFactory *m_factory;

			/**
			\brief True, if the source is already initialized, false if not.
			*/
			NOU::boolean m_isInitialized;
		};

		/**
		\brief The single configuration sources, unsorted.
		*/
		NOU::NOU_DAT_ALG::Vector<ConfigurationSourceData> m_data;

		/**
		\brief Maps the name of a configuration source to the actual source. For faster and easier access.
		*/
		NOU::NOU_DAT_ALG::HashMap <NOU::NOU_DAT_ALG::String8, ConfigurationSourceData*> m_nameDataMap;

		/**
		\brief The mode that is used to load entires.
		*/
		LoadMode m_loadMode;

		/**
		\brief True, if initialize() was called false if not. Independent from success.
		*/
		NOU::boolean m_wasInitCalled;

		ConfigurationManager();
		ConfigurationManager(const ConfigurationManager&) = default;

		/**
		\brief Fills the map m_nameDataMap and the vector m_data.
		*/
		void loadPluginList();

	public:
		/**
		\return The singleton-instance of this class.

		\brief Returns the singleton-instance of this class.
		*/
		static ConfigurationManager& get();

		/**
		\return See detailed section.

		\brief Initializes the configuration management.

		\details
		Initializes the configuration management.

		At this point, this function will always a list of all available plugins. Also, if the load mode 
		LOAD_ON_INITIALIZE is active, all of the configuration sources will also be initialized.

		The possible return values are:
		- SUCCESS: No errors were found.
		- WARNING: 
		    1. One or more configuration sources could not be initialized (this can only be the cause if the 
			   load mode LOAD_ON_INITIALIZE is active). 
			2. There are multiple, successfully loaded, configuration sources with the same name.
		- ERROR: Currently not possible.
		*/
		virtual Initializable::ExitCode initialize() override;

		/**
		\brief Terminates the configuration management by terminating all initialized configuration sources.
		*/
		virtual void terminate() override;

		/**
		\return The name of this initializable.

		\brief Returns the name of this initializable.
		*/
		virtual const NOU::NOU_DAT_ALG::StringView8& getName() const override;

		/**
		\brief Flushes all configuration sources by calling ConfigurationSource::flush() for each source.
		*/
		void flush();

		/**
		\return The currently activated load mode.

		\brief Returns the currently activated load mode.
		*/
		LoadMode getLoadMode() const;

		/**
		\param loadMode The mode to set.

		\brief Sets the load mode. This function has no effect after the instance has been initialized.
		*/
		void setLoadMode(LoadMode loadMode);
	};
}

#endif