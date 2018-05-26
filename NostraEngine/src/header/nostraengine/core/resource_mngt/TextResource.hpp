#ifndef NOU_CORE_TEXT_RESOURCE_HPP
#define NOU_CORE_TEXT_RESOURCE_HPP

#include "nostraengine/core/resource_mngt/ResourceType.hpp"
#include "nostraengine/core/resource_mngt/ResourceMetadata.hpp"
#include "nostraengine/core/resource_mngt/Resource.hpp"
#include "nostraengine/core/resource_mngt/ResourceLoader.hpp"
#include "nostraengine/core/resource_mngt/ResourceManager.hpp"

/**
\file    core/resource_mngt/TextResource.hpp
\author  Lukas Reichmann
\version 1.0.0
\since   0.0.1

\brief A file that contains the class TextResource and TextResourceLoader.
*/

namespace NOE::NOE_CORE
{
	/**
	\brief A resource type that contains the content of a file as a string.
	*/
	class NOU_CLASS TextResource final : public Resource
	{
	private:
		/**
		\brief The text in the file.
		*/
		NOU::NOU_DAT_ALG::String8 m_text;

	public:
		/**
		\param id    The ID of the resource.
		\param name  The name of the loader that this resource was loaded with.
		\param bytes The byte array.
		*/
		TextResource(ResourceMetadata::ID id, const NOU::NOU_DAT_ALG::String8& name,
			NOU::NOU_DAT_ALG::String8 &&text);

		/**
		\return The text.

		\brief Returns the text.
		*/
		NOU::NOU_DAT_ALG::String8& getText();

		/**
		\return The text.

		\brief Returns the text.
		*/
		const NOU::NOU_DAT_ALG::String8& getText() const;
	};

	/**
	\brief A loader for TextResource, a resource that stores the content of a class as a string.
	*/
	class NOU_CLASS TextResourceLoader final : public ResourceLoader
	{
	public:
		/**
		\brief The name of the loader.
		*/
		static const NOU::NOU_DAT_ALG::String8 NAME;

	protected:

		/**
		\param resource The resource to store.
		\param path     The path to store the resource to.

		\return True, if the resource could be stored, false if not.

		\brief Stores the passed resource to the passed path.
		*/
		virtual NOU::boolean storeImpl(Resource *resource, const NOU::NOU_FILE_MNGT::Path& path) override;

		/**
		\param resource Unused.
		\param path     Unused.

		\return \p false

		\brief Does nothing - caching is disabled for this loader.
		*/
		virtual NOU::boolean storeCacheImpl(Resource *resource, const NOU::NOU_FILE_MNGT::Path& path) override;

		/**
		\param metaData The metadata of the resource to load.
		\param path     The path to load the resource from.

		\return A valid resource if it could be loaded, or \p nullptr if not.

		\brief Loads the passed resource from the passed path.
		*/
		virtual Resource* loadImpl(const ResourceMetadata &metaData,
			const NOU::NOU_FILE_MNGT::Path& path) override;

		/**
		\param metaData Unused.
		\param path     Unused.

		\return \p nullptr

		\brief Does nothing - caching is disabled for this loader.
		*/
		virtual Resource* loadCacheImpl(const ResourceMetadata &metaData,
			const NOU::NOU_FILE_MNGT::Path& path) override;

	public:
		/**
		\brief Constructs a new instance.
		*/
		TextResourceLoader();

		/**
		\param id The ID of the resource to check.

		\return \p true

		\brief This loader can load any file, hence this method will always return true.
		*/
		virtual NOU::boolean isResourceValid(typename ResourceMetadata::ID id) const override;

	};
}

#endif