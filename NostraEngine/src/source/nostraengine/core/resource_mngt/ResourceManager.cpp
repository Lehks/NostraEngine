
#include "nostraengine/core/ResourceManagement.hpp"

#if NOU_COMPILER == NOU_COMPILER_VISUAL_CPP
#     pragma warning(disable : 4996)
#endif

namespace NOE::NOE_CORE
{
	NOU::NOU_FILE_MNGT::Path ResourceManager::DATABASE_PATH = "./Resources.db";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_LIST_IDS = 
		"SELECT ID FROM %s;";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_ADD_RESOURCE =
		"INSERT INTO Resources(path, TypesID, cached) VALUES(?, ?, ?)";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_ADD_TYPE =
		"INSERT INTO Types(name, description) VALUES (?, ?)";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_REMOVE = 
		"DELETE FROM %s WHERE ID = ?;";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_UPDATE_CACHE =
		"UPDATE Resources SET cached = ? WHERE ID = ?;";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_CREATE_TABLE_RESOURCES =
		"CREATE TABLE IF NOT EXISTS `Resources` (												   "
		"	`ID`	INTEGER NOT NULL,															   "
		"	`path`	TEXT NOT NULL CHECK(path NOT LIKE cached) UNIQUE,							   "
		"	`cached`	TEXT CHECK(cached NOT LIKE 'NULL'),										   "
		"	`TypesID`	INTEGER NOT NULL,														   "
		"	PRIMARY KEY(`ID`),																	   "
		"	FOREIGN KEY(`TypesID`) REFERENCES `Types`(`ID`) ON DELETE NO ACTION ON UPDATE CASCADE);";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_CREATE_TABLE_TYPES =
		"CREATE TABLE IF NOT EXISTS Types(							 "
		"	ID          INTEGER NOT NULL,							 "
		"	name        TEXT NOT NULL UNIQUE,						 "
		"	description TEXT,										 "
		"	PRIMARY KEY(ID));										 ";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_TABLENAME_RESOURCES = "Resources";

	const NOU::NOU_DAT_ALG::StringView8 ResourceManager::SQL_TABLENAME_TYPES = "Types";

	void ResourceManager::deallocateResourceLoader(ResourceLoader *loader)
	{
		delete loader;
	}

	NOU::boolean ResourceManager::removeRow(NOU::int64 id, const NOU::NOU_DAT_ALG::StringView8 &table)
	{
		NOU::char8 sql[256] = { 0 };
		sprintf(sql, SQL_REMOVE.rawStr(), table.rawStr());


		auto stmt = getUnderlying().execute(sql);
		stmt.bind(id);

		NOE::NOE_UTILITY::sqlite::Row &row = stmt.next();

		return row.affectedRows() > 0;
	}

	ResourceManager::ResourceManager() :
		m_database(DATABASE_PATH),
		m_typeRemoveUpdates(1),
		m_resourceRemoveUpdates(1)
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

	ResourceLoader* ResourceManager::getLoader(const NOU::NOU_DAT_ALG::String8 &name)
	{
		if (m_loaders.containsKey(name))
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
		if(type == ResourceType::INVALID_ID)
			return ResourceMetadata::INVALID_ID;

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
			return ResourceMetadata::ID(row.lastRowId());
	}

	NOU::boolean ResourceManager::removeResource(typename ResourceMetadata::ID id)
	{
		NOU::boolean ret = removeRow(id, SQL_TABLENAME_RESOURCES);

		if (ret)
			m_resourceRemoveUpdates++;

		return ret;
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

			std::cout << file.getPath().getAbsolutePath().rawStr() << std::endl;

			return file.deleteFile();
		}

		return false;
	}

	ResourceMetadata ResourceManager::getMetadata(typename ResourceMetadata::ID id) const
	{
		return ResourceMetadata(id);
	}

	NOU::NOU_DAT_ALG::Vector<ResourceMetadata> ResourceManager::listMetadata()
	{
		NOU::char8 sql[256] = { 0 };
		sprintf(sql, SQL_LIST_IDS.rawStr(), SQL_TABLENAME_RESOURCES.rawStr());

		auto result = getUnderlying().execute(sql);

		NOU::NOU_DAT_ALG::Vector<ResourceMetadata> ret;

		while (result.hasNext() && result.isValid())
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

	typename ResourceType::ID ResourceManager::addType(const NOU::NOU_DAT_ALG::StringView8 &name)
	{
		auto stmt = getUnderlying().execute(SQL_ADD_TYPE);

		stmt.bind(name);
		stmt.bind(nullptr);

		auto row = stmt.next();

		if (row.affectedRows() == 0)
			return ResourceType::INVALID_ID;
		else
			return ResourceMetadata::ID(row.lastRowId());
	}

	typename ResourceType::ID ResourceManager::addType(const NOU::NOU_DAT_ALG::StringView8 &name,
		const NOU::NOU_DAT_ALG::StringView8 &description)
	{
		auto stmt = getUnderlying().execute(SQL_ADD_TYPE);

		stmt.bind(name);
		stmt.bind(description);

		auto row = stmt.next();

		if (row.affectedRows() == 0)
			return ResourceType::INVALID_ID;
		else
			return ResourceMetadata::ID(row.lastRowId());
	}

	NOU::boolean ResourceManager::removeType(typename ResourceType::ID id)
	{
		NOU::boolean ret = removeRow(id, SQL_TABLENAME_TYPES);

		if (ret)
			m_typeRemoveUpdates++;

		return ret;
	}

	ResourceType ResourceManager::getType(typename ResourceType::ID id) const
	{
		return ResourceType(id);
	}

	NOU::NOU_DAT_ALG::Vector<ResourceType> ResourceManager::listTypes()
	{
		NOU::char8 sql[256] = { 0 };
		sprintf(sql, SQL_LIST_IDS.rawStr(), SQL_TABLENAME_TYPES.rawStr());

		auto result = getUnderlying().execute(sql);

		NOU::NOU_DAT_ALG::Vector<ResourceType> ret;

		while (result.hasNext() && result.isValid())
		{
			NOE::NOE_UTILITY::sqlite::Row &row = result.next();

			if (result.hasNext() && result.isValid())
			{
				ResourceType::ID id = row.valueAs(0, NOE::NOE_UTILITY::sqlite::INTEGER());

				ret.push(ResourceType(id));
			}
		}

		return ret;
	}

	NOU::int32 ResourceManager::getTypeRemoveUpdates() const
	{
		return m_typeRemoveUpdates;
	}

	NOU::int32 ResourceManager::getResourceRemoveUpdates() const
	{
		return m_resourceRemoveUpdates;
	}

	void ResourceManager::initalize()
	{
		m_database.open(); ///\todo add error handling

		auto resultTypes = m_database.execute(SQL_CREATE_TABLE_TYPES);
		resultTypes.next();

		auto resultResources = m_database.execute(SQL_CREATE_TABLE_RESOURCES);
		resultResources.next();
	}

	void ResourceManager::terminate()
	{
		m_database.close(); ///\todo add error handling
	}

	NOE::NOE_UTILITY::sqlite::Database& ResourceManager::getUnderlying()
	{
		return m_database;
	}
}