
#include "nostraengine/core/ResourceManagement.hpp"

#if NOU_COMPILER == NOU_COMPILER_VISUAL_CPP
#     pragma warning(disable : 4996)
#endif

namespace NOE::NOE_CORE
{
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
				NOU::NOU_CORE::ErrorCodes::INVALID_OBJECT, "A resource with that ID does not exist.");
			return "__INVALID_ID__";
		}

		NOU::char8 sql[256] = { 0 };
		sprintf(sql, SQL_GENERIC.rawStr(), attribute.rawStr());

		auto stmt = ResourceManager::get().getUnderlying().execute(sql);
		stmt.bind(m_id);

		//there should always be a next
		NOE::NOE_UTILITY::sqlite::Row &row = stmt.next();

		if (!row.isNull(0))
			return row.valueAs(0, NOE::NOE_UTILITY::sqlite::STRING());
		else
			return "_NULL_";
	}

	NOU::boolean ResourceMetadata::checkIfExsists() const
	{
		if (m_removeUpdate >= ResourceManager::get().getResourceRemoveUpdates())
			//return true if id is not invalid; the resource is still in the database
			return m_id != INVALID_ID; 

		auto stmt = ResourceManager::get().getUnderlying().execute(SQL_EXISTS_RESOURCE);
		stmt.bind(m_id);

		NOE::NOE_UTILITY::sqlite::Row *row;

		if (stmt.hasNext())
			row = &stmt.next();
		else
		{
			//the latest update was checked
			m_removeUpdate = ResourceManager::get().getResourceRemoveUpdates();
			return false;
		}

		if (row->isValid())
		{
			NOU::int32 count = row->valueAs(0, NOE::NOE_UTILITY::sqlite::INTEGER());

			if (count == 0) //no type of that ID was found
			{
				//the latest update was checked
				m_removeUpdate = ResourceManager::get().getResourceRemoveUpdates();
				return false;
			}
		}
		else //the row is not valid
		{
			//the latest update was checked
			m_removeUpdate = ResourceManager::get().getResourceRemoveUpdates();
			return false;
		}

		//the latest update was checked
		m_removeUpdate = ResourceManager::get().getResourceRemoveUpdates();
		return true;
	}

	ResourceMetadata::ResourceMetadata(ID id) :
		m_id(id),
		/* 
		 * -1, to force isValid() (or checkIfExists() to be more precise) to check in the database for an 
		 * update
		 */
		m_removeUpdate(ResourceManager::get().getResourceRemoveUpdates() - 1)
	{
		//Check if the ID even exists in the database. If not, set it to INVALID_ID
		isValid();
	}

	typename ResourceMetadata::ID ResourceMetadata::getID() const
	{
		isValid(); //if necessary, set m_id to INVALID_ID

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

		return ResourceType();
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
}