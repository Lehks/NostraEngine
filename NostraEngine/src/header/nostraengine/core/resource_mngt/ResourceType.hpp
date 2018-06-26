#ifndef NOE_CORE_RESOURCE_TYPE_HPP
#define NOE_CORE_RESOURCE_TYPE_HPP

#include "nostraengine/core/StdIncludes.hpp"

/**
\file    core/resource_mngt/ResourceType.hpp
\author  Lukas Reichmann
\version 1.0.0
\since   0.0.1

\brief A file that contains the class ResourceType.
*/

namespace NOE::NOE_CORE
{
	/**
	\brief A class that represents a single resource type in the resources database.

	\details
	A class that represents a single resource type in the resources database. For a full tutorial on how to 
	use the resource management system, see \link resourceManagementSys this page\endlink.
	*/
	class ResourceType
	{
	public:
		/**
		\brief The type of a type ID.
		*/
		using ID = NOU::int32;

		/**
		\brief An ID that is invalid. An ID with this type must never be stored in a database.
		*/
		static constexpr ID INVALID_ID = 0;

		/**
		\brief A SQL statement that is able to check whether a type with a specified ID exists. (Or to be
		more precise, the statement returns the amount of types with the specified ID, which will either
		be one or zero).
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_EXISTS_TYPE;

		/**
		\brief A generic SQL command that gathers the value of an attribute of an object with a specified ID.
		The attribute's name and the object's ID can be modified.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_GENERIC;

		/**
		\brief The name of the "name" attribute in the Resources database.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_NAME_NAME;

		/**
		\brief The name of the "description" attribute in the Resources database.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_DESCRIPTION_NAME;

	private:
		/**
		\brief The ID of the type.
		*/
		mutable ID m_id; //mutable for isValid()
		
		/**
		\brief The value of ResourceManager::getTypeRemoveUpdates() from the last validity check.

		\details
		The value of ResourceManager::getTypeRemoveUpdates() from the last validity check. See 
		ResourceManager::m_typeRemoveUpdates for further information.
		*/
		mutable NOU::uint32 m_removeUpdate; //mutable for isValid()

		/**
		\param attribute The name of the attribute to get the value from.

		\return The value of the attribute.

		\brief Queries the value of the attribute \p attribute of the type.
		*/
		NOU::NOU_DAT_ALG::String8 getAttribute(const NOU::NOU_DAT_ALG::StringView8 &attribute) const;

		/**
		\return True, if the type exists, false if not.

		\brief Checks whether the type still exists in the database.
		*/
		NOU::boolean checkIfExsists() const;
	public:
		/**
		\param id The ID.

		\brief Constructs a new instance and initialized the member attributes with the passed ID.

		\note
		If the passed ID does not exist in the database, the ID will be set to INVALID_ID. If a resource with
		the original ID is created afterwards, the instances of this class that were before that will NOT be
		updated.
		*/
		NOU_FUNC explicit ResourceType(ID id = INVALID_ID);

		/**
		\return The ID of the type.

		\brief Returns the ID of the type. If the type is invalid (it does not exist), INVALID_ID is returned.
		*/
		NOU_FUNC ID getID() const;

		/**
		\return The name of the type.

		\brief Returns the name of the type.
		*/
		NOU_FUNC NOU::NOU_DAT_ALG::String8 getName() const;

		/**
		\return The description of the type.

		\brief Returns the description of the type.
		*/
		NOU_FUNC NOU::NOU_DAT_ALG::String8 getDescription() const;

		/**
		\return True, if the type is valid, false if not.

		\brief Returns whether the type is valid (it exists in the database) or not.
		*/
		NOU_FUNC NOU::boolean isValid() const;

		/**
		\return isValid()

		\brief Same as isValid()
		*/
		NOU_FUNC operator NOU::boolean() const;
	};

	constexpr typename ResourceType::ID ResourceType::INVALID_ID;
}

#endif