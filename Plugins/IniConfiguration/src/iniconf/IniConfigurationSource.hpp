#ifndef	INI_CONFIGURATION_SOURCE_HPP
#define INI_CONFIGURATION_SOURCE_HPP

#include "nostraengine/NostraEngine.hpp"

namespace IniConfigurationPlugin
{
	class IniConfigurationSource final : public NOE::NOE_CORE::ConfigurationSource
	{
	private:
		NOU::NOU_FILE_MNGT::Path m_path;
		NOU::NOU_FILE_MNGT::INIFile m_file;

		NOE_PLUGIN_FUNC void parsePath(const NOU::NOU_DAT_ALG::StringView8 &path, 
			NOU::NOU_DAT_ALG::StringView8 *key, NOU::NOU_DAT_ALG::StringView8 *section) const;

	protected:
		NOE_PLUGIN_FUNC virtual NOU::boolean initializeImpl() override;

		NOE_PLUGIN_FUNC virtual NOU::boolean terminateImpl() override;

		NOE_PLUGIN_FUNC virtual NOU::boolean storeAll() override;

		NOE_PLUGIN_FUNC virtual NOU::boolean 
								hasEntryImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		NOE_PLUGIN_FUNC virtual TypeID 
								getTypeOfImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		NOE_PLUGIN_FUNC virtual NOU::boolean 
							getBooleanImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		NOE_PLUGIN_FUNC virtual NOU::boolean setBooleanImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			NOU::boolean v) override;

		NOE_PLUGIN_FUNC virtual const NOU::NOU_DAT_ALG::String8&
			getStringImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		NOE_PLUGIN_FUNC virtual NOU::boolean setStringImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			const NOU::NOU_DAT_ALG::StringView8 &v) override;

		NOE_PLUGIN_FUNC virtual NOU::int32 
								getInt32Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		NOE_PLUGIN_FUNC virtual NOU::boolean setInt32Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			NOU::int32 v) override;

		NOE_PLUGIN_FUNC virtual NOU::int64 
								getInt64Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		NOE_PLUGIN_FUNC virtual NOU::boolean setInt64Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			NOU::int64 v) override;

		NOE_PLUGIN_FUNC virtual NOU::float32 
							getFloat32Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		NOE_PLUGIN_FUNC virtual NOU::boolean setFloat32Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			NOU::float32 v) override;

		NOE_PLUGIN_FUNC virtual NOU::float64 
							getFloat64Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		NOE_PLUGIN_FUNC virtual NOU::boolean setFloat64Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			NOU::float64 v) override;

		NOE_PLUGIN_FUNC virtual void* 
							getVoidPtrImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const override;

		NOE_PLUGIN_FUNC virtual NOU::boolean setVoidPtrImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
			void *v) override;

		NOE_PLUGIN_FUNC virtual NOU::boolean store(const NOU::NOU_DAT_ALG::StringView8 &qualified) override;

	public:
		IniConfigurationSource(const NOU::NOU_FILE_MNGT::Path &path);

		virtual const NOU::NOU_DAT_ALG::StringView8& getName() override;

	};
}

#endif