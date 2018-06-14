#include "nostraengine/core/configuration_mngt/ConfigurationSource.hpp"

namespace NOE::NOE_CORE
{
#ifdef NOU_ASSERT //only required if NOU_ASSERT uses it
	NOU::boolean isValidStorageBehavior(ConfigurationSource::StorageBehavior storageBehavior)
	{
		return storageBehavior == ConfigurationSource::StorageBehavior::STORE_ON_TERMINATE ||
			storageBehavior == ConfigurationSource::StorageBehavior::STORE_ON_FLUSH || 
			storageBehavior == ConfigurationSource::StorageBehavior::STORE_ON_UPDATE || 

			storageBehavior == (ConfigurationSource::StorageBehavior::STORE_ON_TERMINATE | 
				ConfigurationSource::StorageBehavior::STORE_ON_FLUSH) ||

			storageBehavior == (ConfigurationSource::StorageBehavior::STORE_ON_TERMINATE | 
				ConfigurationSource::StorageBehavior::STORE_ON_UPDATE) ||

			storageBehavior == (ConfigurationSource::StorageBehavior::STORE_ON_FLUSH | 
				ConfigurationSource::StorageBehavior::STORE_ON_UPDATE) ||

			storageBehavior == (ConfigurationSource::StorageBehavior::STORE_ON_TERMINATE | 
				ConfigurationSource::StorageBehavior::STORE_ON_FLUSH
				| ConfigurationSource::StorageBehavior::STORE_ON_UPDATE);
	}
#endif

	void ConfigurationSource::addStorageBehavior(StorageBehavior storageBehavior)
	{
		NOU_ASSERT(isValidStorageBehavior(storageBehavior));

		m_storageBehavior = static_cast<StorageBehavior>(m_storageBehavior | storageBehavior);
	}

	void ConfigurationSource::removeStorageBehavior(StorageBehavior storageBehavior)
	{
		NOU_ASSERT(isValidStorageBehavior(storageBehavior));

		m_storageBehavior = static_cast<StorageBehavior>(m_storageBehavior & ~storageBehavior);
	}

	ConfigurationSource::ConfigurationSource(StorageBehavior storageBehavior) :
		m_storageBehavior(storageBehavior)
	{
		NOU_ASSERT(isValidStorageBehavior(storageBehavior));
	}
	
	ConfigurationSource::StorageBehavior ConfigurationSource::getStorageBehavior() const
	{
		return m_storageBehavior;
	}

	NOU::boolean ConfigurationSource::hasStorageBehavior(StorageBehavior storageBehavior) const
	{
		NOU_ASSERT(isValidStorageBehavior(storageBehavior));

		return static_cast<NOU::boolean>(m_storageBehavior & storageBehavior);
	}

	NOU::boolean ConfigurationSource::initialize()
	{
		///\todo add proper name
		NOU_LOG_INFO("Initializing configuration source NAME...");

		NOU::boolean ret = initializeImpl();

		if (ret)
		{
			///\todo add proper name
			NOU_LOG_INFO("Initializing of configuration source NAME was successful.");
		}
		else
		{
			///\todo add proper name
			NOU_LOG_WARNING("Initializing configuration source NAME was not successful.");
		}

		

		return ret;
	}

	NOU::boolean ConfigurationSource::terminate()
	{
		NOU::boolean ret = true;

		if (hasStorageBehavior(StorageBehavior::STORE_ON_TERMINATE))
			ret = storeAll();

		//only successful, if storeAll() and terminateImpl() were successful
		return ret && terminateImpl();
	}

	void ConfigurationSource::flush()
	{
		if (hasStorageBehavior(StorageBehavior::STORE_ON_FLUSH))
			storeAll();
	}

	NOU::boolean ConfigurationSource::hasEntry(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		return hasEntryImpl(qualified);
	}

	ConfigurationSource::TypeID 
		ConfigurationSource::getTypeOf(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		return getTypeOfImpl(qualified);
	}

	NOU::boolean ConfigurationSource::getBoolean(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::BOOLEAN);

		return getBooleanImpl(qualified);
	}

	NOU::boolean ConfigurationSource::setBoolean(const NOU::NOU_DAT_ALG::StringView8 &qualified, 
		NOU::boolean v)
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::BOOLEAN);

		NOU::boolean ret = setBooleanImpl(qualified, v);

		//only if the value could be set and the required behavior is set
		if (ret && hasStorageBehavior(StorageBehavior::STORE_ON_UPDATE))
		{
			ret = store(qualified);
		}

		return ret;
	}

	const NOU::NOU_DAT_ALG::String8& 
		ConfigurationSource::getString(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::STRING);

		return getStringImpl(qualified);
	}

	NOU::boolean ConfigurationSource::setString(const NOU::NOU_DAT_ALG::StringView8 &qualified,
		const NOU::NOU_DAT_ALG::StringView8 &v)
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::STRING);

		NOU::boolean ret = setStringImpl(qualified, v);

		//only if the value could be set and the required behavior is set
		if (ret && hasStorageBehavior(StorageBehavior::STORE_ON_UPDATE))
		{
			ret = store(qualified);
		}

		return ret;
	}

	NOU::int32 ConfigurationSource::getInt32(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::INT_32);

		return getInt32Impl(qualified);
	}

	NOU::boolean ConfigurationSource::setInt32(const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::int32 v)
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::INT_32);

		NOU::boolean ret = setInt32Impl(qualified, v);

		//only if the value could be set and the required behavior is set
		if (ret && hasStorageBehavior(StorageBehavior::STORE_ON_UPDATE))
		{
			ret = store(qualified);
		}

		return ret;
	}

	NOU::int64 ConfigurationSource::getInt64(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::INT_64);

		return getInt64Impl(qualified);
	}

	NOU::boolean ConfigurationSource::setInt64(const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::int64 v)
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::INT_64);

		NOU::boolean ret = setInt64Impl(qualified, v);

		//only if the value could be set and the required behavior is set
		if (ret && hasStorageBehavior(StorageBehavior::STORE_ON_UPDATE))
		{
			ret = store(qualified);
		}

		return ret;
	}

	NOU::float32 ConfigurationSource::getFloat32(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::FLOAT_32);

		return getFloat32Impl(qualified);
	}

	NOU::boolean ConfigurationSource::setFloat32(const NOU::NOU_DAT_ALG::StringView8 &qualified,
		NOU::float32 v)
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::FLOAT_32);

		NOU::boolean ret = setFloat32Impl(qualified, v);

		//only if the value could be set and the required behavior is set
		if (ret && hasStorageBehavior(StorageBehavior::STORE_ON_UPDATE))
		{
			ret = store(qualified);
		}

		return ret;
	}

	NOU::float64 ConfigurationSource::getFloat64(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::FLOAT_64);

		return getFloat64Impl(qualified);
	}

	NOU::boolean ConfigurationSource::setFloat64(const NOU::NOU_DAT_ALG::StringView8 &qualified, 
		NOU::float64 v)
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::FLOAT_64);

		NOU::boolean ret = setFloat64Impl(qualified, v);

		//only if the value could be set and the required behavior is set
		if (ret && hasStorageBehavior(StorageBehavior::STORE_ON_UPDATE))
		{
			ret = store(qualified);
		}

		return ret;
	}

	void* ConfigurationSource::getVoidPtr(const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::NOT_SET);

		return getVoidPtrImpl(qualified);
	}

	NOU::boolean ConfigurationSource::setVoidPtr(const NOU::NOU_DAT_ALG::StringView8 &qualified, void *v)
	{
		NOU_ASSERT(getTypeOf(qualified) == TypeID::NOT_SET);

		NOU::boolean ret = setVoidPtrImpl(qualified, v);

		//only if the value could be set and the required behavior is set
		if (ret && hasStorageBehavior(StorageBehavior::STORE_ON_UPDATE))
		{
			ret = store(qualified);
		}

		return ret;
	}
}