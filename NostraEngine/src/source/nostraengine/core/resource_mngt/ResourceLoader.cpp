
#include "nostraengine/core/ResourceManagement.hpp"

namespace NOE::NOE_CORE
{
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

	Resource* ResourceLoader::load(ResourceMetadata::ID id)
	{
		ResourceMetadata metadata = ResourceManager::get().getMetadata(id);

		if (ResourceManager::get().getMetadata(id) && !isResourceValid(id))
			return nullptr;

		Resource *ret = nullptr;

		if (isCachingEnabled())
			ret = loadCacheImpl(metadata, metadata.getCachePath());

		if (ret == nullptr)
			return loadImpl(metadata, metadata.getPath());

		return nullptr;
	}

	NOU::boolean ResourceLoader::store(Resource *resource)
	{
		ResourceMetadata metadata = resource->getMetadata();

		if (metadata.isValid() && !isResourceValid(metadata.getID()))
			return false;

		NOU::boolean ret;

		if (isCachingEnabled())
			ret = storeCacheImpl(resource, metadata.getCachePath());

		if (!ret)
			return storeImpl(resource, metadata.getPath());

		return false;
	}

	void ResourceLoader::close(Resource *resource)
	{
		ResourceManager::get().deallocateResource(resource);
	}
}