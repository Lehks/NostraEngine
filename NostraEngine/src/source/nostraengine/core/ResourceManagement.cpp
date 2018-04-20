#include "nostraengine/core/ResourceManagement.hpp"

namespace NOE::NOE_CORE
{
	ResourceMetadata::ResourceMetadata(ResourceID id, const NOU::NOU_FILE_MNGT::Path &path,
		const ResourceType &type, NOU::boolean isCached,
		const NOU::NOU_FILE_MNGT::Path &cachePath) :
		m_id(id),
		m_type(type),
		m_path(path),
		m_isCached(isCached),
		m_cachePath(cachePath)
	{}

	typename ResourceMetadata::ResourceID ResourceMetadata::getID() const
	{
		return m_id;
	}

	const typename ResourceMetadata::ResourceType& ResourceMetadata::getType() const
	{
		return m_type;
	}

	const NOU::NOU_FILE_MNGT::Path& ResourceMetadata::getPath() const
	{
		return m_path;
	}

	NOU::boolean ResourceMetadata::isCached() const
	{
		return m_isCached;
	}

	const NOU::NOU_FILE_MNGT::Path& ResourceMetadata::getCachePath() const
	{
		return m_cachePath;
	}



	Resource::Resource(const ResourceMetadata &metaData, const NOU::NOU_DAT_ALG::StringView8 &name) :
		m_metaData(metaData),
		m_name(name)
	{}

	const ResourceMetadata& Resource::getMetadata() const
	{
		return m_metaData;
	}

	const NOU::NOU_DAT_ALG::StringView8& Resource::getLoaderName() const
	{
		return m_name;
	}

	NOU::boolean Resource::store()
	{
		return ResourceManager::get().getLoader(getLoaderName())->store(this);
	}

	NOU::boolean Resource::cache(NOU::boolean enableCache,
		const NOU::NOU_FILE_MNGT::Path &path)
	{
		return ResourceManager::get().cache(getMetadata().getID(), enableCache, path);
	}

	void Resource::deleteCache()
	{
		ResourceManager::get().deleteCache(getMetadata().getID());
	}



	ResourceLoader::ResourceLoader(const NOU::NOU_DAT_ALG::String8 &name) :
		m_name(name)
	{}

	const NOU::NOU_DAT_ALG::StringView8& ResourceLoader::getName() const
	{
		return m_name;
	}

	void ResourceLoader::enableCaching(NOU::boolean enable)
	{
		m_enableCaching = enable;
	}

	NOU::boolean ResourceLoader::isCachingEnabled()
	{
		return m_enableCaching;
	}

	Resource* ResourceLoader::load(ResourceMetadata::ResourceID id)
	{
		const ResourceMetadata *metadata = ResourceManager::get().getMetadata(id);

		if (metadata != nullptr && !isValidResource(id))
			return nullptr;

		Resource *ret = nullptr;

		if (isCachingEnabled())
			ret = loadCacheImpl(*metadata, metadata->getCachePath());

		if (ret == nullptr)
			return loadImpl(*metadata, metadata->getPath());
	}

	NOU::boolean ResourceLoader::store(Resource *resource)
	{
		const ResourceMetadata *metadata = &resource->getMetadata();

		if (metadata != nullptr && !isValidResource(metadata->getID()))
			return false;

		NOU::boolean ret;

		if (isCachingEnabled())
			ret = storeCacheImpl(resource, metadata->getCachePath());

		if (!ret)
			return storeImpl(resource, metadata->getPath());
	}

	void ResourceLoader::close(Resource *resource)
	{
		if (resource == nullptr)
			return;

		///\todo implement
	}


	void ResourceManager::allocResourceLoader(ResourceLoader *loader)
	{
		delete loader;
	}

	ResourceManager& ResourceManager::get()
	{
		static ResourceManager instance;
		return instance;
	}

	ResourceLoader* ResourceManager::getLoader(const NOU::NOU_DAT_ALG::StringView8 &name)
	{
		if (!m_loaders.containsKey(name))
			return m_loaders.get(name);
		else
			return nullptr;
	}

	void ResourceManager::deleteCaches()
	{

	}

	typename ResourceMetadata::ResourceID ResourceManager::addResource(const NOU::NOU_FILE_MNGT::Path &path,
		const typename ResourceMetadata::ResourceType &type, NOU::boolean enableCache,
		const NOU::NOU_FILE_MNGT::Path &cachePath)
	{
		return 0;
	}

	NOU::boolean ResourceManager::removeResource(typename ResourceMetadata::ResourceID id)
	{
		return false;
	}

	NOU::uint32 ResourceManager::cleanupResources()
	{
		return 0;
	}

	NOU::boolean ResourceManager::cache(typename ResourceMetadata::ResourceID id, NOU::boolean enableCache,
		const NOU::NOU_FILE_MNGT::Path &path)
	{
		return false;
	}

	NOU::boolean ResourceManager::deleteCache(typename ResourceMetadata::ResourceID id)
	{
		return false;
	}

	NOU::NOU_DAT_ALG::Vector<ResourceMetadata> ResourceManager::listMetadata() const
	{
		return NOU::NOU_DAT_ALG::Vector<ResourceMetadata>();
	}

	const ResourceMetadata* ResourceManager::getMetadata(typename ResourceMetadata::ResourceID id) const
	{
		return nullptr;
	}

	void ResourceManager::initalize()
	{

	}

	void ResourceManager::shutdown()
	{

	}
}