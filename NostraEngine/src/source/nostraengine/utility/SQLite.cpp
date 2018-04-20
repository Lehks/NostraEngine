#include "nostraengine/utility/SQLite.hpp"

#include "SQLite3/sqlite3.h"

namespace NOE::NOE_UTILITY
{
	namespace sqlite
	{
		void Row::addEntry(const RowEntry &entry)
		{
			m_entires.pushBack(entry);
		}

		const NOU::NOU_DAT_ALG::Vector<RowEntry>& Row::getEntries() const
		{
			return m_entires;
		}

		void QueryResult::addRow(const Row &row)
		{
			m_rows.pushBack(row);
		}

		const NOU::NOU_DAT_ALG::Vector<Row>& QueryResult::getRows() const
		{
			return m_rows;
		}

		int Database::sqlCallback(void *data, int cellCount, char **values, char **names)
		{
			QueryResult *result = reinterpret_cast<QueryResult*>(data);

			Row row;

			for (NOU::sizeType i = 0; i < cellCount; i++)
				row.addEntry(RowEntry(values[i], names[i]));

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
				return QueryResult();
			}

			QueryResult ret;

			int error = sqlite3_exec(reinterpret_cast<sqlite3*>(m_dbPtr), sql.rawStr(), sqlCallback, 
				&ret, nullptr);

			///\todo Proper setting of different error codes.

			if (error != SQLITE_OK)
			{
				NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
					NOU::NOU_CORE::ErrorCodes::UNKNOWN_ERROR,
					"An unknown error occurred while opening a database.");
			}

			return ret;
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