#ifndef NOE_CORE_RESOURCE_HPP
#define NOE_CORE_RESOURCE_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/resource_mngt/ResourceMetadata.hpp"
#include "nostraengine/core/resource_mngt/ResourceType.hpp"

/**
\file    core/resource_mngt/Resource.hpp
\author  Lukas Reichmann
\version 1.0.0
\since   0.0.1

\brief A file that contains the class Resource.
*/

namespace NOE::NOE_CORE
{
	/**
	\brief A class that is the base class of any resource that is managed by the ResourceManager.

	\details
	A class that is the base class of any resource that is managed by the ResourceManager. For a full tutorial
	on how to use the resource management system, see \link resourceManagementSys this page\endlink.
	*/
	class NOU_CLASS Resource
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
		const NOU::NOU_DAT_ALG::String8 m_name;

	public:
		/**
		\param id   The ID of the resource.
		\param name The name of the loader that this resource was loaded with.

		\brief Constructs a new instance.
		*/
		Resource(ResourceMetadata::ID id, const NOU::NOU_DAT_ALG::String8& name);

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
		const NOU::NOU_DAT_ALG::String8& getLoaderName() const;

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
}

#endif