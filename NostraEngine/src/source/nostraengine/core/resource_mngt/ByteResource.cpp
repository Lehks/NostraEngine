#include "nostraengine/core/resource_mngt/ByteResource.hpp"

#include "nostrautils/file_mngt/File.hpp"

namespace NOE::NOE_CORE
{
	ByteResource::ByteResource(ResourceMetadata::ID id, const NOU::NOU_DAT_ALG::String8& name,
		NOU::NOU_DAT_ALG::Vector<NOU::byte> &&bytes) : 
		Resource(id, name),
		m_bytes(bytes)
	{}

	NOU::NOU_DAT_ALG::Vector<NOU::byte>& ByteResource::getBytes()
	{
		return m_bytes;
	}

	const NOU::NOU_DAT_ALG::Vector<NOU::byte>& ByteResource::getBytes() const
	{
		return m_bytes;
	}





	const NOU::NOU_DAT_ALG::String8 ByteResourceLoader::NAME = "NOE_BYTE_LOADER";

	NOU::boolean ByteResourceLoader::storeImpl(Resource *resource, const NOU::NOU_FILE_MNGT::Path& path)
	{
		//to ensure the reinterpret_cast works
		static_assert(sizeof(NOU::char8) == sizeof(NOU::byte));

		ByteResource *byteRes = reinterpret_cast<ByteResource*>(resource);

		NOU::NOU_FILE_MNGT::File file(path);

		file.open();

		byteRes->getBytes().pushBack(0);

		NOU::boolean res = file.write(reinterpret_cast<NOU::char8*>(byteRes->getBytes().data()));

		file.close();

		if (res)
		{
			ResourceManager::get().deallocateResource(byteRes);
			return true;
		}
		else
			return false;
	}

	NOU::boolean ByteResourceLoader::storeCacheImpl(Resource *resource, const NOU::NOU_FILE_MNGT::Path& path)
	{
		return false;
	}

	Resource* ByteResourceLoader::loadImpl(const ResourceMetadata &metaData,
		const NOU::NOU_FILE_MNGT::Path& path)
	{
		//to ensure the reinterpret_cast works
		static_assert(sizeof(NOU::char8) == sizeof(NOU::byte));

		NOU::NOU_FILE_MNGT::File file(path);

		NOU::sizeType fileSize = file.size();

		NOU::NOU_DAT_ALG::Vector<NOU::byte> bytes(fileSize + 1);
		
		file.open();

		file.read(fileSize, reinterpret_cast<NOU::char8*>(bytes.data()));

		//+1 to enable writing after the bytes
		bytes.setSize(fileSize + 1);

		bytes[fileSize] = 0; //this is required by the string view later
		
		//shrink again, to have write protection on the null terminator
		bytes.setSize(fileSize);

		file.close();

		Resource *ret = ResourceManager::get().allocateResource<ByteResource>(metaData.getID(), 
																	getName(), NOU::NOU_CORE::move(bytes));

		return ret;
	}

	Resource* ByteResourceLoader::loadCacheImpl(const ResourceMetadata &metaData, 
		const NOU::NOU_FILE_MNGT::Path& path)
	{
		return nullptr;
	}

	ByteResourceLoader::ByteResourceLoader() : ResourceLoader(NAME)
	{
		ResourceLoader::enableCaching(false); //can not cache
	}

	NOU::boolean ByteResourceLoader::isResourceValid(typename ResourceMetadata::ID id) const
	{
		return true; //the byte loader can load any resource
	}
}