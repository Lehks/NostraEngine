#include "nostraengine/core/ResourceManagement.hpp"
#include "nostraengine/core/ErrorCodes.hpp"

#include "SQLite3/sqlite3.h"

#include <iostream>

namespace NOE::NOE_CORE
{
	const NOU::NOU_DAT_ALG::StringView8 ResourceType::SQL_EXISTS_TYPE = 
																"SELECT COUNT(*) FROM Types WHERE ID = ?;";

	const NOU::NOU_DAT_ALG::StringView8 ResourceType::SQL_GENERIC = "SELECT %s FROM Types WHERE ID = ?;";

	const NOU::NOU_DAT_ALG::StringView8 ResourceType::SQL_NAME_NAME = "name";

	const NOU::NOU_DAT_ALG::StringView8 ResourceType::SQL_DESCRIPTION_NAME = "description";

	NOU::NOU_DAT_ALG::String8 ResourceType::getAttribute
													(const NOU::NOU_DAT_ALG::StringView8 &attribute) const
	{
		if (!isValid())
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), 
				NOU::NOU_CORE::ErrorCodes::INVALID_OBJECT, "A type with that ID does not exist.");
			return "__INVALID_TYPE_ATTRIBUTE__";
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

	NOU::boolean ResourceType::checkIfExsists() const
	{
		auto stmt = ResourceManager::get().getUnderlying().execute(SQL_EXISTS_TYPE);
		stmt.bind(m_id);

		NOE::NOE_UTILITY::sqlite::Row *row;

		if (stmt.hasNext())
			row = &stmt.next();
		else
			return false;
		
		if (row->isValid())
		{
			NOU::int32 count = row->valueAs(0, NOE::NOE_UTILITY::sqlite::INTEGER());

			if (count == 0) //no type of that ID was found
			{
				return false;
			}
		}
		else //the row is not valid
		{
			return false;
		}

		return true;
	}
	
	ResourceType::ResourceType(ID id) :
		m_id(id)
	{
		if (m_id != INVALID_ID) //check if exists, if the id is not invalid anyway
		{
			if (!checkIfExsists())
			{
				m_id = INVALID_ID;
			}
		}
	}

	typename ResourceType::ID ResourceType::getID() const
	{
		return m_id;
	}

	NOU::NOU_DAT_ALG::String8 ResourceType::getName() const
	{
		return getAttribute(SQL_NAME_NAME);
	}

	NOU::NOU_DAT_ALG::String8 ResourceType::getDescription() const
	{
		return getAttribute(SQL_DESCRIPTION_NAME);
	}

	NOU::boolean ResourceType::isValid() const
	{
		if (m_id == INVALID_ID)
			return false;
		else
		{
			if (checkIfExsists())
			{
				//it exists
				return true;
			}
			else
			{
				//it does not exist
				m_id = INVALID_ID;
				return false;
			}
		}
	}

	ResourceType::operator NOU::boolean() const
	{
		return isValid();
	}




	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_GENERIC = 
																"SELECT %s FROM Resources WHERE ID = ?;";

	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_TYPE_NAME = "TypesID";
	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_PATH_NAME = "path";
	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_CACHED_PATH_NAME = "cached";

	const NOU::NOU_DAT_ALG::StringView8 ResourceMetadata::SQL_EXISTS_RESOURCE = 
															"SELECT COUNT(*) FROM Resources WHERE ID = ?;";

	NOU::NOU_DAT_ALG::String8 ResourceMetadata::getAttribute
													(const NOU::NOU_DAT_ALG::StringView8 &attribute) const
	{
		if (!isValid())
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				NOU::NOU_CORE::ErrorCodes::INVALID_OBJECT, "A type with that ID does not exist.");
			return "__INVALID_TYPE_ATTRIBUTE__";
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

	NOU::boolean ResourceMetadata::checkIfExsists() const
	{
		auto stmt = ResourceManager::get().getUnderlying().execute(SQL_EXISTS_RESOURCE);
		stmt.bind(m_id);

		NOE::NOE_UTILITY::sqlite::Row *row;

		if (stmt.hasNext())
			row = &stmt.next();
		else
			return false;

		if (row->isValid())
		{
			NOU::int32 count = row->valueAs(0, NOE::NOE_UTILITY::sqlite::INTEGER());

			if (count == 0) //no type of that ID was found
			{
				return false;
			}
		}
		else //the row is not valid
		{
			return false;
		}

		return true;
	}

	ResourceMetadata::ResourceMetadata(ID id) :
		m_id(id)
	{
		//Check if the ID even exists in the database. If not, set it to INVALID_ID

		if (id != INVALID_ID)
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

			
			if (row->isValid())
			{
				NOU::int32 count = row->valueAs(0, NOE::NOE_UTILITY::sqlite::INTEGER());

				if (count == 0)
					m_id = INVALID_ID;
			}
			else
			{
				m_id = INVALID_ID;
				return;
			}
		}
	}

	typename ResourceMetadata::ID ResourceMetadata::getID() const
	{
		return m_id;
	}

	ResourceType ResourceMetadata::getType() const
	{
		if (!isValid())
		{
			return ResourceType();
		}

		NOU::char8 sql[256] = { 0 };
		sprintf(sql, SQL_GENERIC.rawStr(), SQL_TYPE_NAME.rawStr());

		auto stmt = ResourceManager::get().getUnderlying().execute(sql);
		stmt.bind(m_id);

		//there should always be a next
		NOE::NOE_UTILITY::sqlite::Row &row = stmt.next();

		if (!row.isNull(0))
			return ResourceType(row.valueAs(0, NOE::NOE_UTILITY::sqlite::INTEGER()));
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
		if (m_id == INVALID_ID)
			return false;
		else
		{
			if (checkIfExsists())
			{
				//it exists
				return true;
			}
			else
			{
				//it does not exist
				m_id = INVALID_ID;
				return false;
			}
		}
	}

	ResourceMetadata::operator NOU::boolean() const
	{
		return isValid();
	}



	Resource::Resource(ResourceMetadata::ID id, const NOU::NOU_DAT_ALG::StringView8 &name) :
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




	NOU::NOU_FILE_MNGT::Path ResourceManager::DATABASE_PATH = "./Resources.db";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_LIST_IDS = "SELECT ID FROM Resources;";
	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_ADD_RESOURCE =
		"INSERT INTO Resources(path, type, TypesID) VALUES(?, ?, ?)";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_REMOVE = "DELETE %s Resources WHERE ID = ?;";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_UPDATE_CACHE =
		"UPDATE Resources SET TypesID = ? WHERE ID = ?;";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_CREATE_TABLE =
		"CREATE TABLE IF NOT EXISTS Resources (ID INTEGER NOT NULL, "
		"path TEXT NOT NULL UNIQUE CHECK(path NOT LIKE cached), "
		"cached TEXT CHECK(cached NOT LIKE 'NULL'), TypesID INTEGER NOT NULL, PRIMARY KEY (ID));";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_TABLENAME_RESOURCES = "Resources";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_TABLENAME_TYPES = "Types";

	void ResourceManager::deallocateResourceLoader(ResourceLoader *loader)
	{
		delete loader;
	}

	NOU::boolean ResourceManager::removeRow(NOU::int64 id, const NOU::NOU_DAT_ALG::StringView8 &table)
	{
		NOU::char8 sql[256] = { 0 };
		sprintf(sql, SQL_REMOVE.rawStr(), table);


		auto stmt = getUnderlying().execute(sql);
		stmt.bind(id);

		NOE::NOE_UTILITY::sqlite::Row &row = stmt.next();

		return row.affectedRows() > 0;
	}

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

	typename ResourceMetadata::ID ResourceManager::addResource(const NOU::NOU_FILE_MNGT::Path &path,
		typename ResourceType::ID type, NOU::boolean enableCache,
		const NOU::NOU_FILE_MNGT::Path &cachePath)
	{
		auto stmt = getUnderlying().execute(SQL_ADD_RESOURCE);

		stmt.bind(path.getRelativePath().rawStr());
		stmt.bind(type);
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

	NOU::boolean ResourceManager::removeResource(typename ResourceMetadata::ID id)
	{
		return removeRow(id, SQL_TABLENAME_RESOURCES);
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

	NOU::boolean ResourceManager::cache(typename ResourceMetadata::ID id, NOU::boolean enableCache,
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

	NOU::boolean ResourceManager::deleteCache(typename ResourceMetadata::ID id)
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
		auto result = getUnderlying().execute(SQL_LIST_IDS);

		NOU::NOU_DAT_ALG::Vector<ResourceMetadata> ret;

		while(result.hasNext() && result.isValid())
		{
			NOE::NOE_UTILITY::sqlite::Row &row = result.next();

			if (result.hasNext() && result.isValid())
			{
				ResourceMetadata::ID id = row.valueAs(0, NOE::NOE_UTILITY::sqlite::INTEGER());

				ret.push(ResourceMetadata(id));
			}
		}

		return ret;
	}

	ResourceMetadata ResourceManager::getMetadata(typename ResourceMetadata::ID id) const
	{
		return ResourceMetadata(id);
	}

	typename ResourceType::ID ResourceManager::addType(const NOU::NOU_DAT_ALG::StringView8 &name)
	{

	}

	typename ResourceType::ID ResourceManager::addType(const NOU::NOU_DAT_ALG::StringView8 &name, 
		const NOU::NOU_DAT_ALG::StringView8 &description)
	{

	}

	NOU::boolean ResourceManager::removeType(typename ResourceType::ID id)
	{
		return removeRow(id, SQL_TABLENAME_TYPES);
	}

	ResourceType ResourceManager::getType(typename ResourceType::ID id) const
	{

	}

	NOU::NOU_DAT_ALG::Vector<ResourceType> ResourceManager::listTypes() const
	{

	}

	void ResourceManager::initalize()
	{
		m_database.open(); ///\todo add error handling

		auto result = m_database.execute(SQL_CREATE_TABLE);
		result.next();
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