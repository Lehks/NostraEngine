
#include "nostraengine/core/ResourceManagement.hpp"

namespace NOE::NOE_CORE
{
	Resource::Resource(ResourceMetadata::ID id, const NOU::NOU_DAT_ALG::String8 &name) :
		m_metadata(id),
		m_name(name)
	{}

	const ResourceMetadata& Resource::getMetadata() const
	{
		return m_metadata;
	}

	const NOU::NOU_DAT_ALG::String8& Resource::getLoaderName() const
	{
		return m_name;
	}

	NOU::boolean Resource::store()
	{
		return ResourceManager::get().getLoader(getLoaderName())->store(this);
	}

	NOU::boolean Resource::cache(NOU::boolean enableCache,
		const NOU::NOU_FILE_MNGT::Path &path)
	{
		return ResourceManager::get().cache(getMetadata().getID(), enableCache, path);
	}

	void Resource::deleteCache()
	{
		ResourceManager::get().deleteCache(getMetadata().getID());
	}
}