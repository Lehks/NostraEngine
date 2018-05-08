#ifndef NOE_CORE_RESOURCE_LOADER_HPP
#define NOE_CORE_RESOURCE_LOADER_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/utility/SQLite.hpp"

/**
\author  Lukas Reichmann
\version 1.0.0
\since   0.0.1

\brief A file that contains the entire resource management system of the Nostra Engine.
*/

namespace NOE::NOE_CORE
{
	/**
	\brief A class that can be used to read the meta data of a single resource. 
	*/
	class NOU_CLASS ResourceMetadata
	{
	public:

		/**
		\brief The type of a resource ID.
		*/
		using ID = NOU::int32;

		/**
		\brief The type of a resource type.
		*/
		using ResourceType = NOU::NOU_DAT_ALG::String8;

		/**
		\brief An ID that is invalid. An ID with this type must never be stored in a database.
		*/
		static constexpr ID INVALID_ID = 0;

		/**
		\brief A generic SQL command that gathers the value of an attribute of an object with a specified ID. 
		       The attribute's name and the object's ID can be modified.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_GENERIC;

		/**
		\brief The name of the "type" attribute in the Resources database.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_TYPE_NAME;

		/**
		\brief The name of the "path" attribute in the Resources database.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_PATH_NAME;

		/**
		\brief The name of the "cached" attribute in the Resources database.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_CACHED_PATH_NAME;

		/**
		\brief A SQL statement that is able to check whether a resource with a specified ID exists. (Or to be
		more precise, the statement returns the amount of resources with the specified ID, which will either 
		be one or zero).
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_EXISTS_RESOURCE;

	private:
		/**
		\brief The ID of the resource.
		*/
		ID m_id;

		/**
		\param attribute The name of the attribute to get the value from.

		\return The value of the attribute.

		\brief Queries the value of the attribute \p attribute of the resource that is associated with this
		       meta data.
		*/
		NOU::NOU_DAT_ALG::String8 getAttribute(const NOU::NOU_DAT_ALG::StringView8 &attribute) const;

	public:
		/**
		\param id The ID.

		\brief Constructs a new instance and initialized the member attributes with the passed ID.

		\note
		If the passed ID does not exist in the database, the ID will be set to INVALID_ID. If a resource with
		the original ID is created afterwards, the instances of this class that were before that will NOT be
		updated.
		*/
		ResourceMetadata(ID id = INVALID_ID);

		/**
		\return The ID of the resource.

		\brief Returns the ID of the resource.
		*/
		ID getID() const;

		/**
		\return The type of the resource.

		\brief Returns the type of a resource.
		*/
		ResourceType getType() const;

		/**
		\return The path to the source file of the resource.

		\brief Returns the path to the source file of the resource.
		*/
		NOU::NOU_FILE_MNGT::Path getPath() const;

		/**
		\return True, if the resource is cached and false if not.

		\brief Returns whether the resource is cached or not.
		*/
		NOU::boolean isCached() const;

		/**
		\return The path the cache file. 

		\brief Returns the path to the cache file.

		\warning 
		The result of this method is only valid if <tt>isCached()</tt> returns true.
		*/
		NOU::NOU_FILE_MNGT::Path getCachePath() const;

		/**
		\return True, if the meta data is valid, false if not.

		\brief Returns whether the meta data is valid or not.
		*/
		NOU::boolean isValid() const;

		/**
		\return isValid()

		\brief Same as isValid()
		*/
		operator NOU::boolean () const;
	};

	class Resource
	{
	private:
		/**
		\brief The ID of the resource.
		*/
		ResourceMetadata m_metadata;

		/**
		\brief The name of the loader that this resource was loaded with.

		\details
		The name of the loader that this resource was loaded with. This is stored in the resource loader 
		itself and this member only references that name in the resource loader.
		*/
		const NOU::NOU_DAT_ALG::StringView8 &m_name;

	public:
		/**
		\param id   The ID of the resource.
		\param name The name of the loader that this resource was loaded with.

		\brief Constructs a new instance.
		*/
		Resource(ResourceMetadata::ID id, const NOU::NOU_DAT_ALG::StringView8& name);

		/**
		\return The meta data of the resource.

		\brief Returns the meta data of the resource.
		*/
		const ResourceMetadata& getMetadata() const;
	
		/**
		\return The name of the resource loader that this resource was loaded with.

		\brief Returns the name of the resource loader that this resource was loaded with.

		\details
		Returns the name of the resource loader that this resource was loaded with. Since it is a requirement
		to a resource loader that it must be able to store a resource that it loaded, it is always possible to
		store the resource with this loader (unless another error occurs, e.g. the process does not have the
		permission to write the source file of the resource).
		*/
		const NOU::NOU_DAT_ALG::StringView8& getLoaderName() const;

		/**
		\return True, if the resource was successfully stored, false if not.

		\brief Stores the resource using the loader that it was loaded with.

		\details
		Stores the resource using the loader that it was loaded with. Calling this method is similar to 
		\code{.cpp}
		ResourceManager::get().getLoader(this->getLoaderName()).store(this->getMetadata().getID())
		\endcode
		*/
		NOU::boolean store();

		/**
		\param enableCache If true, caching will be enables for this resource, if false, caching will be 
		                   disabled.
		\param path        If \p enableCache is true, this will be the path to the cache file, otherwise the
		                   parameter will be ignored.

		\brief Enables or disables caching for this resource.

		\details
		Stores the resource using the loader that it was loaded with. Calling this method is similar to 
		\code{.cpp}
		ResourceManager::get().cache(this->getMetadata().getID(), enableCache, path)
		\endcode

		Since this method calls ResourceManager::cache(), the same errors can occur in this method.
		*/
		NOU::boolean cache(NOU::boolean enableCache = true, const NOU::NOU_FILE_MNGT::Path &path = "./");
		
		/**
		\brief Deletes the cache file of the resource.

		\details
		Deletes the cache file of the resource. This can be used to force to regenerate a cache.

		Calling this method is similar to
		\code{.cpp}
		ResourceManager::get().deleteCache(this->getMetadata().getID())
		\endcode

		\note
		If the resource is not cached, this method will not do anything.
		*/
		void deleteCache();
	};

	class NOU_CLASS ResourceLoader
	{
	private:
		/**
		\brief The name of the loader.
		*/
		NOU::NOU_DAT_ALG::String8 m_name;

		/**
		\brief True, if the loader should work with caches, false if not.
		*/
		NOU::boolean  m_enableCaching;

	protected:
		/**
		\param resource The resource to store.
		\param path     The path to store the resource to.

		\return True, if the resource was stored successfully, false if not.

		\brief Stores the passed resource to its source (and not to a cache).

		\details
		Stores the passed resource to its source (and not to a cache). This method is defined by an actual 
		loader (and not this abstract parent class) and will be called by store() when a resource should be
		stored to its actual source file.
		*/
		virtual NOU::boolean storeImpl(Resource *resource, const NOU::NOU_FILE_MNGT::Path& path) = 0;

		/**
		\param resource The resource to cache.
		\param path     The path to store the resource to.

		\return True, if the resource was cached successfully, false if not.

		\brief Stores the passed resource to its cache (and not to a cache).

		\details
		Stores the passed resource to its cache. This method is defined by an actual loader (and not this 
		abstract parent class) and will be called by store() when a resource should cached. This method will 
		only be called if a resource is stored that has caching enabled.
		*/
		virtual NOU::boolean storeCacheImpl(Resource *resource, const NOU::NOU_FILE_MNGT::Path& path) = 0;

		/**
		\param metaData The meta data of the resource to load.
		\param path     The path to the source of the resource to load.

		\return The loaded resource if it could be loaded, or \p nullptr if it could not be.

		\brief Loads the resource with the passed meta data from the passed file (which is its source file).

		\details
		Loads the resource with the passed meta data from the passed file. This method is defined by an 
		actual loader (and not this abstract parent class) and will be called by load() when a resource should
		be from its actual source file.
		*/
		virtual Resource* loadImpl(const ResourceMetadata &metaData, 
			const NOU::NOU_FILE_MNGT::Path& path) = 0;

		/**
		\param metaData The meta data of the resource to load.
		\param path     The path to the cache of the resource to load.

		\return The loaded resource if it could be loaded, or \p nullptr if it could not be.

		\brief Loads the resource with the passed meta data from the passed file (which is its cache file).

		\details
		Loads the resource with the passed meta data from the passed file. This method is defined by an
		actual loader (and not this abstract parent class) and will be called by load() when a resource should
		be from its cache file.
		*/
		virtual Resource* loadCacheImpl(const ResourceMetadata &metaData, 
			const NOU::NOU_FILE_MNGT::Path& path) = 0;

	public:
		/**
		\param name The name of the loader.

		\brief Constructs a new resource loader with the passed name.
		*/
		ResourceLoader(const NOU::NOU_DAT_ALG::String8 &name);
		
		ResourceLoader(const ResourceLoader &) = delete;
		ResourceLoader(ResourceLoader &&) = delete;

		/**
		\return The name of the loader.

		\brief Returns the name of this loader.

		\note
		It required for a resource loader class that all instances of that class share the same name.
		*/
		const NOU::NOU_DAT_ALG::StringView8& getName() const;

		/**
		\param enable If true, caching will be enabled, if false, caching will be disabled.

		\brief Enables or disables caching for that loader.

		\details
		Enables or disables caching for that loader. This method allows it, to overwrite a resource's cache 
		setting. By disabling caching for a loader, the loader will never load from or store to a cache - even
		if caching is enabled for a certain resource. However, it is not possible to make a resource loader 
		cache a resource if that resource should not be cached.

		For simpler understanding, here is a chart that shows when a resource will be stored to or loader from
		a cache:

		Resource Caching | Loader caching | Will be cached?
		---------------- | -------------- | ---------------
		No               | No             | No
		Yes              | No             | No
		No               | Yes            | No
		Yes              | Yes            | Yes

		By default, caching is enabled for a loader (but this may be overwritten by the resource loader's 
		constructor).
		*/
		void enableCaching(NOU::boolean enable);

		/**
		\return Whether caching is enabled or disabled for this resource loader.

		\brief Returns whether caching is enabled or disabled for this resource loader.
		*/
		NOU::boolean isCachingEnabled();

		/**
		\param id The ID of the resource to load.

		\return A pointer to the loaded resource, or \p nullptr if the loading failed.

		\brief Loads and returns the resource with the passed ID.

		\note
		It is only valid to load a resource from a loader when isValidResource() returns true.

		\note
		A resource that has been loaded, needs to be closed with close() after it is not used anymore.
		*/
		Resource* load(ResourceMetadata::ID id);

		/**
		\param resource The resource to store.

		\return True, if storing was successful and false if not.

		\brief Stores the passed resource.

		\note
		It is only valid to store a resource using a loader when isValidResource() returns true.
		*/
		NOU::boolean store(Resource *resource);

		/**
		\param resource The resource to close.

		\brief Closes a resource. If the resource needs to be stored, this has to be done before closing it.

		\details
		Closes a resource. If the resource needs to be stored, this has to be done before closing it. This is
		required, because internally, the resources are dynamically allocated and therefore have to be deleted
		again.

		\note
		After a resource is closed, it is not usable anymore.
		*/
		void close(Resource *resource);

		/**
		\return True, if the resource is valid, false if not.

		\brief Returns whether the loader can load and store the resource with the passed ID. If the resource
		       does not exist, false is returned.
		*/
		virtual NOU::boolean isResourceValid(typename ResourceMetadata::ID id) const = 0;
	};

	class NOU_CLASS ResourceManager final
	{
	private:
		/**
		\brief The default path to the database file.
		*/
		static NOU::NOU_FILE_MNGT::Path DATABASE_PATH;

		/**
		\brief The SQL code to query all IDs in the database. This is used by listMetadata().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_LIST_IDS;

		/**
		\brief The SQL code to add a resource to the database. This is used by addResource().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_ADD_RESOURCE;

		/**
		\brief The SQL code to remove a resource from the database. This is used by removeResource().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_REMOVE;

		/**
		\brief The SQL code to update the cache state of a resource. This is used by cache().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_UPDATE_CACHE;

		/**
		\brief The SQL code to create the resources database if it does not exist yet. This is used by 
		       initialize().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_CREATE_TABLE;

		/**
		\brief The database that is used by the resource manager.
		*/
		NOE::NOE_UTILITY::sqlite::Database m_database;

		/**
		\brief A list of the loaders that were added to the manager.
		*/
		NOU::NOU_DAT_ALG::HashMap<NOU::NOU_DAT_ALG::String8, ResourceLoader*> m_loaders;

		/**
		\tparam T    The type resource loader to add. This must be a child class of ResourceLoader.
		\tparam ARGS The types of the parameters that will be passed to the constructor of the resource
		loader.

		\param args The parameters that will be passed to the constructor of the resource loader.

		\return The constructed loader.

		\brief Allocates a new ResourceLoader of the type T.
		*/
		template<typename T, typename ...ARGS>
		static ResourceLoader* alloatecResourceLoader(ARGS&&... args);

		/**
		\param loader The loader to deallocate

		\brief Deallocates the passed loader.
		*/
		static void deallocateResourceLoader(ResourceLoader *loader);

	public:
		/**
		\param databasePath The path to the database file.

		\brief Constructs a new instance that uses the passed file as database.
		*/
		//no default argument possible, DATABASE_PATH is not defined yet
		explicit ResourceManager(const NOU::NOU_FILE_MNGT::Path &databasePath);

		/**
		\brief Constructs a new instance that uses the file with the path \p DATABASE_PATH as database.
		*/
		ResourceManager();

		/**
		\tparam ARGS The types of the arguments that will be passed to the constructor of \p T.

		\param args The arguments that will be passed to the constructor of \p T.

		\return A pointer to the allocated resource.

		\brief Allocates a new instance of \p T. \p T must be a child of nostra::engine::core::Resource.
		*/
		template<typename T, typename... ARGS>
		Resource* allocateResource(ARGS&&... args);

		/**
		\param resource The resource to deallocate.

		\brief Deallocates a resource that was previously allocated with allocateResource().
		*/
		void deallocateResource(Resource *resource);

		/**
		\return The static instance of the resource manager.

		\brief Returns the instance of the resource manager.

		\details
		Returns the instance of the resource manager. This method also stores the instance as a static local variable.
		*/
		static ResourceManager& get();

		/**
		\tparam T    The type resource loader to add. This must be a child class of ResourceLoader.
		\tparam ARGS The types of the parameters that will be passed to the constructor of the resource 
		             loader.

		\param args The parameters that will be passed to the constructor of the resource loader.

		\return True, if the loader was added and false if it was not (in that case, a loader with the same
		        name already exists). 

		\brief Adds a new ResourceLoader.
		
		\details 
		Adds a new ResourceLoader. It is only possible to get a ResourceLoader using getLoader() after it has 
		been added using this method.

		\note
		The loader names need to be unique and there can never be two loaders added to the manager with the
		same name at the same time.
		*/
		template<typename T, typename ...ARGS>
		NOU::boolean addLoader(ARGS&&... args);

		/**
		\param name The name of the resource loader to get.

		\return The loader with the passed name, or \p nullptr if there is no such loader.

		\brief Returns the loader with the passed name.
		*/
		ResourceLoader* getLoader(const NOU::NOU_DAT_ALG::StringView8 &name);

		/**
		\brief Deletes the cache files of all resources.
		*/
		void deleteCaches();

		/**
		\param path        The path to the resource. It is not allowed to have different resources that have 
		                   the same path.
		\param type        The type of the resource.
		\param enableCache Enables (true) or disables (false) the caching.
		\param cachePath   The path to the cache of the resource. If \p enableCache is false, this parameter
		                   will be ignored.

		\return The ID of the resource that was added, or ResourceManager::INVALID_RESOURCE_ID if an error 
		        occurred (check the error handler for further information about the error).

		\brief Adds a new resource to the resource database.

		\details
		Adds a new resource to the resource database. On failure, ResourceManager::INVALID_RESOURCE_ID is 
		returned and an error is pushed to the error handler. The possible errors are: 
		- ErrorCodes::RESOURCE_ALREADY_PRESENT: A resource with the same path already exists.
		- ErrorCodes::INVALID_PATH: The path does not lead to a file (either the path the resource or the path
		  to the cache is invalid).
		(Note that this list does not include errors that may be pushed be e.g. an underlying container)

		\note
		Since the resource manager stores what resources are added to it in a database that is persistent over
		multiple executions of the engine, this method does not need to be called each time that the engine
		is being executed.

		\note
		As long as the resource is not removed from the database, the ID of the resources will stay the same 
		over multiple executions (if a resource is removed and then added again, the ID may, and most likely 
		will, change).
		*/
		typename ResourceMetadata::ID addResource(const NOU::NOU_FILE_MNGT::Path &path, 
			const typename ResourceMetadata::ResourceType &type, NOU::boolean enableCache = false,
			const NOU::NOU_FILE_MNGT::Path &cachePath = "./");

		/**
		\param id The ID of the resource that should be removed.

		\return True, if the resource was removed, false if not. The operation fails if there is no resource 
		        with the passed ID.

		\brief Removes a resource from the resource database.

		\note
		This method does not delete the files that were associated with that resource (that is the source and
		a possible cache file).
		*/
		NOU::boolean removeResource(typename ResourceMetadata::ID id);

		/**
		\return The amount of resources that were removed.

		\brief Removes all resources from the database whose source file does not exist.

		\note
		This method behaves as if removeResource() was called for each resource.
		*/
		NOU::uint32 cleanupResources();

		/**
		\param id          The ID of the resource.
		\param enableCache Enables (true) or disables (false) the caching.
		\param cachePath   The path to the cache of the resource. If \p enableCache is false, this parameter
		                   will be ignored.

		\return True, if the operation was successful and false if not. If the operation was not successful, 
		        an error will be pushed to the error handler.

		\brief Enables or disables caching for a resource.

		\details
		Enables or disables caching for a resource. On failure, ResourceManager::INVALID_RESOURCE_ID is 
		returned and an error is pushed to the error handler. The possible errors are: 
		- ErrorCodes::INVALID_PATH: The path does not lead to a file (either the path the resource or the path
		  to the cache is invalid).
		- ErrorCodes::RESOURCE_NOT_PRESENT: A resource with the passed ID does not exist.
		(Note that this list does not include errors that may be pushed be e.g. an underlying container)
		*/
		NOU::boolean cache(typename ResourceMetadata::ID id, NOU::boolean enableCache,
			const NOU::NOU_FILE_MNGT::Path &path = "./");

		/**
		\param id The ID of the resource.

		\return True, if the resource was removed, false if not. The operation fails if there is no resource
		with the passed ID.

		\brief Deletes the cache file of the resource with the passed ID.

		\details
		Deletes the cache file of the resource with the passed ID. This can be used to force to regenerate a
		cache.

		\note
		If the resource exists but is not cached, this method will not do anything (but it will still return 
		true).
		*/
		NOU::boolean deleteCache(typename ResourceMetadata::ID id);

		/**
		\return A list that contains the meta data of all resources in the database.

		\brief Returns a list that contains the meta data of all resources in the database.
		*/
		NOU::NOU_DAT_ALG::Vector<ResourceMetadata> listMetadata();

		/**
		\param id The ID of the resource.

		\return The meta data of the resource with the passed ID, or \p nullptr if the resource does not 
		        exist.

		\brief Returns the meta data of a single resource.
		*/
		ResourceMetadata getMetadata(typename ResourceMetadata::ID id) const;
	
		void initalize();

		void shutdown();

		/**
		\return The underlying database.

		\brief Returns the underlying database.
		*/
		NOE::NOE_UTILITY::sqlite::Database& getUnderlying();
	};

	template<typename T, typename... ARGS>
	Resource* ResourceManager::allocateResource(ARGS&&... args)
	{
		static_assert(NOU::NOU_CORE::IsBaseOf<Resource, T>::value);

		return new T(NOU::NOU_CORE::forward<ARGS>(args)...);
	}

	template<typename T, typename ...ARGS>
	static ResourceLoader* ResourceManager::alloatecResourceLoader(ARGS&&... args)
	{
		static_assert(NOU::NOU_CORE::IsBaseOf<ResourceLoader, T>::value);

		return new T(NOU_CORE::forward<ARGS>(args)...);
	}

	template<typename T, typename ...ARGS>
	NOU::boolean ResourceManager::addLoader(ARGS&&... args)
	{
		ResourceLoader *loader = allocResourceLoader(NOU_CORE::forward<ARGS>(args)...);

		if (!m_loaders.containsKey(loader->getName()))
		{
			m_loaders.map(loader->getName(), loader);     
			return true;
		}
		else
		{
			return false;
		}
	}

}

#endif