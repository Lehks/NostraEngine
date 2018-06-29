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
	class ConfigurationManager final : public Initializable
	{
	public:
		
		/**
		\brief The load mode defines the point in time when configuration sources will be loaded.
		*/
		enum class LoadMode
		{
			/**
			\brief When this load mode is set, all of the configuration source will be initialized when the
			       configuration management is initialized.
			*/
			LOAD_ON_INITIALIZE,

			/**
			\brief When this load mode is set, each configuration source will be initialized when it is accessed for
			       the first time.
			*/
			LOAD_ON_DEMAND
		};

		/**
		\brief The name of this initializable. Returned by getName().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 INITIALIZABLE_NAME;

		/**
		\brief The priority of this initializable.
		*/
		static const NOU::uint32 INITIALIZABLE_PRIORITY;

		/**
		\brief The load mode used by default.
		*/
		static const LoadMode DEFAULT_LOAD_MODE;

		/**
		\brief The bucket count of m_factoryNameDataMap.
		*/
		static const NOU::sizeType DEFAULT_FACTORY_MAP_CAPACITY;

		/**
		\brief The bucket count of m_factoryNameDataMap.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 PATH_SEPARATOR;

		/**
		\brief The path to the configuration folder that is used by default.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 DEFAULT_CONFIGURATION_PATH;

	private:
		/**
		\brief A bundle of data that is always stored with a configuration source.
		*/
		struct ConfigurationSourceData final
		{
			/**
			\param ptr  The pointer to the configuration source. Will be deleted using 
			            NOU::NOU_DAT_ALG::defaultDeleter.
			\param path The path to the configuration source.

			\brief Constructs a new instance.
			*/
			NOU_FUNC ConfigurationSourceData(ConfigurationSource *ptr, const NOU::NOU_FILE_MNGT::Path &path);

			/**
			\brief The configuration source.
			*/
			NOU::NOU_MEM_MNGT::UniquePtr<ConfigurationSource> m_sourcePtr;           

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
		\brief The path that the configuration files will be loaded from.
		*/
		NOU::NOU_FILE_MNGT::Path m_loadPath;

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

		/**
		\brief Maps the name of a configuration source factories to the actual source.
		*/
		NOU::NOU_DAT_ALG::HashMap <NOU::NOU_DAT_ALG::String8, 
		                    NOU::NOU_MEM_MNGT::UniquePtr<ConfigurationSourceFactory>> m_factoryNameDataMap;

		ConfigurationManager();
		ConfigurationManager(const ConfigurationManager&) = delete;

		/**
		\return Returns the list of files that was created.

		\brief Returns a list of all of the configuration source files.
		*/
		NOU::NOU_DAT_ALG::Vector<NOU::NOU_FILE_MNGT::File> 
			createFileList(const NOU::NOU_FILE_MNGT::Path &path) const;

		/**
		\brief Fills the map m_nameDataMap and the vector m_data.
		*/
		NOU::boolean loadSourcesList();

		/**
		\brief Deletes all elements in m_factoryNameDataMap
		*/
		void destroyFactoryMap();

		/**
		\param fullyQualified  The fully qualified path to resolve.
		\param sourceName[out] After the function call, this will contain the name of the configuration 
		                       source.
		\param qualified[out]  After the function call, this will contain the qualified name of the entry.

		\brief Splits up a fully qualified name into the name of the configuration source and the qualified
		       path in that source.
		*/
		static void resolveFullyQualifiedPath(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified, 
			NOU::NOU_DAT_ALG::StringView8 *sourceName, NOU::NOU_DAT_ALG::StringView8 *qualified);

		/**
		\param sourceName The name of the configuration source to get.

		\return A pointer to the selected configuration source, or \p nullptr if the source does not exist.

		\brief Returns a pointer to the configuration source with the passed name.
		*/
		ConfigurationSource* getConfigurationSource(const NOU::NOU_DAT_ALG::StringView8 &sourceName);

	public:
		/**
		\return The singleton-instance of this class.

		\brief Returns the singleton-instance of this class.
		*/
		NOU_FUNC static ConfigurationManager& get();

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
		NOU_FUNC virtual Initializable::ExitCode initialize() override;

		/**
		\brief Terminates the configuration management by terminating all initialized configuration sources.
		*/
		NOU_FUNC virtual void terminate() override;

		/**
		\return The name of this initializable.

		\brief Returns the name of this initializable.
		*/
		NOU_FUNC virtual const NOU::NOU_DAT_ALG::StringView8& getName() const override;

		/**
		\brief Flushes all configuration sources by calling ConfigurationSource::flush() for each source.
		*/
		NOU_FUNC void flush();

		/**
		\return The currently activated load mode.

		\brief Returns the currently activated load mode.
		*/
		NOU_FUNC LoadMode getLoadMode() const;

		/**
		\param loadMode The mode to set.

		\brief Sets the load mode. This function has no effect after the instance has been initialized.
		*/
		NOU_FUNC void setLoadMode(LoadMode loadMode);

		/**
		\return The currently set load path.

		\brief Returns the currently set load path.
		*/
		const NOU::NOU_FILE_MNGT::Path& ConfigurationManager::getPath() const;

		/**
		\param path The path to set.

		\brief Sets path from where the configuration files will be loaded. This function has no effect after 
		       the instance has been initialized.
		*/
		void ConfigurationManager::setPath(const NOU::NOU_FILE_MNGT::Path &path);
		/**
		\tparam T    The child class type of ConfigurationSourceFactory.
		\tparam ARGS The types of the parameters that will be passed to the constructor of \p T.

		\param args The parameters that will be passed to the constructor of \p T.

		\brief Adds a new configuration source factory to the manager.
		*/
		template<typename T, typename... ARGS>
		void addSourceFactory(ARGS&&... args);

		/**
		\param fullyQualified The fully qualified path to the entry.

		\return The type of the entry with the passed fully qualified path. It will return 
		        ConfigurationSource::TypeID::INVALID if the entry does not exist (Note: it is also possible
				that the underlying configuration source instance returns that value).

		\brief Returns the type of an entry in a configuration source.

		\details
		Returns the type of an entry in a configuration source.

		This function is similar to getTypeOf(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC ConfigurationSource::TypeID getTypeOf(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified);

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.

		\return The type of the entry with the passed fully qualified path. It will return 
		        ConfigurationSource::TypeID::INVALID if the entry does not exist (Note: it is also possible
				that the underlying configuration source instance returns that value).

		\brief Returns the type of an entry in a configuration source.

		\details
		Returns the type of an entry in a configuration source.

		This function is similar to getTypeOf(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to do
		additional name-resolving.
		*/
		NOU_FUNC ConfigurationSource::TypeID getTypeOf(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified);

		/**
		\param fullyQualified The fully qualified path to the entry to check.

		\return True, if the entry exists, false if not. It will also return false if the entry does not exist
		        in the first place.

		\brief Returns whether an entry exists.

		\details
		Returns whether an entry exists.

		This function is similar to hasEntry(const NOU::NOU_DAT_ALG::StringView8&, const 
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving. 
		*/
		NOU_FUNC NOU::boolean hasEntry(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified);

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.

		\return True, if the entry exists, false if not. It will also return false if the entry does not exist
		        in the first place.

		\brief Returns whether an entry exists.

		\details
		Returns whether an entry exists.

		This function is similar to hasEntry(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to do
		additional name-resolving.
		*/
		NOU_FUNC NOU::boolean hasEntry(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified);

		/**
		\param fullyQualified The fully qualified path to the entry with the value to get.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		        exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getBoolean(const NOU::NOU_DAT_ALG::StringView8&, const 
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving. 
		*/
		NOU_FUNC NOU::boolean getBoolean(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const;

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getBoolean(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to 
		do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean getBoolean(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified) const;

		/**
		\param fullyQualified The fully qualified path to the entry with the value to get.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getString(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC NOU::NOU_DAT_ALG::String8 
			getString(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const;

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getString(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to
		do additional name-resolving.
		*/
		NOU_FUNC NOU::NOU_DAT_ALG::String8 getString(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified) const;

		/**
		\param fullyQualified The fully qualified path to the entry with the value to get.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getInt32(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC NOU::int32 getInt32(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const;

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getInt32(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to
		do additional name-resolving.
		*/
		NOU_FUNC NOU::int32 getInt32(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified) const;

		/**
		\param fullyQualified The fully qualified path to the entry with the value to get.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getInt64(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC NOU::int64 getInt64(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const;

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getInt64(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to
		do additional name-resolving.
		*/
		NOU_FUNC NOU::int64 getInt64(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified) const;

		/**
		\param fullyQualified The fully qualified path to the entry with the value to get.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getFloat32(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC NOU::float32 getFloat32(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const;

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getFloat32(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to
		do additional name-resolving.
		*/
		NOU_FUNC NOU::float32 getFloat32(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified) const;

		/**
		\param fullyQualified The fully qualified path to the entry with the value to get.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getFloat64(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC NOU::float64 getFloat64(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const;

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getFloat64(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to
		do additional name-resolving.
		*/
		NOU_FUNC NOU::float64 getFloat64(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified) const;

		/**
		\param fullyQualified The fully qualified path to the entry with the value to get.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getVoidPtr(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC void* getVoidPtr(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const;

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to getVoidPtr(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to
		do additional name-resolving.
		*/
		NOU_FUNC void* getVoidPtr(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified) const;


		/**
		\param fullyQualified The fully qualified path to the entry with the value to set.
		\param v              The value to set.

		\return True, if the value was successfully set, false if not.

		\brief Sets the value of the entry with the specified path.

		\details
		Sets the value of the entry with the specified path.

		This function is similar to setBoolean(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setBoolean(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified, NOU::boolean v);

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.
		\param v          The value to set.

		\return True, if the value was successfully set, false if not.

		\brief Sets the value of the entry with the specified path.

		\details
		Sets the value of the entry with the specified path.

		This function is similar to setBoolean(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to
		do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setBoolean(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::boolean v);

		/**
		\param fullyQualified The fully qualified path to the entry with the value to set.
		\param v              The value to set.

		\return True, if the value was successfully set, false if not.

		\brief Sets the value of the entry with the specified path.

		\details
		Sets the value of the entry with the specified path.

		This function is similar to setString(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setString(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified,
			NOU::NOU_DAT_ALG::String8 v);

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.
		\param v          The value to set.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to setString(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to
		do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setString(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::NOU_DAT_ALG::String8 v);

		/**
		\param fullyQualified The fully qualified path to the entry with the value to set.
		\param v              The value to set.

		\return True, if the value was successfully set, false if not.

		\brief Sets the value of the entry with the specified path.

		\details
		Sets the value of the entry with the specified path.

		This function is similar to setInt32(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setInt32(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified, NOU::int32 v);

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.
		\param v          The value to set.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to setInt32(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to
		do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setInt32(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::int32 v);

		/**
		\param fullyQualified The fully qualified path to the entry with the value to set.
		\param v              The value to set.

		\return True, if the value was successfully set, false if not.

		\brief Sets the value of the entry with the specified path.

		\details
		Sets the value of the entry with the specified path.

		This function is similar to setInt64(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setInt64(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified, NOU::int64 v);

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.
		\param v          The value to set.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to setInt64(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to
		do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setInt64(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::int64 v);

		/**
		\param fullyQualified The fully qualified path to the entry with the value to set.
		\param v              The value to set.

		\return True, if the value was successfully set, false if not.

		\brief Sets the value of the entry with the specified path.

		\details
		Sets the value of the entry with the specified path.

		This function is similar to setFloat32(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setFloat32(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified, NOU::float32 v);

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.
		\param v          The value to set.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to setFloat32(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to
		do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setFloat32(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::float32 v);

		/**
		\param fullyQualified The fully qualified path to the entry with the value to set.
		\param v              The value to set.

		\return True, if the value was successfully set, false if not.

		\brief Sets the value of the entry with the specified path.

		\details
		Sets the value of the entry with the specified path.

		This function is similar to setFloat64(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setFloat64(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified, NOU::float64 v);

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.
		\param v          The value to set.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to setFloat64(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to
		do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setFloat64(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::float64 v);

		/**
		\param fullyQualified The fully qualified path to the entry with the value to set.
		\param v              The value to set.

		\return True, if the value was successfully set, false if not.

		\brief Sets the value of the entry with the specified path.

		\details
		Sets the value of the entry with the specified path.

		This function is similar to setVoidPtr(const NOU::NOU_DAT_ALG::StringView8&, const
		NOU::NOU_DAT_ALG::StringView8&) but it has to do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setVoidPtr(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified, void *v);

		/**
		\param sourceName The name of the configuration source.
		\param qualified  The qualified path to the entry.
		\param v          The value to set.

		\return The value of the entry with the specified path, or an undefined value if the entry does not
		exist.

		\brief Returns the value of the entry with the specified path.

		\details
		Returns the value of the entry with the specified path.

		This function is similar to setVoidPtr(const NOU::NOU_DAT_ALG::StringView8&) but it does not have to
		do additional name-resolving.
		*/
		NOU_FUNC NOU::boolean setVoidPtr(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
			const NOU::NOU_DAT_ALG::StringView8 &qualified, void *v);
	};

	template<typename T, typename... ARGS>
	void ConfigurationManager::addSourceFactory(ARGS&&... args)
	{
		static_assert(NOU::NOU_CORE::IsBaseOf<ConfigurationSourceFactory, T>::value);

		NOU::NOU_MEM_MNGT::UniquePtr<ConfigurationSourceFactory> factory(
			new T(NOU::NOU_CORE::forward<ARGS>(args)...), NOU::NOU_MEM_MNGT::defaultDeleter);

		m_factoryNameDataMap.map(factory->getAssociatedExtension(), NOU::NOU_CORE::move(factory));
	}
}

#endif