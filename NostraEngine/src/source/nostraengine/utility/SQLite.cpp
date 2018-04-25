#include "nostraengine/utility/SQLite.hpp"

#include "SQLite3/sqlite3.h"

namespace NOE::NOE_UTILITY
{
	namespace sqlite
	{
#ifndef NOU_SQLITE_MAKE_ERROR
#define NOU_SQLITE_MAKE_ERROR(code) NOU::NOU_CORE::Error(#code, ErrorCodes::code)
#endif

		ErrorPool::ErrorPool() :
			m_errors //must be in order
			{
				NOU_SQLITE_MAKE_ERROR(SQL_SYNTAX_ERROR) ,
				NOU_SQLITE_MAKE_ERROR(SQL_INVALID_PARAMETER_INDEX)
			}
		{}

#undef NOU_SQLITE_MAKE_ERROR

		const NOU::NOU_CORE::Error* ErrorPool::queryError(NOU::NOU_CORE::ErrorPool::ErrorType id) const
		{
			if (id > ErrorCodes::FIRST_ELEMENT && id < ErrorCodes::LAST_ELEMENT)
			{
				NOU::sizeType index = id - ErrorCodes::FIRST_ELEMENT + 1;

				return m_errors + index;
			}
		}

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



		Row2::Row2(SQLStatement &stmt) :
			m_stmt(&stmt),
			m_valid(false)
		{}

		NOU::int32 Row2::valueAs(NOU::sizeType index, INTEGER)
		{
			return sqlite3_column_int(reinterpret_cast<sqlite3_stmt*>(m_stmt->get()), index);
		}

		NOU::int64 Row2::valueAs(NOU::sizeType index, INTEGER_64)
		{
			return sqlite3_column_int64(reinterpret_cast<sqlite3_stmt*>(m_stmt->get()), index);
		}

		NOU::float32 Row2::valueAs(NOU::sizeType index, FLOAT)
		{
			return sqlite3_column_double(reinterpret_cast<sqlite3_stmt*>(m_stmt->get()), index);
		}

		NOU::float64 Row2::valueAs(NOU::sizeType index, FLOAT_64)
		{
			return sqlite3_column_double(reinterpret_cast<sqlite3_stmt*>(m_stmt->get()), index);
		}

		NOU::NOU_DAT_ALG::StringView8 Row2::valueAs(NOU::sizeType index, STRING)
		{
			auto rawText = sqlite3_column_text(reinterpret_cast<sqlite3_stmt*>(m_stmt->get()), index);

			return reinterpret_cast<const NOU::char8*>(rawText);
		}

		NOU::boolean Row2::isNull(NOU::sizeType index)
		{
			return sqlite3_column_type(reinterpret_cast<sqlite3_stmt*>(m_stmt->get()), index) == SQLITE_NULL;
		}

		Type Row2::getType(NOU::sizeType index)
		{
			int type = sqlite3_column_type(reinterpret_cast<sqlite3_stmt*>(m_stmt->get()), index);

			switch (type)
			{
			case SQLITE_INTEGER:
				return Type::INTEGER;
			case SQLITE_FLOAT:
				return Type::FLOAT;
			case SQLITE_TEXT:
				return Type::STRING;
			default:
				return Type::UNKNOWN;
			}
		}

		NOU::sizeType Row2::size() const
		{
			return sqlite3_column_count(reinterpret_cast<sqlite3_stmt*>(m_stmt->get()));
		}

		void Row2::setValid(NOU::boolean valid)
		{
			m_valid = valid;
		}

		NOU::boolean Row2::isValid() const
		{
			return m_valid;
		}


		SQLStatement::SQLStatement(Database &db, const NOU::NOU_DAT_ALG::StringView8 &sql) :
			m_db(&db),
			m_sql(nullptr),
			m_nextIndex(1),
			m_state(State::NOT_STARTED),
			m_row(*this)
		{
			int error = sqlite3_prepare_v2(reinterpret_cast<sqlite3*>(m_db->getUnderlying()), sql.rawStr(),
				sql.size(), reinterpret_cast<sqlite3_stmt**>(&m_sql), nullptr);

			std::cout << sqlite3_errmsg(reinterpret_cast<sqlite3*>(m_db->getUnderlying())) << std::endl;

			if (error != SQLITE_OK)
			{
				NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), ErrorCodes::SQL_SYNTAX_ERROR, 
					"There was a syntax error in the SQL statement.");
			}
		}

		SQLStatement::SQLStatement(Database &db) :
			m_sql(nullptr),
			m_nextIndex(1),
			m_state(State::NOT_STARTED),
			m_row(*this)
		{}

		SQLStatement::SQLStatement(SQLStatement &&other) :
			m_sql(other.m_sql),
			m_nextIndex(other.m_nextIndex),
			m_state(other.m_state),
			m_row(*this)
		{
			other.m_sql = nullptr;
		}

		SQLStatement::~SQLStatement()
		{
			//no known errors
			sqlite3_finalize(reinterpret_cast<sqlite3_stmt*>(m_sql));
		}
		
		NOU::boolean SQLStatement::isValid() const
		{
			return m_sql != nullptr;
		}

		//helper function to reduce code duplication
		void setBindError(int error)
		{
			if (error != SQLITE_OK)
			{
				if (error == SQLITE_RANGE)
				{
					NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), ErrorCodes::SQL_INVALID_PARAMETER_INDEX,
						"There are no parameters left to bind.");
				}
				else
				{
					NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), NOU::NOU_CORE::ErrorCodes::UNKNOWN_ERROR,
						"An unknown error happened while binding a value.");
				}
			}
		}

		void SQLStatement::bind(std::nullptr_t)
		{
			if (m_state != State::NOT_STARTED)
				return;

			int error = sqlite3_bind_null(reinterpret_cast<sqlite3_stmt*>(m_sql), m_nextIndex);

			setBindError(error);

			m_nextIndex++;
		}

		void SQLStatement::bind(NOU::int32 i)
		{
			if (m_state != State::NOT_STARTED)
				return;

			int error = sqlite3_bind_int(reinterpret_cast<sqlite3_stmt*>(m_sql), m_nextIndex, i);

			setBindError(error);

			m_nextIndex++;
		}

		void SQLStatement::bind(NOU::int32 *i)
		{
			if (i == nullptr)
				bind(nullptr);
			else
				bind(*i);
		}

		void SQLStatement::bind(NOU::int64 i)
		{
			if (m_state != State::NOT_STARTED)
				return;

			int error = sqlite3_bind_int64(reinterpret_cast<sqlite3_stmt*>(m_sql), m_nextIndex, i);

			setBindError(error);

			m_nextIndex++;
		}

		void SQLStatement::bind(NOU::int64 *i)
		{
			if (i == nullptr)
				bind(nullptr);
			else
				bind(*i);
		}

		void SQLStatement::bind(NOU::float32 f)
		{
			if (m_state != State::NOT_STARTED)
				return;

			bind(static_cast<NOU::float64>(f)); //there is no sqlite3 bind for float32
		}

		void SQLStatement::bind(NOU::float32 *f)
		{
			if (f == nullptr)
				bind(nullptr);
			else
				bind(*f);
		}

		void SQLStatement::bind(NOU::float64 f)
		{
			if (m_state != State::NOT_STARTED)
				return;

			int error = sqlite3_bind_double(reinterpret_cast<sqlite3_stmt*>(m_sql), m_nextIndex, f);

			setBindError(error);

			m_nextIndex++;
		}

		void SQLStatement::bind(NOU::float64 *f)
		{
			if (f == nullptr)
				bind(nullptr);
			else
				bind(*f);
		}

		void SQLStatement::bind(const NOU::NOU_DAT_ALG::StringView8 &str)
		{
			if (m_state != State::NOT_STARTED)
				return;

			int error = sqlite3_bind_text(reinterpret_cast<sqlite3_stmt*>(m_sql), m_nextIndex, 
				str.rawStr(), str.size(), SQLITE_TRANSIENT);

			setBindError(error);

			m_nextIndex++;
		}

		void SQLStatement::bind(const NOU::NOU_DAT_ALG::StringView8 *str)
		{
			if (str == nullptr)
				bind(nullptr);
			else
				bind(*str); 
		}

		Row2& SQLStatement::next()
		{
			int error = sqlite3_step(reinterpret_cast<sqlite3_stmt*>(m_sql));

			m_state = State::IN_PROGRESS;

			if (error == SQLITE_DONE)
			{
				m_state = State::DONE;
				m_row.setValid(true);
			}
			else if (error != SQLITE_ROW)
				m_row.setValid(false);
			else
				m_row.setValid(true);

			return m_row;
		}

		NOU::boolean SQLStatement::hasNext()
		{
			return m_state != State::DONE;
		}

		void* SQLStatement::get()
		{
			return m_sql;
		}

		SQLStatement& SQLStatement::operator = (SQLStatement &&other)
		{
			//no known errors occur
			sqlite3_finalize(reinterpret_cast<sqlite3_stmt*>(m_sql));

			m_sql = other.m_sql;
			m_nextIndex = other.m_nextIndex;
			m_state = other.m_state;

			other.m_sql = nullptr;

			return *this;
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
			
			sqlite3_extended_result_codes(reinterpret_cast<sqlite3*>(m_dbPtr), true);
			
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

			int error = sqlite3_close_v2(reinterpret_cast<sqlite3*>(m_dbPtr));

			if (error == SQLITE_OK)
			{
				return true;
			}
			else if (error == SQLITE_BUSY)
			{
				NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
					NOU::NOU_CORE::ErrorCodes::INVALID_STATE,
					"The database is being used by someone else right now.");
				return false;
			}
			else
			{
				NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
					NOU::NOU_CORE::ErrorCodes::UNKNOWN_ERROR,
					"An unknown error occurred while closing a database.");
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

		SQLStatement Database::execute(const NOU::NOU_DAT_ALG::StringView8 &sql)
		{
			if (!isOpen())
			{
				NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
					NOU::NOU_CORE::ErrorCodes::INVALID_STATE,
					"Database is not opened.");

				return SQLStatement(*this);
			}

			return SQLStatement(*this, sql);
		}

		/*const QueryResult Database::executeSQL(SQLStatement &sql)
		{
			sqlite3_stmt *stmt = reinterpret_cast<sqlite3_stmt*>(sql.get());

			QueryResult result(-1, nullptr);

			int error;

			while ((error = sqlite3_step(stmt)) != SQLITE_DONE)
			{
				if (error == SQLITE_ROW)
				{
					NOU::sizeType colCount = sqlite3_column_count(stmt);

					for (NOU::sizeType i = 0; i < colCount; i++)
					{

					}
				}
			}
		}*/

		const NOU::NOU_FILE_MNGT::Path & Database::getPath() const
		{
			return m_path;
		}

		NOU::boolean Database::isOpen() const
		{
			return m_dbPtr != nullptr;
		}

		void* Database::getUnderlying()
		{
			return m_dbPtr;
		}
	}
}