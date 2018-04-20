#include "nostraengine/core/StdIncludes.hpp"

namespace NOE::NOE_UTILITY
{
	namespace sqlite
	{
		/**
		\brief Defines a value-name pair.
		*/
		NOU_DEFINE_PAIR(RowEntryTempl, value, name);

		/**
		\brief Instantiates the RowEntryTempl template with a String8 as both parameters.

		\details
		Instantiates the RowEntryTempl template with a String8 as both parameters. 

		The single parameters are:
		- value: The value of the cell
		- name: The name of the column that the cell is in.
		*/
		using RowEntry = RowEntryTempl<NOU::NOU_DAT_ALG::String8, NOU::NOU_DAT_ALG::String8>;

		/**
		\brief Represents a single row of a SQL query. A row consists single RowEntries.
		*/
		class NOU_CLASS Row
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
		class NOU_CLASS QueryResult
		{
		private:
			/**
			\brief The single rows in the result.
			*/
			NOU::NOU_DAT_ALG::Vector<Row> m_rows;

		public:
			/**
			\param row The row to add.

			\brief Adds a row to the row. This method is usually not used by a user.
			*/
			void addRow(const Row &row);

			/**
			\return The rows.

			\brief Returns the rows.
			*/
			const NOU::NOU_DAT_ALG::Vector<Row>& getRows() const;
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
		};
	}
}