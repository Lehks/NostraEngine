#ifndef NOE_CORE_RESOURCE_METADATA_HPP
#define NOE_CORE_RESOURCE_METADATA_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/resource_mngt/ResourceType.hpp"

/**
\file    core/resource_mngt/ResourceMetadata.hpp
\author  Lukas Reichmann
\version 1.0.0
\since   0.0.1

\brief A file that contains the class ResourceMetadata.
*/

namespace NOE::NOE_CORE
{
	/**
	\brief A class that can be used to read the meta data of a single resource.

	\details
	A class that can be used to read the meta data of a single resource. For a full tutorial on how to use the
	resource management system, see \link resourceManagementSys this page\endlink.
	*/
	class ResourceMetadata
	{
	public:

		/**
		\brief The type of a resource ID.
		*/
		using ID = NOU::int32;

		/**
		\brief An ID that is invalid. An ID with this type must never be stored in a database.
		*/
		static constexpr ID INVALID_ID = 0;

		/**
		\brief A generic SQL command that gathers the value of an attribute of an object with a specified ID.
		The attribute's name and the object's ID can be modified.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_GENERIC;

		/**
		\brief The name of the "type" attribute in the Resources database.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_TYPE_NAME;

		/**
		\brief The name of the "path" attribute in the Resources database.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_PATH_NAME;

		/**
		\brief The name of the "cached" attribute in the Resources database.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_CACHED_PATH_NAME;

		/**
		\brief A SQL statement that is able to check whether a resource with a specified ID exists. (Or to be
		more precise, the statement returns the amount of resources with the specified ID, which will either
		be one or zero).
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_EXISTS_RESOURCE;

	private:
		/**
		\brief The ID of the resource.
		*/
		mutable ID m_id; //mutable for isValid()
		
		/**
		\brief The value of ResourceManager::getResourceRemoveUpdates() from the last validity check.

		\details
		The value of ResourceManager::getResourceRemoveUpdates() from the last validity check. See 
		ResourceManager::m_resourceRemoveUpdates for further information.
		*/
		mutable NOU::int32 m_removeUpdate; //mutable for isValid()

		/**
		\param attribute The name of the attribute to get the value from.

		\return The value of the attribute.

		\brief Queries the value of the attribute \p attribute of the resource that is associated with this
		meta data.
		*/
		NOU::NOU_DAT_ALG::String8 getAttribute(const NOU::NOU_DAT_ALG::StringView8 &attribute) const;

		/**
		\return True, if the resource exists, false if not.

		\brief Checks whether the resource still exists in the database.
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
		NOU_FUNC explicit ResourceMetadata(ID id = INVALID_ID);

		/**
		\return The ID of the resource.

		\brief Returns the ID of the resource. If the resource is invalid (it does not exist), INVALID_ID is
		       returned.
		*/
		NOU_FUNC ID getID() const;

		/**
		\return The type of the resource.

		\brief Returns the type of the resource.
		*/
		NOU_FUNC ResourceType getType() const;

		/**
		\return The path to the source file of the resource.

		\brief Returns the path to the source file of the resource.
		*/
		NOU_FUNC NOU::NOU_FILE_MNGT::Path getPath() const;

		/**
		\return True, if the resource is cached and false if not.

		\brief Returns whether the resource is cached or not.
		*/
		NOU_FUNC NOU::boolean isCached() const;

		/**
		\return The path the cache file.

		\brief Returns the path to the cache file.

		\warning
		The result of this method is only valid if <tt>isCached()</tt> returns true.
		*/
		NOU_FUNC NOU::NOU_FILE_MNGT::Path getCachePath() const;

		/**
		\return True, if the meta data is valid, false if not.

		\brief Returns whether the meta data is valid or not.
		*/
		NOU_FUNC NOU::boolean isValid() const;

		/**
		\return isValid()

		\brief Same as isValid()
		*/
		NOU_FUNC operator NOU::boolean() const;
	};

	constexpr ResourceMetadata::ID ResourceMetadata::INVALID_ID;
}

#endif