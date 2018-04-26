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

		class NOU_CLASS Row
		{
		private:
			SQLStatement *m_stmt;
			NOU::boolean m_valid;

		public:
			Row(SQLStatement &stmt);

			NOU::int32 valueAs(NOU::sizeType index, INTEGER) const;

			NOU::int64 valueAs(NOU::sizeType index, INTEGER_64) const;

			NOU::float32 valueAs(NOU::sizeType index, FLOAT) const;

			NOU::float64 valueAs(NOU::sizeType index, FLOAT_64) const;

			NOU::NOU_DAT_ALG::StringView8 valueAs(NOU::sizeType index, STRING) const;

			NOU::boolean isNull(NOU::sizeType index) const;

			Type getType(NOU::sizeType index) const;

			NOU::sizeType size() const;

			void setValid(NOU::boolean valid);

			NOU::boolean isValid() const;

			NOU::int64 affectedRows() const;

			NOU::int64 lastRowId() const;
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
			Row m_row;

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

			Row& next();

			NOU::boolean hasNext();

			void* getUnderlying();

		    Database& getDatabase();

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