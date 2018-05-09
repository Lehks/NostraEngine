#ifndef NOE_CORE_RESOURCE_LOADER_HPP
#define NOE_CORE_RESOURCE_LOADER_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/resource_mngt/ResourceMetadata.hpp"
#include "nostraengine/core/resource_mngt/ResourceType.hpp"
#include "nostraengine/core/resource_mngt/Resource.hpp"

namespace NOE::NOE_CORE
{
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
}

#endif