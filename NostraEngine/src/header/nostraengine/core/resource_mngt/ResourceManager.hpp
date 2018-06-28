#ifndef NOE_CORE_RESOURCE_MANAGER_HPP
#define NOE_CORE_RESOURCE_MANAGER_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/resource_mngt/ResourceMetadata.hpp"
#include "nostraengine/core/resource_mngt/ResourceType.hpp"
#include "nostraengine/core/resource_mngt/Resource.hpp"
#include "nostraengine/core/resource_mngt/ResourceLoader.hpp"
#include "nostraengine/utility/SQLite.hpp"

/**
\file    core/resource_mngt/ResourceManager.hpp
\author  Lukas Reichmann
\version 1.0.0
\since   0.0.1

\brief A file that contains the class ResourceManager.
*/

namespace NOE::NOE_CORE
{
	/**
	\brief The central class of the resource management system of the engine. 

	\details 
	The central class of the resource management system of the engine. For a full tutorial on how to use the 
	resource management system, see \link resourceManagementSys this page\endlink.
	*/
	class ResourceManager final
	{
	private:
		/**
		\brief The default path to the database file.
		*/
		static NOU::NOU_FILE_MNGT::Path DATABASE_PATH;

		/**
		\brief The SQL code to query all IDs in the database. This is used by listMetadata().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_LIST_IDS;

		/**
		\brief The SQL code to add a resource to the database. This is used by addResource().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_ADD_RESOURCE;

		/**
		\brief The SQL code to add a type to the database. This is used by addType().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_ADD_TYPE;

		/**
		\brief The SQL code to remove a resource from the database. This is used by removeResource().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_REMOVE;

		/**
		\brief The SQL code to update the cache state of a resource. This is used by cache().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_UPDATE_CACHE;

		/**
		\brief The SQL code to create the table "Resources" in the resources database if it does not exist 
		yet. This is used by initialize().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_CREATE_TABLE_RESOURCES;

		/**
		\brief The SQL code to create the table "Types" in the resources database if it does not exist 
		yet. This is used by initialize().
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_CREATE_TABLE_TYPES;

		/**
		\brief The name of the table "Resources".
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_TABLENAME_RESOURCES;

		/**
		\brief The name of the table "Types".
		*/
		static const NOU::NOU_DAT_ALG::StringView8 SQL_TABLENAME_TYPES;

		/**
		\brief The database that is used by the resource manager.
		*/
		NOE::NOE_UTILITY::sqlite::Database m_database;

		/**
		\brief A list of the loaders that were added to the manager.
		*/
		NOU::NOU_DAT_ALG::HashMap<NOU::NOU_DAT_ALG::String8, ResourceLoader*> m_loaders;

		/**
		\brief The counter for the removes of types.

		\details
		The counter for the removes of types. This counter is used to help the class ResourceMetadata check
		if the resource that is associated with it still exists or not.

		The concept is the following:
		Each time that a type is removed from the database, this counter is increased. In addition to that, 
		the ResourceType will store a value of the same type as this. If a ResourceType instance is being 
		constructed, it will do an initial validity check and then set its internal counter to the same value 
		as this variable. 

		As soon as the ResourceType instance needs to do another validity check, it will first check whether 
		the value of this variable is bigger the value of its internal counter. If so, a remove operation was 
		done and the type may be invalid. After the check is done, the counter of the ResourceType instance 
		will be set to the value of this variable yet again.
		*/
		NOU::uint32 m_typeRemoveUpdates; //must start at 1!
		
		/**
		\brief The counter for the removes of resources.

		\details
		The counter for the removes of resources. This counter is used to help the class ResourceMetadata 
		check if the resource that is associated with it still exists or not.

		The concept is the following:
		Each time that a resources is removed from the database, this counter is increased. In addition to 
		that, the ResourceMetadata will store a value of the same type as this. If a ResourceMetadata instance
		is being constructed, it will do an initial validity check and then set its internal counter to the
		same value as this variable. 

		As soon as the ResourceMetadata instance needs to do another validity check, it will first check
		whether the value of this variable is bigger the value of its internal counter. If so, a remove
		operation was done and the resource may be invalid. After the check is done, the counter of the 
		ResourceMetadata instance will be set to the value of this variable yet again.
		*/
		NOU::uint32 m_resourceRemoveUpdates; //must start at 1!

		/**
		\tparam T    The type resource loader to add. This must be a child class of ResourceLoader.
		\tparam ARGS The types of the parameters that will be passed to the constructor of the resource
		loader.

		\param args The parameters that will be passed to the constructor of the resource loader.

		\return The constructed loader.

		\brief Allocates a new ResourceLoader of the type T.
		*/
		template<typename T, typename ...ARGS>
		static ResourceLoader* allocateResourceLoader(ARGS&&... args);

		/**
		\param loader The loader to deallocate

		\brief Deallocates the passed loader.
		*/
		static void deallocateResourceLoader(ResourceLoader *loader);

		/**
		\param ID    The row-id of the row to remove.
		\param table The table to remove the row from.

		\brief Removes a row with the ID \p id from the table \p table.
		*/
		//an ID should always fit into int64
		NOU::boolean removeRow(NOU::int64 id, const NOU::NOU_DAT_ALG::StringView8 &table);

		/**
		\brief Constructs a new instance that uses the file with the path \p DATABASE_PATH as database.
		*/
		ResourceManager();

	public:
		ResourceManager(const ResourceManager &other) = delete;
		ResourceManager(ResourceManager &&other) = delete;

		/**
		\tparam ARGS The types of the arguments that will be passed to the constructor of \p T.

		\param args The arguments that will be passed to the constructor of \p T.

		\return A pointer to the allocated resource.

		\brief Allocates a new instance of \p T. \p T must be a child of nostra::engine::core::Resource.
		*/
		template<typename T, typename... ARGS>
		Resource* allocateResource(ARGS&&... args);

		/**
		\param resource The resource to deallocate.

		\brief Deallocates a resource that was previously allocated with allocateResource().
		*/
		NOU_FUNC void deallocateResource(Resource *resource);

		/**
		\return The static instance of the resource manager.

		\brief Returns the instance of the resource manager.

		\details
		Returns the instance of the resource manager. This method also stores the instance as a static local variable.
		*/
		NOU_FUNC static ResourceManager& get();

		/**
		\tparam T    The type resource loader to add. This must be a child class of ResourceLoader.
		\tparam ARGS The types of the parameters that will be passed to the constructor of the resource
		loader.

		\param args The parameters that will be passed to the constructor of the resource loader.

		\return True, if the loader was added and false if it was not (in that case, a loader with the same
		name already exists).

		\brief Adds a new ResourceLoader.

		\details
		Adds a new ResourceLoader. It is only possible to get a ResourceLoader using getLoader() after it has
		been added using this method.

		\note
		The loader names need to be unique and there can never be two loaders added to the manager with the
		same name at the same time.
		*/
		template<typename T, typename ...ARGS>
		NOU::boolean addLoader(ARGS&&... args);

		/**
		\param name The name of the resource loader to get.

		\return The loader with the passed name, or \p nullptr if there is no such loader.

		\brief Returns the loader with the passed name.
		*/
		NOU_FUNC ResourceLoader* getLoader(const NOU::NOU_DAT_ALG::String8 &name);

		/**
		\brief Deletes the cache files of all resources.
		*/
		NOU_FUNC void deleteCaches();

		/**
		\param path        The path to the resource. It is not allowed to have different resources that have
		the same path.
		\param type        The ID of the type of the resource. This type must already exist.
		\param enableCache Enables (true) or disables (false) the caching.
		\param cachePath   The path to the cache of the resource. If \p enableCache is false, this parameter
		will be ignored.

		\return The ID of the resource that was added, or ResourceManager::INVALID_RESOURCE_ID if an error
		occurred (check the error handler for further information about the error).

		\brief Adds a new resource to the resource database.

		\details
		Adds a new resource to the resource database. On failure, ResourceManager::INVALID_RESOURCE_ID is
		returned and an error is pushed to the error handler. The possible errors are:
		- ErrorCodes::RESOURCE_ALREADY_PRESENT: A resource with the same path already exists.
		- ErrorCodes::INVALID_PATH: The path does not lead to a file (either the path the resource or the path
		to the cache is invalid).
		(Note that this list does not include errors that may be pushed be e.g. an underlying container)

		\note
		Since the resource manager stores what resources are added to it in a database that is persistent over
		multiple executions of the engine, this method does not need to be called each time that the engine
		is being executed.

		\note
		As long as the resource is not removed from the database, the ID of the resources will stay the same
		over multiple executions (if a resource is removed and then added again, the ID may, and most likely
		will, change).
		*/
		NOU_FUNC typename ResourceMetadata::ID addResource(const NOU::NOU_FILE_MNGT::Path &path,
			typename ResourceType::ID type, NOU::boolean enableCache = false,
			const NOU::NOU_FILE_MNGT::Path &cachePath = "./");

		/**
		\param id The ID of the resource that should be removed.

		\return True, if the resource was removed, false if not. The operation fails if there is no resource
		with the passed ID.

		\brief Removes a resource from the resource database.

		\note
		This method does not delete the files that were associated with that resource (that is the source and
		a possible cache file).
		*/
		NOU_FUNC NOU::boolean removeResource(typename ResourceMetadata::ID id);

		/**
		\return The amount of resources that were removed.

		\brief Removes all resources from the database whose source file does not exist.

		\note
		This method behaves as if removeResource() was called for each resource.
		*/
		NOU_FUNC NOU::uint32 cleanupResources();

		/**
		\param id          The ID of the resource.
		\param enableCache Enables (true) or disables (false) the caching.
		\param cachePath   The path to the cache of the resource. If \p enableCache is false, this parameter
		will be ignored.

		\return True, if the operation was successful and false if not. If the operation was not successful,
		an error will be pushed to the error handler.

		\brief Enables or disables caching for a resource.

		\details
		Enables or disables caching for a resource. On failure, ResourceManager::INVALID_RESOURCE_ID is
		returned and an error is pushed to the error handler. The possible errors are:
		- ErrorCodes::INVALID_PATH: The path does not lead to a file (either the path the resource or the path
		to the cache is invalid).
		- ErrorCodes::RESOURCE_NOT_PRESENT: A resource with the passed ID does not exist.
		(Note that this list does not include errors that may be pushed be e.g. an underlying container)
		*/
		NOU_FUNC NOU::boolean cache(typename ResourceMetadata::ID id, NOU::boolean enableCache,
			const NOU::NOU_FILE_MNGT::Path &path = "./");

		/**
		\param id The ID of the resource.

		\return True, if the resource was removed, false if not. The operation fails if there is no resource
		with the passed ID.

		\brief Deletes the cache file of the resource with the passed ID.

		\details
		Deletes the cache file of the resource with the passed ID. This can be used to force to regenerate a
		cache.

		\note
		If the resource exists but is not cached, this method will not do anything (but it will still return
		true).
		*/
		NOU_FUNC NOU::boolean deleteCache(typename ResourceMetadata::ID id);

		/**
		\param id The ID of the resource.

		\return The meta data of the resource with the passed ID, or \p nullptr if the resource does not
		exist.

		\brief Returns the meta data of a single resource.
		*/
		NOU_FUNC ResourceMetadata getMetadata(typename ResourceMetadata::ID id) const;

		/**
		\return A list that contains the meta data of all resources in the database.

		\brief Returns a list that contains the meta data of all resources in the database.
		*/
		NOU_FUNC NOU::NOU_DAT_ALG::Vector<ResourceMetadata> listMetadata();

		/**
		\param name The name of the type.

		\return The ID of the type that was created, or ResourceType::INVALID_ID if the type could not be
		        created.

		\brief Adds a new type with the name \p name and the description \p NULL.
		*/
		NOU_FUNC typename ResourceType::ID addType(const NOU::NOU_DAT_ALG::StringView8 &name);

		/**
		\param name        The name of the type.
		\param description The description of the type.

		\return The ID of the type that was created, or ResourceType::INVALID_ID if the type could not be
		created.

		\brief Adds a new type with the name \p name and the description \p description.
		*/
		NOU_FUNC typename ResourceType::ID addType(const NOU::NOU_DAT_ALG::StringView8 &name,
			const NOU::NOU_DAT_ALG::StringView8 &description);

		/**
		\param id The ID of the type to remove.

		\return True, if the type was removed, false if not.

		\brief Removes a type from the database.
		*/
		NOU_FUNC NOU::boolean removeType(typename ResourceType::ID id);

		/**
		\param id The ID of the type to get.

		\brief Returns the type with the passed ID. That type may be invalid.
		*/
		NOU_FUNC ResourceType getType(typename ResourceType::ID id) const;

		/**
		\return A list that contains all types in the database.

		\brief Returns a list that contains all types in the database.
		*/
		NOU_FUNC NOU::NOU_DAT_ALG::Vector<ResourceType> listTypes();

		/**
		\return The count of type removes.

		\brief Returns the count of type removes.

		\details
		Returns the count of type removes. See m_typeRemoveUpdates for further information.
		*/
		NOU_FUNC NOU::int32 getTypeRemoveUpdates() const;

		/**
		\return The count of resources removes.

		\brief Returns the count of resources removes.

		\details
		Returns the resources of type removes. See m_resourceRemoveUpdates for further information.
		*/
		NOU_FUNC NOU::int32 getResourceRemoveUpdates() const;

		/**
		\brief Initializes the resource manager. It is only usable after this method has been called.
		*/
		NOU_FUNC void initalize();

		/**
		\brief Terminates the resource manager. After calling this method, it is not usable anymore.
		*/
		NOU_FUNC void terminate();

		/**
		\return The underlying database.

		\brief Returns the underlying database.
		*/
		NOU_FUNC NOE::NOE_UTILITY::sqlite::Database& getUnderlying();
	};

	template<typename T, typename... ARGS>
	Resource* ResourceManager::allocateResource(ARGS&&... args)
	{
		static_assert(NOU::NOU_CORE::IsBaseOf<Resource, T>::value);

		return new T(NOU::NOU_CORE::forward<ARGS>(args)...);
	}

	template<typename T, typename ...ARGS>
	static ResourceLoader* ResourceManager::allocateResourceLoader(ARGS&&... args)
	{
		static_assert(NOU::NOU_CORE::IsBaseOf<ResourceLoader, T>::value);

		return new T(NOU_CORE::forward<ARGS>(args)...);
	}

	template<typename T, typename ...ARGS>
	NOU::boolean ResourceManager::addLoader(ARGS&&... args)
	{
		ResourceLoader *loader = allocateResourceLoader<T>(NOU_CORE::forward<ARGS>(args)...);

		if (!m_loaders.containsKey(loader->getName()))
		{
			m_loaders.map(loader->getName(), loader);
			return true;
		}
		else
		{
			return false;
		}
	}
}

#endif