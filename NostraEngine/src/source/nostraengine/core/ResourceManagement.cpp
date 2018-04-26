#include "nostraengine/core/ResourceManagement.hpp"
#include "nostraengine/core/ErrorCodes.hpp"

namespace NOE::NOE_CORE
{
	constexpr ResourceMetadata::ResourceID ResourceMetadata::INVALID_ID;

	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_GENERIC = 
																"SELECT %s FROM Resources WHERE ID = ?;";

	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_TYPE_NAME = "type";
	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_PATH_NAME = "path";
	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_CACHED_PATH_NAME = "cached";

	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_EXISTS_RESOURCE = 
															"SELECT COUNT(*) FROM Resources WHERE ID = ?;";

	NOU::NOU_DAT_ALG::String8 ResourceMetadata::getAttribute
													(const NOU::NOU_DAT_ALG::StringView8 &attribute) const
	{
		if (!isValid())
		{
			return "NULL";
		}

		NOU::char8 sql[256] = { 0 };
		sprintf(sql, SQL_GENERIC.rawStr(), attribute.rawStr());

		auto stmt = ResourceManager::get().getUnderlying().execute(sql);
		stmt.bind(m_id);

		//there should always be a next
		NOE::NOE_UTILITY::sqlite::Row &row = stmt.next();

		if (!row.isNull(0))
			return row.valueAs(0, NOE::NOE_UTILITY::sqlite::STRING());
	}

	ResourceMetadata::ResourceMetadata(ResourceID id) :
		m_id(id)
	{
		//Check if the ID even exists in the database. If not, set it to INVALID_ID

		if (id != 0)
		{
			auto stmt = ResourceManager::get().getUnderlying().execute(SQL_EXISTS_RESOURCE);
			stmt.bind(id);

			NOE::NOE_UTILITY::sqlite::Row *row;

			if (stmt.hasNext())
			{
				row = &stmt.next();
			}
			else
			{
				m_id = INVALID_ID;
				return;
			}

			NOU::int32 count = row->valueAs(0, NOE::NOE_UTILITY::sqlite::INTEGER());

			if (count == 0)
				m_id = INVALID_ID;
		}
	}

	typename ResourceMetadata::ResourceID ResourceMetadata::getID() const
	{
		return m_id;
	}

	typename ResourceMetadata::ResourceType ResourceMetadata::getType() const
	{
		return getAttribute(SQL_TYPE_NAME);
	}

	NOU::NOU_FILE_MNGT::Path ResourceMetadata::getPath() const
	{
		return getAttribute(SQL_PATH_NAME);
	}

	NOU::boolean ResourceMetadata::isCached() const
	{
		if (!isValid())
		{
			return false;
		}

		NOU::char8 sql[256] = { 0 };
		sprintf(sql, SQL_GENERIC.rawStr(), SQL_CACHED_PATH_NAME.rawStr());

		auto stmt = ResourceManager::get().getUnderlying().execute(sql);
		stmt.bind(m_id);

		//there should always be a next
		NOE::NOE_UTILITY::sqlite::Row &row = stmt.next();

		return !row.isNull(0);
	}

	NOU::NOU_FILE_MNGT::Path ResourceMetadata::getCachePath() const
	{
		return getAttribute(SQL_CACHED_PATH_NAME);
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
										"INSERT INTO Resources(path, type, cached) VALUES(?, ?, ?)";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_REMOVE = "DELETE FROM Resources WHERE ID = ?;";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_UPDATE_CACHE =
														"UPDATE Resources SET cached = ? WHERE ID = ?;";

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
		auto stmt = getUnderlying().execute(SQL_ADD_RESOURCE);

		stmt.bind(path.getRelativePath().rawStr());
		stmt.bind(type.rawStr());
		if (enableCache)
			stmt.bind(cachePath.getRelativePath().rawStr());
		else
			stmt.bind(nullptr);

		auto row = stmt.next();

		if (row.affectedRows() == 0)
			return ResourceMetadata::INVALID_ID;
		else
			return row.lastRowId();
	}

	NOU::boolean ResourceManager::removeResource(typename ResourceMetadata::ResourceID id)
	{
		auto stmt = getUnderlying().execute(SQL_REMOVE);
		stmt.bind(id);

		NOE::NOE_UTILITY::sqlite::Row &row = stmt.next();

		return row.affectedRows() > 0;
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

		auto stmt = getUnderlying().execute(SQL_UPDATE_CACHE);
		
		if (enableCache)
			stmt.bind(path.getRelativePath().rawStr());
		else
			stmt.bind(nullptr);

		stmt.bind(id);

		NOE::NOE_UTILITY::sqlite::Row &row = stmt.next();

		return row.affectedRows() > 0;
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

		auto result = getUnderlying().execute(SQL_LIST_IDS);

		NOU::NOU_DAT_ALG::Vector<ResourceMetadata> ret;

		while(result.hasNext())
		{
			NOE::NOE_UTILITY::sqlite::Row &row = result.next();

			if (result.hasNext())
			{
				ResourceMetadata::ResourceID id = row.valueAs(0, NOE::NOE_UTILITY::sqlite::INTEGER());

				ret.push(ResourceMetadata(id));
			}
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