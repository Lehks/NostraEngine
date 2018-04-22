#include "nostraengine/core/ResourceManagement.hpp"

namespace NOE::NOE_CORE
{
	constexpr ResourceMetadata::ResourceID ResourceMetadata::INVALID_ID;

	ResourceMetadata::ResourceMetadata(ResourceID id) :
		m_id(id),
		m_path(""),
		m_cachePath("")
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

	NOU::boolean ResourceMetadata::isValid() const
	{
		return m_id != 0;
	}

	ResourceMetadata::operator NOU::boolean() const
	{
		return isValid();
	}



	Resource::Resource(ResourceMetadata::ResourceID id, const NOU::NOU_DAT_ALG::StringView8 &name) :
		m_id(id),
		m_name(name)
	{}

	ResourceMetadata Resource::getMetadata() const
	{
		return ResourceManager::get().getMetadata(m_id);
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
		ResourceMetadata metadata = ResourceManager::get().getMetadata(id);

		if (metadata && !isValidResource(id))
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
		const ResourceMetadata *metadata = &resource->getMetadata();

		if (metadata != nullptr && !isValidResource(metadata->getID()))
			return false;

		NOU::boolean ret;

		if (isCachingEnabled())
			ret = storeCacheImpl(resource, metadata->getCachePath());

		if (!ret)
			return storeImpl(resource, metadata->getPath());

		return false;
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

	const NOU::NOU_FILE_MNGT::Path ResourceManager::DATABASE_PATH = "./Resources.db";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_LIST_IDS = "SELECT ID FROM Resources;";

	ResourceManager::ResourceManager(const NOU::NOU_FILE_MNGT::Path &databasePath) :
		m_database(databasePath)
	{}

	ResourceManager::ResourceManager() :
		m_database(DATABASE_PATH)
	{}

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

	NOU::NOU_DAT_ALG::Vector<ResourceMetadata> ResourceManager::listMetadata()
	{
		//Check if the sizeof ID and int32 match; otherwise stringToInt32() needs to be changed
		static_assert(sizeof(ResourceMetadata::ResourceID) == sizeof(NOU::int32));

		auto result = getUnderlying().executeSQL(SQL_LIST_IDS);

		NOU::NOU_DAT_ALG::Vector<ResourceMetadata> ret;

		for (auto &row : result.getRows())
		{
			ResourceMetadata::ResourceID id = 
				NOU::NOU_DAT_ALG::String8::stringToInt32(*row.getEntries()[0].getValue());

			ResourceMetadata metadata(id);

			ret.push(metadata);
		}

		return ret;
	}

	ResourceMetadata ResourceManager::getMetadata(typename ResourceMetadata::ResourceID id) const
	{
		return ResourceMetadata(id);
	}

	void ResourceManager::initalize()
	{
		m_database.open(); ///\todo add error handling
	}

	void ResourceManager::shutdown()
	{
		m_database.close(); ///\todo add error handling
	}

	NOE::NOE_UTILITY::sqlite::Database& ResourceManager::getUnderlying()
	{
		return m_database;
	}
}