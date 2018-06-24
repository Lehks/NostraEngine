#include "nostraengine/core/resource_mngt/TextResource.hpp"

#include "nostrautils/file_mngt/File.hpp"

namespace NOE::NOE_CORE
{
	TextResource::TextResource(ResourceMetadata::ID id, const NOU::NOU_DAT_ALG::String8& name,
		NOU::NOU_DAT_ALG::String8 &&text) :
		Resource(id, name),
		m_text(text)
	{}

	NOU::NOU_DAT_ALG::String8& TextResource::getText()
	{
		return m_text;
	}

	const NOU::NOU_DAT_ALG::String8& TextResource::getText() const
	{
		return m_text;
	}





	const NOU::NOU_DAT_ALG::String8 TextResourceLoader::NAME = "NOE_TEXT_LOADER";

	NOU::boolean TextResourceLoader::storeImpl(Resource *resource, const NOU::NOU_FILE_MNGT::Path& path)
	{
		//to ensure the reinterpret_cast works
		static_assert(sizeof(NOU::char8) == sizeof(NOU::byte));

		TextResource *byteRes = static_cast<TextResource*>(resource);

		NOU::NOU_FILE_MNGT::File file(path);

		file.open();

		NOU::boolean res = file.write(byteRes->getText());

		file.close();

		if (res)
		{
			ResourceManager::get().deallocateResource(byteRes);
			return true;
		}
		else
			return false;
	}

	NOU::boolean TextResourceLoader::storeCacheImpl(Resource *resource, const NOU::NOU_FILE_MNGT::Path& path)
	{
		return false;
	}

	Resource* TextResourceLoader::loadImpl(const ResourceMetadata &metaData,
		const NOU::NOU_FILE_MNGT::Path& path)
	{
		//to ensure the reinterpret_cast works
		static_assert(sizeof(NOU::char8) == sizeof(NOU::byte));

		NOU::NOU_FILE_MNGT::File file(path);

		NOU::sizeType fileSize = file.size();

		NOU::NOU_DAT_ALG::String8 text;
		text.appendBuffer(fileSize);

		file.open();

		file.read(text, fileSize);

		file.close();

		Resource *ret = ResourceManager::get().allocateResource<TextResource>(metaData.getID(),
			getName(), NOU::NOU_CORE::move(text));

		return ret;
	}

	Resource* TextResourceLoader::loadCacheImpl(const ResourceMetadata &metaData,
		const NOU::NOU_FILE_MNGT::Path& path)
	{
		return nullptr;
	}

	TextResourceLoader::TextResourceLoader() : ResourceLoader(NAME)
	{
		ResourceLoader::enableCaching(false); //can not cache
	}

	NOU::boolean TextResourceLoader::isResourceValid(typename ResourceMetadata::ID id) const
	{
		return true; //the byte loader can load any resource
	}
}