#include "nostraengine/core/ResourceManagement.hpp"
#include "nostraengine/core/ErrorCodes.hpp"

namespace NOE::NOE_CORE
{
	constexpr ResourceMetadata::ResourceID ResourceMetadata::INVALID_ID;

	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_GENERIC = 
																"SELECT %s FROM Resources WHERE ID = %d;";

	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_TYPE_NAME = "type";
	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_PATH_NAME = "path";
	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_CACHED_PATH_NAME = "cached";

	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_EXISTS_RESOURCE = 
															"SELECT COUNT(*) FROM Resources WHERE ID = %d";

	NOU::NOU_DAT_ALG::Uninitialized<NOU::NOU_FILE_MNGT::Path> ResourceMetadata::getCachePathImp() const
	{
		NOU::char8 sql[128] = { 0 };

		sprintf(sql, SQL_GENERIC.rawStr(), SQL_CACHED_PATH_NAME.rawStr(), m_id);

		auto result = ResourceManager::get().getUnderlying().executeSQL(sql);

		NOU_COND_PUSH_ERROR(!result.isValid(), NOU::NOU_CORE::getErrorHandler(), 
			NOE::NOE_CORE::ErrorCodes::SQL_EXECUTION_ERROR, "The attribute 'cached' could not be queried.");

		auto val = result.getRows()[0].getEntries()[0].getValue();

		if (val != nullptr)
			return *val;
		else
			return NOU::NOU_DAT_ALG::Uninitialized<NOU::NOU_FILE_MNGT::Path>();
	}

	ResourceMetadata::ResourceMetadata(ResourceID id) :
		m_id(id)
	{
		//Check if the ID even exists in the database. If not, 

		if (id != 0)
		{
			NOU::char8 sql[256] = { 0 };
			sprintf(sql, SQL_EXISTS_RESOURCE.rawStr(), id);

			auto result = ResourceManager::get().getUnderlying().executeSQL(sql);

			if (!result.isValid() || result.getRows().size() == 0)
			{
				m_id = INVALID_ID;
				return;
			}

			NOU::int32 count = 
				NOU::NOU_DAT_ALG::StringView8::stringToInt32(*result.getRows()[0].getEntries()[0].getValue());

			if (count == 0)
			{
				m_id = INVALID_ID;
			}
		}
	}

	typename ResourceMetadata::ResourceID ResourceMetadata::getID() const
	{
		return m_id;
	}

	typename ResourceMetadata::ResourceType ResourceMetadata::getType() const
	{
		if (!isValid())
			return "NULL";

		NOU::char8 sql[128] = { 0 };

		sprintf(sql, SQL_GENERIC.rawStr(), SQL_TYPE_NAME.rawStr(), m_id);

		auto result = ResourceManager::get().getUnderlying().executeSQL(sql);

		NOU_COND_PUSH_ERROR(!result.isValid(), NOU::NOU_CORE::getErrorHandler(),
			NOE::NOE_CORE::ErrorCodes::SQL_EXECUTION_ERROR, "The attribute 'type' could not be queried.");

		return *result.getRows()[0].getEntries()[0].getValue();
	}

	NOU::NOU_FILE_MNGT::Path ResourceMetadata::getPath() const
	{
		if (!isValid())
			return "NULL";

		NOU::char8 sql[128] = {0};

		sprintf(sql, SQL_GENERIC.rawStr(), SQL_PATH_NAME.rawStr(), m_id);

		auto result = ResourceManager::get().getUnderlying().executeSQL(sql);

		NOU_COND_PUSH_ERROR(!result.isValid(), NOU::NOU_CORE::getErrorHandler(),
			NOE::NOE_CORE::ErrorCodes::SQL_EXECUTION_ERROR, "The attribute 'path' could not be queried.");

		return NOU::NOU_FILE_MNGT::Path(*result.getRows()[0].getEntries()[0].getValue());
	}

	NOU::boolean ResourceMetadata::isCached() const
	{
		if (!isValid())
			return false;

		return getCachePathImp().isValid();
	}

	NOU::NOU_FILE_MNGT::Path ResourceMetadata::getCachePath() const
	{
		return *getCachePathImp();
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
		m_metadata(id),
		m_name(name)
	{}

	const ResourceMetadata& Resource::getMetadata() const
	{
		return m_metadata;
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



	void ResourceManager::deallocateResourceLoader(ResourceLoader *loader)
	{
		delete loader;
	}

	NOU::NOU_FILE_MNGT::Path ResourceManager::DATABASE_PATH = "./Resources.db";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_LIST_IDS = "SELECT ID FROM Resources;";
	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_ADD_RESOURCE =
										"INSERT INTO Resources(path, type, cached) VALUES('%s', '%s', '%s')";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_ADD_RESOURCE_NO_CACHE =
										"INSERT INTO Resources(path, type, cached) VALUES('%s', '%s', NULL)";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_GET_ID = 
											"SELECT ID FROM Resources WHERE path = '%s';";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_REMOVE =
																	"DELETE FROM Resources WHERE ID = %d;";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_UPDATE_CACHE =
														"UPDATE Resources SET cached = '%s' WHERE ID = %d;";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_UPDATE_CACHE_NULL =
														"UPDATE Resources SET cached = NULL WHERE ID = %d;";

	ResourceManager::ResourceManager(const NOU::NOU_FILE_MNGT::Path &databasePath) :
		m_database(databasePath)
	{}

	ResourceManager::ResourceManager() :
		m_database(DATABASE_PATH)
	{}

	void ResourceManager::deallocateResource(Resource *resource)
	{
		delete resource;
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
		auto metadata = listMetadata();

		for (auto &mdata : metadata)
		{
			deleteCache(mdata.getID());
		}
	}

	typename ResourceMetadata::ResourceID ResourceManager::addResource(const NOU::NOU_FILE_MNGT::Path &path,
		const typename ResourceMetadata::ResourceType &type, NOU::boolean enableCache,
		const NOU::NOU_FILE_MNGT::Path &cachePath)
	{
		NOU::char8 sql[1024] = { 0 };

		if(enableCache)
			sprintf(sql, SQL_ADD_RESOURCE.rawStr(), path.getRelativePath().rawStr(), type.rawStr(), 
																cachePath.getRelativePath().rawStr());
		else
			sprintf(sql, SQL_ADD_RESOURCE_NO_CACHE.rawStr(), path.getRelativePath().rawStr(), type.rawStr());

		auto result = getUnderlying().executeSQL(sql);

		if (result.isValid())
		{
			memset(sql, 0, sizeof(sql) / sizeof(sql[0]));

			sprintf(sql, SQL_GET_ID.rawStr(), path.getRelativePath().rawStr());

			auto result = getUnderlying().executeSQL(sql);

			auto val = result.getRows()[0].getEntries()[0].getValue();

			return NOU::NOU_DAT_ALG::StringView8::stringToInt32(*val);
		}
		else
		{
			std::cout << result.getErrorMsg().rawStr() << std::endl;
			return ResourceMetadata::INVALID_ID;
		}
	}

	NOU::boolean ResourceManager::removeResource(typename ResourceMetadata::ResourceID id)
	{
		NOU::char8 sql[128] = { 0 };

		sprintf(sql, SQL_REMOVE.rawStr(), id);

		auto result = getUnderlying().executeSQL(sql);

		return result.getAffectedRows() > 0;
	}

	NOU::uint32 ResourceManager::cleanupResources()
	{
		NOU::NOU_DAT_ALG::Vector<ResourceMetadata> metadata = listMetadata();

		NOU::int32 counter = 0;

		for (auto &data : metadata)
		{
			NOU::NOU_FILE_MNGT::File file(data.getPath());

			if (!file.exists())
			{
				removeResource(data.getID());
				counter++;
			}
		}

		return counter;
	}

	NOU::boolean ResourceManager::cache(typename ResourceMetadata::ResourceID id, NOU::boolean enableCache,
		const NOU::NOU_FILE_MNGT::Path &path)
	{
		ResourceMetadata metadata = ResourceManager::get().getMetadata(id);

		NOU::char8 sql[1024] = { 0 };

		if (enableCache)
			sprintf(sql, SQL_UPDATE_CACHE.rawStr(), path.getRelativePath().rawStr(), id);
		else
			sprintf(sql, SQL_UPDATE_CACHE_NULL.rawStr(), id);
		
		auto result = getUnderlying().executeSQL(sql);

		return result.getAffectedRows() > 0;
	}

	NOU::boolean ResourceManager::deleteCache(typename ResourceMetadata::ResourceID id)
	{
		ResourceMetadata metadata = ResourceManager::get().getMetadata(id);

		if (metadata.isCached())
		{
			NOU::NOU_FILE_MNGT::File file(metadata.getCachePath());

			//delete file
		}

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