#ifndef NOE_CORE_RESOURCE_LOADER_HPP
#define NOE_CORE_RESOURCE_LOADER_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOE::NOE_CORE
{
	class NOU_CLASS ResourceMetadata
	{
	public:

		/**
		\brief The type of a resource ID.
		*/
		using ResourceID = NOU::int32;

		/**
		\brief The type of a resource type.
		*/
		using ResourceType = NOU::NOU_DAT_ALG::String8;

	private:
		/**
		\brief The ID of the resource.
		*/
		ResourceID m_id;

		/**
		\brief The path to the source file of the resource.
		*/
		NOU::NOU_FILE_MNGT::Path m_path;

		/**
		\brief The ID of the resource.
		*/
		ResourceType m_type;

		/**
		\brief True, if the resource is cached, false if not.
		*/
		NOU::boolean m_isCached;

		/**
		\brief The ID of the resource.
		*/
		NOU::NOU_FILE_MNGT::Path m_cachePath;

	public:
		/**
		\param id          The ID.
		\param type        The type.
		\param path        The path.
		\param enableCache The cache state.
		\param cachePath   The cache path.

		\brief Constructs a new instance and initialized the member attributes with the passed parameters.
		*/
		ResourceMetadata(ResourceID id, const NOU::NOU_FILE_MNGT::Path &path, const ResourceType &type,
			NOU::boolean isCached, const NOU::NOU_FILE_MNGT::Path &cachePath);

		/**
		\return The ID of the resource.

		\brief Returns the ID of the resource.
		*/
		ResourceID getID() const;

		/**
		\return The type of the resource.

		\brief Returns the type of a resource.
		*/
		const ResourceType& getType() const;

		/**
		\return The path to the source file of the resource.

		\brief Returns the path to the source file of the resource.
		*/
		const NOU::NOU_FILE_MNGT::Path& getPath() const;

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
		const NOU::NOU_FILE_MNGT::Path& getCachePath() const;
	};

	class Resource
	{
	private:
		/**
		\brief The meta data of the resource. 

		\details
		The meta data of the resource. This is stored in the resource manager and this member only references
		that meta data in the resource manager.
		*/
		const ResourceMetadata &m_metaData;

		/**
		\brief The name of the loader that this resource was loaded with.

		\details
		The name of the loader that this resource was loaded with. This is stored in the resource loader 
		itself and this member only references that name in the resource loader.
		*/
		const NOU::NOU_DAT_ALG::StringView8 &m_name;

	public:
		/**
		\brief Constructs a new instance.
		*/
		Resource(const ResourceMetadata &metaData, const NOU::NOU_DAT_ALG::StringView8& name);

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

		/**
		\param id The ID of the resource to check.

		\return True if the resource is valid, false if not.

		\brief Returns whether a resouce is valid (= can be loaded and stored) for this loader.
		*/
		virtual NOU::boolean isValidResource(ResourceMetadata::ResourceID id) = 0;

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
		Resource* load(ResourceMetadata::ResourceID id);

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
		virtual NOU::boolean isResourceValid(typename ResourceMetadata::ResourceID id) const = 0;
	};

	class NOU_CLASS ResourceManager final
	{
	private:
	public:
		/**
		\return The static instance of the resource manager.

		\brief Returns the instance of the resource manager.

		\details
		Returns the instance of the resource manager. This method also stores the instance as a static local variable.
		*/
		static ResourceManager& get();

		/**
		\param loader The ResourceLoader to add.

		\brief Adds a new ResourceLoader.
		
		\details 
		Adds a new ResourceLoader. It is only possible to get a ResourceLoader using getLoader() after it has 
		been added using this method.
		*/
		void addLoader(const ResourceLoader &loader);

		/**
		\param name The name of the resource loader to get.

		\return The loader with the passed name, or \p nullptr if there is no such loader.

		\brief Returns the loader with the passed name.
		*/
		ResourceLoader& getLoader(const NOU::NOU_DAT_ALG::StringView8 &name);

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
		typename ResourceMetadata::ResourceID addResource(const NOU::NOU_FILE_MNGT::Path &path, 
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
		NOU::boolean removeResource(typename ResourceMetadata::ResourceID id);

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
		NOU::boolean cache(typename ResourceMetadata::ResourceID id, NOU::boolean enableCache,
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
		NOU::boolean deleteCache(typename ResourceMetadata::ResourceID id);

		/**
		\return A list that contains the meta data of all resources in the database.

		\brief Returns a list that contains the meta data of all resources in the database.
		*/
		NOU::NOU_DAT_ALG::Vector<ResourceMetadata> listMetadata() const;

		/**
		\param id The ID of the resource.

		\return The meta data of the resource with the passed ID, or \p nullptr if the resource does not 
		        exist.

		\brief Returns the meta data of a single resource.
		*/
		const ResourceMetadata* getMetadata(typename ResourceMetadata::ResourceID id) const;
	
		void initalize();

		void shutdown();
	};
}

#endif