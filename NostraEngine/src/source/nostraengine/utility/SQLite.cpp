#include "nostraengine/utility/SQLite.hpp"

#include "SQLite3/sqlite3.h"

namespace NOE::NOE_UTILITY
{
	namespace sqlite
	{
		RowEntry::RowEntry(const NOU::char8 *value, const NOU::NOU_DAT_ALG::StringView8 &name) :
			//do not initialize m_value here
			m_name(name)
		{
			if (value != nullptr)
				m_value = value;
		}

		const NOU::NOU_DAT_ALG::String8* RowEntry::getValue() const
		{
			return m_value.isValid() ? m_value.data() : nullptr;
		}

		const NOU::NOU_DAT_ALG::String8& RowEntry::getName() const
		{
			return m_name;
		}

		void Row::addEntry(const RowEntry &entry)
		{
			m_entires.pushBack(entry);
		}

		const NOU::NOU_DAT_ALG::Vector<RowEntry>& Row::getEntries() const
		{
			return m_entires;
		}

		QueryResult::QueryResult(NOU::int32 affectedRows, NOU::char8 *error) :
			m_valid(true),
			m_error(error == nullptr ? "" : error),
			m_affectedRows(affectedRows)
		{}

		void QueryResult::setValid(NOU::boolean valid)
		{
			m_valid = valid;
		}

		void QueryResult::addRow(const Row &row)
		{
			m_rows.pushBack(row);
		}

		NOU::boolean QueryResult::isValid() const
		{
			return m_valid;
		}

		const NOU::NOU_DAT_ALG::Vector<Row>& QueryResult::getRows() const
		{
			return m_rows;
		}

		NOU::NOU_DAT_ALG::StringView8 QueryResult::getErrorMsg() const
		{
			return m_error;
		}

		void QueryResult::setAffectedRows(NOU::int32 rows)
		{
			m_affectedRows = rows;
		}

		NOU::int32 QueryResult::getAffectedRows() const
		{
			return m_affectedRows;
		}



		int Database::sqlCallback(void *data, int cellCount, char **values, char **names)
		{
			QueryResult *result = reinterpret_cast<QueryResult*>(data);

			Row row;

			for (NOU::sizeType i = 0; i < cellCount; i++)
			{
				row.addEntry(RowEntry(values[i], names[i]));
			}

			result->addRow(row);

			return 0;
		}

		Database::Database(const NOU::NOU_FILE_MNGT::Path &path) :
			m_dbPtr(nullptr),
			m_path(path)
		{}

		NOU::boolean Database::open()
		{
			int error = sqlite3_open(m_path.getAbsolutePath().rawStr(), 
				reinterpret_cast<sqlite3**>(&m_dbPtr));

			if (error == SQLITE_OK)
			{
				return true;
			}
			else
			{
				if (error == SQLITE_CANTOPEN)
				{
					switch (sqlite3_extended_errcode(reinterpret_cast<sqlite3*>(m_dbPtr)))
					{
					case SQLITE_CANTOPEN_ISDIR:
						NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
							NOU::NOU_CORE::ErrorCodes::CANNOT_OPEN_FILE,
							"The passed path leads to a directory.");
						return false;

						//Should never happen, since noe will always pass the full path (and this only 
						//happens with relative ones)
					case SQLITE_CANTOPEN_FULLPATH:
						NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
							NOU::NOU_CORE::ErrorCodes::UNKNOWN_ERROR,
							"An unknown error occurred while opening a database.");
						return false;
					}
				}
				else if(error == SQLITE_NOTADB)
				{
					NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
						NOU::NOU_CORE::ErrorCodes::CANNOT_OPEN_FILE,
						"The passed path leads to a files, but the file does not contain a database.");
					return false;
				}
				else
				{
					NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
						NOU::NOU_CORE::ErrorCodes::UNKNOWN_ERROR,
						"An unknown error occurred while opening a database.");
					return false;
				}
			}
		}

		NOU::boolean Database::close()
		{
			if (!isOpen())
			{
				NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
					NOU::NOU_CORE::ErrorCodes::INVALID_STATE,
					"Database is not opened.");
				return false;
			}

			int error = sqlite3_close(reinterpret_cast<sqlite3*>(m_dbPtr));

			if (error == SQLITE_OK)
			{
				return true;
			}
			else
			{
				NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
					NOU::NOU_CORE::ErrorCodes::UNKNOWN_ERROR,
					"An unknown error occurred while opening a database.");
				return false;
			}
		}

		const QueryResult Database::executeSQL(const NOU::NOU_DAT_ALG::StringView8 &sql)
		{
			if (!isOpen())
			{
				NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
					NOU::NOU_CORE::ErrorCodes::INVALID_STATE,
					"Database is not opened.");

				QueryResult ret(-1);
				ret.setValid(false);
				return NOU::NOU_CORE::move(ret);
			}

			QueryResult ret(-1);

			NOU::char8 *errmsg;

			int error = sqlite3_exec(reinterpret_cast<sqlite3*>(m_dbPtr), sql.rawStr(), sqlCallback, 
				&ret, &errmsg);

			ret.setAffectedRows(sqlite3_changes(reinterpret_cast<sqlite3*>(m_dbPtr)));

			if (errmsg != nullptr) //if an error happened
			{
				QueryResult errRet(-1, errmsg);

				sqlite3_free(errmsg);

				errRet.setValid(false);
				return NOU::NOU_CORE::move(errRet);
			}
			
			if (error != SQLITE_OK)
			{
				NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
					NOU::NOU_CORE::ErrorCodes::UNKNOWN_ERROR,
					"An unknown error occurred while executing an SQL statement.");
			}

			return NOU::NOU_CORE::move(ret);
		}

		const NOU::NOU_FILE_MNGT::Path & Database::getPath() const
		{
			return m_path;
		}

		NOU::boolean Database::isOpen() const
		{
			return m_dbPtr != nullptr;
		}
	}
}