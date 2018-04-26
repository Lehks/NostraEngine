#ifndef NOE_UTILITY_SQLITE
#define NOE_UTILITY_SQLITE

#include "nostraengine/core/StdIncludes.hpp"

namespace NOE::NOE_UTILITY
{
	namespace sqlite
	{
		class ErrorCodes
		{
		public:
			enum
			{
				FIRST_ELEMENT = 5000,

				SQL_SYNTAX_ERROR,
				SQL_INVALID_PARAMETER_INDEX,

				LAST_ELEMENT
			};
		};

		class ErrorPool : public NOU::NOU_CORE::ErrorPool
		{
			NOU::NOU_CORE::Error m_errors[ErrorCodes::LAST_ELEMENT - ErrorCodes::FIRST_ELEMENT - 1];

		public:
			ErrorPool();

			virtual const NOU::NOU_CORE::Error* queryError(NOU::NOU_CORE::ErrorPool::ErrorType id) const;
		};

		/**
		\brief A class that represents a single cell in a database table. It stores the value of the cell and
		       the name of the column that the cell is in.
		*/
		class NOU_CLASS RowEntry final
		{
		private:
			/**
			\brief The value of the cell. If the value is NULL in the database, the member will not be
			       initialized.
			*/
			NOU::NOU_DAT_ALG::Uninitialized<NOU::NOU_DAT_ALG::String8> m_value;

			/**
			\brief The name of the column.
			*/
			NOU::NOU_DAT_ALG::String8 m_name;

		public:
			/**
			\param value The value of the self. It will be copied, unless the value is \p nullptr.
			*/
			RowEntry(const NOU::char8 *value, const NOU::NOU_DAT_ALG::StringView8 &name);

			/**
			\return The value of the cell.

			\brief Returns a pointer to the value of the cell. If the value is NULL in the database, \p
			       nullptr is returned.
			*/
			const NOU::NOU_DAT_ALG::String8* getValue() const;

			/**
			\return The name of the column that this cell is in.

			\brief Returns the name of the column that this cell is in.
			*/
			const NOU::NOU_DAT_ALG::String8& getName() const;
		};

		/**
		\brief Represents a single row of a SQL query. A row consists single RowEntries.
		*/
		class NOU_CLASS Row final
		{
		private:
			/**
			\brief The single entries in the row.
			*/
			NOU::NOU_DAT_ALG::Vector<RowEntry> m_entires;

		public:
			/**
			\param entry The entry to add.

			\brief Adds an entry to the row. This method is usually not used by a user.
			*/
			void addEntry(const RowEntry &entry);

			/**
			\return The entries.

			\brief Returns the entires.
			*/
			const NOU::NOU_DAT_ALG::Vector<RowEntry>& getEntries() const;
		};

		/**
		\brief Represents the result of an entire SQL query as a list of the queried rows.
		*/
		class NOU_CLASS QueryResult final
		{
		private:
			/**
			\brief The single rows in the result.
			*/
			NOU::NOU_DAT_ALG::Vector<Row> m_rows;

			/**
			\brief True, if the result is valid, false if not.
			*/
			NOU::boolean m_valid;

			/**
			\brief If the result is invalid, this string will contain further information about the error.
			*/
			NOU::NOU_DAT_ALG::String8 m_error;

			/**
			\brief The amount of rows that were affected by the query. Only valid for INSERT, UPDATE or DELETE
			       operations.
			*/
			NOU::int32 m_affectedRows;

		public:
			/**
			\brief Constructs a new instance.
			*/
			QueryResult(NOU::int32 affectedRows, NOU::char8 *error = nullptr);

			/**
			\param valid The new valid state.

			\brief Sets the valid state.
			*/
			void setValid(NOU::boolean valid);

			/**
			\param row The row to add.

			\brief Adds a row to the row. This method is usually not used by a user.
			*/
			void addRow(const Row &row);

			/**
			\return True, if the result is valid, false if not.

			\brief Returns whether the result is valid.
			*/
			NOU::boolean isValid() const;

			/**
			\return The rows.

			\brief Returns the rows.
			*/
			const NOU::NOU_DAT_ALG::Vector<Row>& getRows() const;

			/**
			\return The error message that was produced by the database on failure.

			\brief Returns the error message that was produced by the database on failure, or an empty string 
			       if there was no error.
			*/
			NOU::NOU_DAT_ALG::StringView8 getErrorMsg() const;

			/**
			\param rows The new amount of affected rows.

			\brief Sets the affected rows. 
			*/
			void setAffectedRows(NOU::int32 rows);

			/**
			\return The amount of rows that were affected by the query.

			\brief Returns the amount of rows that were affected by the query that produced this result. 

			\note
			This value is only valid for INSERT, UPDATE or DELETE operations, otherwise the value is 
			undefined.
			*/
			NOU::int32 getAffectedRows() const;
		};

		struct INTEGER {};
		struct INTEGER_64 {};
		struct FLOAT {};
		struct FLOAT_64 {};
		struct STRING {};

		enum class Type
		{
			INTEGER,
			FLOAT,
			STRING,
			UNKNOWN
		};

		///\cond
		class SQLStatement;
		///\endcond

		class NOU_CLASS Row2
		{
		private:
			SQLStatement *m_stmt;
			NOU::boolean m_valid;

		public:
			Row2(SQLStatement &stmt);

			NOU::int32 valueAs(NOU::sizeType index, INTEGER);

			NOU::int64 valueAs(NOU::sizeType index, INTEGER_64);

			NOU::float32 valueAs(NOU::sizeType index, FLOAT);

			NOU::float64 valueAs(NOU::sizeType index, FLOAT_64);

			NOU::NOU_DAT_ALG::StringView8 valueAs(NOU::sizeType index, STRING);

			NOU::boolean isNull(NOU::sizeType index);

			Type getType(NOU::sizeType index);

			NOU::sizeType size() const;

			void setValid(NOU::boolean valid);

			NOU::boolean isValid() const;
		};

		///\cond
		class Database;
		///\endcond

		class NOU_CLASS SQLStatement
		{
		private:
			enum class State
			{
				NOT_STARTED,
				IN_PROGRESS,
				DONE
			};

			Database *m_db;
			void *m_sql;
			NOU::sizeType m_nextIndex;
			State m_state;
			Row2 m_row;

		public:
			SQLStatement(Database &db, const NOU::NOU_DAT_ALG::StringView8 &sql);
			SQLStatement(Database &db);

			SQLStatement(const SQLStatement &other) = delete;
			SQLStatement(SQLStatement &&other);

			~SQLStatement();

			NOU::boolean isValid() const;
			
			void SQLStatement::bind(std::nullptr_t);

			void SQLStatement::bind(NOU::int32 i);

			void SQLStatement::bind(NOU::int32 *i);

			void SQLStatement::bind(NOU::int64 i);

			void SQLStatement::bind(NOU::int64 *i);

			void SQLStatement::bind(NOU::float32 f);

			void SQLStatement::bind(NOU::float32 *f);

			void SQLStatement::bind(NOU::float64 f);

			void SQLStatement::bind(NOU::float64 *f);

			void SQLStatement::bind(const NOU::NOU_DAT_ALG::StringView8 &str);

			void SQLStatement::bind(const NOU::NOU_DAT_ALG::StringView8 *str);

			Row2& next();

			NOU::boolean hasNext();

			void* get();

			SQLStatement& operator = (SQLStatement &&other);
		};

		/**
		\brief A class that is capable of connecting to a SQLite3 database.
		*/
		class NOU_CLASS Database
		{
		private:
			/**
			\brief The pointer to the opened database.
			*/
			void *m_dbPtr; //define as void, to avoid the inclusion of sqlite3.h

			/**
			\brief The path to the database file.
			*/
			NOU::NOU_FILE_MNGT::Path m_path;

			/**
			\param data      Custom data that was passed to sqlite3_exec() (the third parameter).
			\param cellCount The amount of cells in the row (aka the size of both \p values and \p names).
			\param values    The single values of the cells in the row.
			\param names     The single names of the columns.

			\brief A callback that will be called by the SQLite interface for each queried row.

			\return 0
			*/
			static int sqlCallback(void *data, int cellCount, char **values, char **names);

		public:
			/**
			\param path The path to the database file.

			\brief Constructs a new instance with the passed path. This does not establish a database
				   connection yet.
			*/
			Database(const NOU::NOU_FILE_MNGT::Path &path);

			/**
			\return True, if the operation was successful, false if not.

			\brief Establishes a connection to the database. 

			\details
			Establishes a connection to the database. If the database file does not exist yet, it will be
			created.

			On failure (false is returned), an error will be pushed to the error handler. The possible errors 
			are:
			- nostra::utils::core::ErrorCodes::CANNOT_OPEN_FILE: The file could not be opened; it is either a
			  directory or not a database at all (the error message will hold further information).
			- nostra::utils::core::ErrorCodes::UNKNOWN_ERROR: An unknown error occurred.
			*/
			NOU::boolean open();

			/**
			\return True, if the operation was successful, false if not.

			\brief Closes a connection to the database and saves the changes.

			\details
			Closes a connection to the database.

			On failure (false is returned), an error will be pushed to the error handler. The possible errors
			are:
			- nostra::utils::core::ErrorCodes::INVALID_STATE: The connection to the database was not created 
			  (open() was not called).
			- nostra::utils::core::ErrorCodes::UNKNOWN_ERROR: An unknown error occurred.
			*/
			NOU::boolean close();

			/**
			\param sql The SQL source code to execute.

			\return The result of the SQL query. If the query is empty, the operation might have failed. See 
			        the detailed section for further information.

			\brief Executes one or more SQL statements and returns the result.

			\details
			Executes one or more SQL statements and returns the result.

			On failure, an empty QueryResult is returned and an error will be pushed to the error handler 
			(note that, depending on the SQL query, the QueryResult my be empty without any errors). The
			possible errors are:
			- nostra::utils::core::ErrorCodes::UNKNOWN_ERROR: An unknown error occurred.
			*/
			const QueryResult executeSQL(const NOU::NOU_DAT_ALG::StringView8 &sql);

			SQLStatement execute(const NOU::NOU_DAT_ALG::StringView8 &sql);

			//const QueryResult executeSQL(SQLStatement &sql);

			/**
			\return The path to the database file.

			\brief Returns the path to the database file.
			*/
			const NOU::NOU_FILE_MNGT::Path & getPath() const;

			/**
			\return True, if the connection is open, false if not.

			\brief Returns whether the connection to the database is established or not.
			*/
			NOU::boolean isOpen() const;

			/**
			\return The underlying database handle.

			\brief Returns the underlying database handle.
			*/
			void* getUnderlying();
		};
	}
}

#endif