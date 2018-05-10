#include "nostraengine/core/ResourceManagement.hpp"

#include "nostrautils/dat_alg/StringView.hpp"

namespace NOE::NOE_CORE
{
	class NOU_CLASS ByteResource final : public Resource
	{
	private:
		NOU::NOU_DAT_ALG::Vector<NOU::byte> m_bytes;

	public:
		ByteResource(ResourceMetadata::ID id, const NOU::NOU_DAT_ALG::StringView8& name, 
			NOU::NOU_DAT_ALG::Vector<NOU::byte> &&bytes);

		NOU::NOU_DAT_ALG::Vector<NOU::byte>& getBytes();
		const NOU::NOU_DAT_ALG::Vector<NOU::byte>& getBytes() const;
	};

	class NOU_CLASS ByteResourceLoader final : public ResourceLoader 
	{
	public:
		static const NOU::NOU_DAT_ALG::StringView8 NAME;

	protected:

		virtual NOU::boolean storeImpl(Resource *resource, const NOU::NOU_FILE_MNGT::Path& path) override;

		virtual NOU::boolean storeCacheImpl(Resource *resource, const NOU::NOU_FILE_MNGT::Path& path) override;

		virtual Resource* loadImpl(const ResourceMetadata &metaData,
			const NOU::NOU_FILE_MNGT::Path& path) override;

		virtual Resource* loadCacheImpl(const ResourceMetadata &metaData,
			const NOU::NOU_FILE_MNGT::Path& path) override;

	public:
		ByteResourceLoader();

		virtual NOU::boolean isResourceValid(typename ResourceMetadata::ID id) const override;

	};
}