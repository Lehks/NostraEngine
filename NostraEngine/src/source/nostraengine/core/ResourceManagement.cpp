#include "nostraengine/core/ResourceManagement.hpp"

namespace NOE::NOE_CORE
{
	ResourceMetadata::ResourceMetadata(ResourceID id, const NOU::NOU_FILE_MNGT::Path &path,
		const ResourceType &type, NOU::boolean isCached,
		const NOU::NOU_FILE_MNGT::Path &cachePath) :
		m_id(id),
		m_type(type),
		m_path(path),
		m_isCached(isCached),
		m_cachePath(cachePath)
	{}

	typename ResourceMetadata::ResourceID ResourceMetadata::getID() const
	{
		return m_id;
	}

	const typename ResourceMetadata::ResourceType& ResourceMetadata::getType() const
	{
		return m_type;
	}

	const NOU::NOU_FILE_MNGT::Path& ResourceMetadata::getPath() const
	{
		return m_path;
	}

	NOU::boolean ResourceMetadata::isCached() const
	{
		return m_isCached;
	}

	const NOU::NOU_FILE_MNGT::Path& ResourceMetadata::getCachePath() const
	{
		return m_cachePath;
	}



	Resource::Resource(const ResourceMetadata &metaData, const NOU::NOU_DAT_ALG::StringView8 &name) :
		m_metaData(metaData),
		m_name(name)
	{}

	const ResourceMetadata& Resource::getMetadata() const
	{
		return m_metaData;
	}

	const NOU::NOU_DAT_ALG::StringView8& Resource::getLoaderName() const
	{
		return m_name;
	}

	NOU::boolean Resource::store()
	{
		///\todo implement
		return false;
	}

	NOU::boolean Resource::cache(NOU::boolean enableCache = true,
		const NOU::NOU_FILE_MNGT::Path &path = "./")
	{
		///\todo implement
		return false;
	}

	void Resource::deleteCache()
	{
		///\todo implement
	}
}