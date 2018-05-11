#include "nostraengine/core/ResourceManagement.hpp"

#include "nostrautils/dat_alg/StringView.hpp"

/**
\file    core/resource_mngt/ByteResource.hpp
\author  Lukas Reichmann
\version 1.0.0
\since   0.0.1

\brief A file that contains the class ByteResource and ByteResourceLoader.
*/

namespace NOE::NOE_CORE
{
	/**
	\brief A resource type that contains the content of a file as byte array. This loader ist mostly used for
	other loaders to build upon it.
	*/
	class NOU_CLASS ByteResource final : public Resource
	{
	private:
		/**
		\brief The bytes in the file.
		*/
		NOU::NOU_DAT_ALG::Vector<NOU::byte> m_bytes;

	public:
		/**
		\param id    The ID of the resource.
		\param name  The name of the loader that this resource was loaded with.
		\param bytes The byte array.
		*/
		ByteResource(ResourceMetadata::ID id, const NOU::NOU_DAT_ALG::StringView8& name, 
			NOU::NOU_DAT_ALG::Vector<NOU::byte> &&bytes);

		/**
		\return The byte array.

		\brief Returns the byte array.
		*/
		NOU::NOU_DAT_ALG::Vector<NOU::byte>& getBytes();

		/**
		\return The byte array.

		\brief Returns the byte array.
		*/
		const NOU::NOU_DAT_ALG::Vector<NOU::byte>& getBytes() const;
	};

	/**
	\brief A loader for ByteResource, a resource that stores the content of a class as byte array.
	*/
	class NOU_CLASS ByteResourceLoader final : public ResourceLoader 
	{
	public:
		/**
		\brief The name of the loader.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 NAME;

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
		ByteResourceLoader();

		/**
		\param id The ID of the resource to check.

		\return \p true

		\brief This loader can load any file, hence this method will always return true.
		*/
		virtual NOU::boolean isResourceValid(typename ResourceMetadata::ID id) const override;

	};
}