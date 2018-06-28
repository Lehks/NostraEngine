#ifndef NOE_UTILITY_SQLITE
#define NOE_UTILITY_SQLITE

#include "nostraengine/core/StdIncludes.hpp"

namespace NOE::NOE_UTILITY
{
	namespace sqlite
	{
		/**
		\brief The error codes that are used by the SQLlite interface.
		*/
		class ErrorCodes
		{
		public:
			enum
			{
				/**
				\brief Always the first element in the enum. This has only technical purposes and is not an
				       actual error code.
				*/
				FIRST_ELEMENT = 5000,

				/**
				\brief The database file could not be opened.
				*/
				CAN_NOT_OPEN_FILE,

				/**
				\brief A syntax error was found in an SQL statement.
				*/
				SQL_SYNTAX_ERROR,

				/**
				\brief SQLStatement::bind() was called too often for a single statement.
				*/
				SQL_INVALID_PARAMETER_INDEX,

				/**
				\brief Always the last element in the enum. This has only technical purposes and is not an
				actual error code.
				*/
				LAST_ELEMENT
			};
		};

		/**
		\brief The error pool that is used to provide the errors for the SQLite interfaces. This is barely
		       documented because it behaves according to the rules that are set up by 
			   nostra::utils::core::ErrorPool.
		*/
		class ErrorPool : public NOU::NOU_CORE::ErrorPool
		{
			NOU::NOU_CORE::Error m_errors[ErrorCodes::LAST_ELEMENT - ErrorCodes::FIRST_ELEMENT - 1];

		public:
			ErrorPool();

			virtual const NOU::NOU_CORE::Error* queryError(NOU::NOU_CORE::ErrorPool::ErrorType id) const;
		};

		/**
		\brief A dummy type that is used with SQLStatement::bind(). See the documentation of that function for
		       further information.
		*/
		struct INTEGER {};

		/**
		\brief A dummy type that is used with SQLStatement::bind(). See the documentation of that function for
		further information.
		*/
		struct INTEGER_64 {};

		/**
		\brief A dummy type that is used with SQLStatement::bind(). See the documentation of that function for
		further information.
		*/
		struct FLOAT {};

		/**
		\brief A dummy type that is used with SQLStatement::bind(). See the documentation of that function for
		further information.
		*/
		struct FLOAT_64 {};

		/**
		\brief A dummy type that is used with SQLStatement::bind(). See the documentation of that function for
		further information.
		*/
		struct STRING {};

		/**
		\brief The possible types of a cell in a Row.
		*/
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

		/**
		\brief A class that represents the last row that was queried by a SQLStatement.

		\details	
		A class that represents the last row that was queried by a SQLStatement. This class changes its state
		with each call to SQLStatement::next() and it will always only hold the information about the last
		row that was queried using that method.
		*/
		class Row
		{
		private:
			SQLStatement *m_stmt;
			NOU::boolean m_valid;

		public:
			NOU_FUNC Row(SQLStatement &stmt);

			NOU_FUNC NOU::int32 valueAs(NOU::sizeType index, INTEGER) const;

			NOU_FUNC NOU::int64 valueAs(NOU::sizeType index, INTEGER_64) const;

			NOU_FUNC NOU::float32 valueAs(NOU::sizeType index, FLOAT) const;

			NOU_FUNC NOU::float64 valueAs(NOU::sizeType index, FLOAT_64) const;

			NOU_FUNC NOU::NOU_DAT_ALG::StringView8 valueAs(NOU::sizeType index, STRING) const;

			NOU_FUNC NOU::boolean isNull(NOU::sizeType index) const;

			NOU_FUNC Type getType(NOU::sizeType index) const;

			NOU_FUNC NOU::sizeType size() const;

			NOU_FUNC void setValid(NOU::boolean valid);

			NOU_FUNC NOU::boolean isValid() const;

			NOU_FUNC NOU::int64 affectedRows() const;

			NOU_FUNC NOU::int64 lastRowId() const;
		};

		///\cond
		class Database;
		///\endcond

		class SQLStatement
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
			NOU_FUNC SQLStatement(Database &db, const NOU::NOU_DAT_ALG::StringView8 &sql);
			NOU_FUNC SQLStatement(Database &db);

			SQLStatement(const SQLStatement &other) = delete;
			NOU_FUNC SQLStatement(SQLStatement &&other);

			~SQLStatement();

			NOU_FUNC NOU::boolean isValid() const;
			
			NOU_FUNC void SQLStatement::bind(std::nullptr_t);

			NOU_FUNC void SQLStatement::bind(NOU::int32 i);

			NOU_FUNC void SQLStatement::bind(NOU::int32 *i);

			NOU_FUNC void SQLStatement::bind(NOU::int64 i);

			NOU_FUNC void SQLStatement::bind(NOU::int64 *i);

			NOU_FUNC void SQLStatement::bind(NOU::float32 f);

			NOU_FUNC void SQLStatement::bind(NOU::float32 *f);

			NOU_FUNC void SQLStatement::bind(NOU::float64 f);

			NOU_FUNC void SQLStatement::bind(NOU::float64 *f);

			NOU_FUNC void SQLStatement::bind(const NOU::NOU_DAT_ALG::StringView8 &str);

			NOU_FUNC void SQLStatement::bind(const NOU::NOU_DAT_ALG::StringView8 *str);

			NOU_FUNC Row& next();

			NOU_FUNC NOU::boolean hasNext();

			NOU_FUNC void* getUnderlying();

			NOU_FUNC Database& getDatabase();

			NOU_FUNC SQLStatement& operator = (SQLStatement &&other);
		};

		/**
		\brief A class that is capable of connecting to a SQLite3 database.
		*/
		class Database
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
			NOU_FUNC Database(const NOU::NOU_FILE_MNGT::Path &path);

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
			NOU_FUNC NOU::boolean open();

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
			NOU_FUNC NOU::boolean close();

			NOU_FUNC SQLStatement execute(const NOU::NOU_DAT_ALG::StringView8 &sql);

			//const QueryResult executeSQL(SQLStatement &sql);

			/**
			\return The path to the database file.

			\brief Returns the path to the database file.
			*/
			NOU_FUNC const NOU::NOU_FILE_MNGT::Path & getPath() const;

			/**
			\return True, if the connection is open, false if not.

			\brief Returns whether the connection to the database is established or not.
			*/
			NOU_FUNC NOU::boolean isOpen() const;

			/**
			\return The underlying database handle.

			\brief Returns the underlying database handle.
			*/
			NOU_FUNC void* getUnderlying();
		};
	}
}

#endif