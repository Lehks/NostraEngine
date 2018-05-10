
#include "nostraengine/core/ResourceManagement.hpp"

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
			return "NULL";
	}

	NOU::boolean ResourceType::checkIfExsists() const
	{
		if (m_removeUpdate >= ResourceManager::get().getTypeRemoveUpdates())
			//return true if id is not invalid; the resource is still in the database
			return m_id != INVALID_ID;

		auto stmt = ResourceManager::get().getUnderlying().execute(SQL_EXISTS_TYPE);
		stmt.bind(m_id);

		NOE::NOE_UTILITY::sqlite::Row *row;

		if (stmt.hasNext())
			row = &stmt.next();
		else
		{
			//the latest update was checked
			m_removeUpdate = ResourceManager::get().getTypeRemoveUpdates();
			return false;
		}

		if (row->isValid())
		{
			NOU::int32 count = row->valueAs(0, NOE::NOE_UTILITY::sqlite::INTEGER());

			if (count == 0) //no type of that ID was found
			{
				//the latest update was checked
				m_removeUpdate = ResourceManager::get().getTypeRemoveUpdates();
				return false;
			}
		}
		else //the row is not valid
		{
			//the latest update was checked
			m_removeUpdate = ResourceManager::get().getTypeRemoveUpdates();
			return false;
		}

		//the latest update was checked
		m_removeUpdate = ResourceManager::get().getTypeRemoveUpdates();
		return true;
	}

	ResourceType::ResourceType(ID id) :
		m_id(id),
		/*
		* -1, to force isValid() (or checkIfExists() to be more precise) to check in the database for an
		* update
		*/
		m_removeUpdate(ResourceManager::get().getTypeRemoveUpdates() - 1)
	{
		//Check if the ID even exists in the database. If not, set it to INVALID_ID
		isValid();
	}

	typename ResourceType::ID ResourceType::getID() const
	{
		isValid(); //if necessary, set m_id to INVALID_ID

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
}