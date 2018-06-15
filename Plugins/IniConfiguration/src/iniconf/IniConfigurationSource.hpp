#ifndef	INI_CONFIGURATION_SOURCE_HPP
#define INI_CONFIGURATION_SOURCE_HPP

#include "nostraengine/NostraEngine.hpp"

namespace IniConfigurationPlugin
{
	class NOU_CLASS IniConfigurationSource final : public NOE::NOE_CORE::ConfigurationSource
	{
	private:
		NOU::NOU_FILE_MNGT::Path m_path;
		NOU::NOU_FILE_MNGT::INIFile m_file;

		void parsePath(const NOU::NOU_DAT_ALG::StringView8 &path, NOU::NOU_DAT_ALG::StringView8 *key,
			NOU::NOU_DAT_ALG::StringView8 *section) const;

	protected:
		virtual NOU::boolean initializeImpl() override;

		virtual NOU::boolean terminateImpl() override;

		virtual NOU::boolean storeAll() override;

		virtual NOU::boolean hasEntryImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		virtual TypeID getTypeOfImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		virtual NOU::boolean getBooleanImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		virtual NOU::boolean setBooleanImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			NOU::boolean v) override;

		virtual const NOU::NOU_DAT_ALG::String8&
			getStringImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		virtual NOU::boolean setStringImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			const NOU::NOU_DAT_ALG::StringView8 &v) override;

		virtual NOU::int32 getInt32Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		virtual NOU::boolean setInt32Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			NOU::int32 v) override;

		virtual NOU::int64 getInt64Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		virtual NOU::boolean setInt64Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			NOU::int64 v) override;

		virtual NOU::float32 getFloat32Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		virtual NOU::boolean setFloat32Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			NOU::float32 v) override;

		virtual NOU::float64 getFloat64Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		virtual NOU::boolean setFloat64Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			NOU::float64 v) override;

		virtual void* getVoidPtrImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		virtual NOU::boolean setVoidPtrImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			void *v) override;

		virtual NOU::boolean store(const NOU::NOU_DAT_ALG::StringView8 &qualified) override;

	public:
		IniConfigurationSource(const NOU::NOU_FILE_MNGT::Path &path);

		virtual const NOU::NOU_DAT_ALG::StringView8& getName() override;

	};
}

#endif