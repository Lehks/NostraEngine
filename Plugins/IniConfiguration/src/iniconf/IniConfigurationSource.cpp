
#include "IniConfigurationSource.hpp"

namespace IniConfigurationPlugin
{
/**
\todo remove const_cast
\todo replace literals with constants in getTypeOfImpl()
*/

	void IniConfigurationSource::parsePath(const NOU::NOU_DAT_ALG::StringView8 &path,
		NOU::NOU_DAT_ALG::StringView8 *key, NOU::NOU_DAT_ALG::StringView8 *section) const
	{
		NOU::sizeType index = path.find('.');

		if (index != NOU::NOU_DAT_ALG::StringView8::NULL_INDEX)
		{
			*key = path.logicalSubstring(index + 1);
			*section = path.logicalSubstring(0, index);
		}
		else
		{
			*key = path;
		}
	}


	NOU::boolean IniConfigurationSource::initializeImpl()
	{
		return m_file.read();
	}

	NOU::boolean IniConfigurationSource::terminateImpl()
	{
		return true;
	}

	NOU::boolean IniConfigurationSource::storeAll()
	{
		return m_file.write();
	}

	NOU::boolean IniConfigurationSource::hasEntryImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 key;
		NOU::NOU_DAT_ALG::StringView8 section;

		parsePath(qualified, &key, &section);

		return const_cast<IniConfigurationSource*>(this)->m_file.keyExists(key, section);
	}

	NOE::NOE_CORE::ConfigurationSource::TypeID 
		IniConfigurationSource::getTypeOfImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 key;
		NOU::NOU_DAT_ALG::StringView8 section;

		parsePath(qualified, &key, &section);

		NOU::int32 type = const_cast<IniConfigurationSource*>(this)->m_file.getDataType(key, section);

		if (type == 1)//NOU::NOU_FILE_MNGT::INIFile::INI_TYPE_NouString)
		{
			return NOE::NOE_CORE::ConfigurationSource::TypeID::STRING;
		}
		else if (type == 2)//NOU::NOU_FILE_MNGT::INIFile::INI_TYPE_INT)
		{
			return NOE::NOE_CORE::ConfigurationSource::TypeID::INT_32;
		}
		else if (type == 3)//NOU::NOU_FILE_MNGT::INIFile::INI_TYPE_FLOAT)
		{
			return NOE::NOE_CORE::ConfigurationSource::TypeID::FLOAT_32;
		}
		else
		{
			return NOE::NOE_CORE::ConfigurationSource::TypeID::INVALID;
		}
	}

	NOU::boolean IniConfigurationSource::getBooleanImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 key;
		NOU::NOU_DAT_ALG::StringView8 section = NOU::NOU_FILE_MNGT::INIFile::INI_DEFAULT_SECTION;

		parsePath(qualified, &key, &section);

		if (const_cast<IniConfigurationSource*>(this)->m_file.keyExists(key, section))
		{
			return const_cast<IniConfigurationSource*>(this)->m_file.getInt(key, section);
		}
		else
			return NOU::float32(0);
	}

	NOU::boolean IniConfigurationSource::setBooleanImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
		NOU::boolean v)
	{
		NOU::NOU_DAT_ALG::StringView8 key;
		NOU::NOU_DAT_ALG::StringView8 section = NOU::NOU_FILE_MNGT::INIFile::INI_DEFAULT_SECTION;

		parsePath(qualified, &key, &section);

		if (m_file.keyExists(key, section))
		{
			m_file.setInt(key, v, section);

			return true;
		}
		else
			return false;
	}

	NOU::NOU_DAT_ALG::String8
		IniConfigurationSource::getStringImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 key;
		NOU::NOU_DAT_ALG::StringView8 section = NOU::NOU_FILE_MNGT::INIFile::INI_DEFAULT_SECTION;

		parsePath(qualified, &key, &section);

		NOU::NOU_DAT_ALG::String8 str = section;
		NOU::NOU_DAT_ALG::String8 str1 = key;

		if (const_cast<IniConfigurationSource*>(this)->m_file.keyExists(key, section))
		{
			return const_cast<IniConfigurationSource*>(this)->m_file.getString(key, section);
		}
		else
			return NOU::NOU_DAT_ALG::String8::EMPTY_STRING;
	}

	NOU::boolean IniConfigurationSource::setStringImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
		const NOU::NOU_DAT_ALG::StringView8 &v)
	{
		NOU::NOU_DAT_ALG::StringView8 key;
		NOU::NOU_DAT_ALG::StringView8 section = NOU::NOU_FILE_MNGT::INIFile::INI_DEFAULT_SECTION;

		parsePath(qualified, &key, &section);

		if (m_file.keyExists(key, section))
		{
			m_file.setString(key, v, section);

			return true;
		}
		else
			return false;
	}

	NOU::int32 IniConfigurationSource::getInt32Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 key;
		NOU::NOU_DAT_ALG::StringView8 section = NOU::NOU_FILE_MNGT::INIFile::INI_DEFAULT_SECTION;

		parsePath(qualified, &key, &section);

		if (const_cast<IniConfigurationSource*>(this)->m_file.keyExists(key, section))
		{
			return const_cast<IniConfigurationSource*>(this)->m_file.getInt(key, section);
		}
		else
			return NOU::int32(0);
	}

	NOU::boolean IniConfigurationSource::setInt32Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
		NOU::int32 v)
	{
		NOU::NOU_DAT_ALG::StringView8 key;
		NOU::NOU_DAT_ALG::StringView8 section = NOU::NOU_FILE_MNGT::INIFile::INI_DEFAULT_SECTION;

		parsePath(qualified, &key, &section);

		if (m_file.keyExists(key, section))
		{
			m_file.setInt(key, v, section);

			return true;
		}
		else
			return false;
	}

	NOU::int64 IniConfigurationSource::getInt64Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		return getInt32Impl(qualified);
	}

	NOU::boolean IniConfigurationSource::setInt64Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
		NOU::int64 v)
	{
		return setInt32Impl(qualified, static_cast<NOU::int32>(v));
	}

	NOU::float32 IniConfigurationSource::getFloat32Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 key;
		NOU::NOU_DAT_ALG::StringView8 section = "";

		parsePath(qualified, &key, &section);

		if (const_cast<IniConfigurationSource*>(this)->m_file.keyExists(key, section))
		{
			return const_cast<IniConfigurationSource*>(this)->m_file.getFloat(key, section);
		}
		else
			return NOU::float32(0);
	}

	NOU::boolean IniConfigurationSource::setFloat32Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
		NOU::float32 v)
	{
		NOU::NOU_DAT_ALG::StringView8 key;
		NOU::NOU_DAT_ALG::StringView8 section = "";

		parsePath(qualified, &key, &section);

		if (m_file.keyExists(key, section))
		{
			m_file.setFloat(key, v, section);

			return true;
		}
		else
			return false;
	}

	NOU::float64 IniConfigurationSource::getFloat64Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		return getFloat32Impl(qualified);
	}

	NOU::boolean IniConfigurationSource::setFloat64Impl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
		NOU::float64 v)
	{
		return setFloat32Impl(qualified, static_cast<NOU::float32>(v));
	}	

	void* IniConfigurationSource::getVoidPtrImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		return nullptr;
	}

	NOU::boolean IniConfigurationSource::setVoidPtrImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified,
		void *v)
	{
		return false;
	}

	NOU::boolean IniConfigurationSource::store(const NOU::NOU_DAT_ALG::StringView8 &qualified)
	{
		return storeAll();
	}

	IniConfigurationSource::IniConfigurationSource(const NOU::NOU_FILE_MNGT::Path &path) :
		ConfigurationSource(StorageBehavior::STORE_ON_FLUSH | StorageBehavior::STORE_ON_TERMINATE),
		m_path(path),
		m_file(path.getAbsolutePath())
	{}

	const NOU::NOU_DAT_ALG::StringView8& IniConfigurationSource::getName()
	{
		return m_path.getName();
	}

}