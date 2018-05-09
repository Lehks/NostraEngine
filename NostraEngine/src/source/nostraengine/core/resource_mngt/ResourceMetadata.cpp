
#include "nostraengine/core/ResourceManagement.hpp"

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
}