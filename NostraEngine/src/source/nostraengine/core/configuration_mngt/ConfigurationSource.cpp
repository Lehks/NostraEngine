#include "nostraengine/core/configuration_mngt/ConfigrationSource.hpp"

namespace NOE::NOE_CORE
{
	void ConfigurationSource::addStorageBehavior(StorageBehavior storageBehavior)
	{
		m_storageBehavior = static_cast<StorageBehavior>(m_storageBehavior | storageBehavior);
	}

	void ConfigurationSource::removeStorageBehavior(StorageBehavior storageBehavior)
	{
		m_storageBehavior = static_cast<StorageBehavior>(m_storageBehavior & ~storageBehavior);
	}

	ConfigurationSource::ConfigurationSource(StorageBehavior storageBehavior) :
		m_storageBehavior(storageBehavior)
	{}
	
	ConfigurationSource::StorageBehavior ConfigurationSource::getStorageBehavior() const
	{
		return m_storageBehavior;
	}

	NOU::boolean ConfigurationSource::hasStorageBehavior(StorageBehavior storageBehavior) const
	{
		return static_cast<NOU::boolean>(m_storageBehavior & storageBehavior);
	}

	NOU::boolean ConfigurationSource::initialize()
	{
		return initializeImpl();
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
		return getBooleanImpl(qualified);
	}

	NOU::boolean ConfigurationSource::setBoolean(const NOU::NOU_DAT_ALG::StringView8 &qualified, 
		NOU::boolean v)
	{
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
		return getStringImpl(qualified);
	}

	NOU::boolean ConfigurationSource::setString(const NOU::NOU_DAT_ALG::StringView8 &qualified,
		const NOU::NOU_DAT_ALG::StringView8 &v)
	{
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
		return getInt32Impl(qualified);
	}

	NOU::boolean ConfigurationSource::setInt32(const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::int32 v)
	{
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
		return getInt64Impl(qualified);
	}

	NOU::boolean ConfigurationSource::setInt64(const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::int64 v)
	{
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
		return getFloat32Impl(qualified);
	}

	NOU::boolean ConfigurationSource::setFloat32(const NOU::NOU_DAT_ALG::StringView8 &qualified,
		NOU::float32 v)
	{
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
		return getFloat64Impl(qualified);
	}

	NOU::boolean ConfigurationSource::setFloat64(const NOU::NOU_DAT_ALG::StringView8 &qualified, 
		NOU::float64 v)
	{
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
		return getVoidPtrImpl(qualified);
	}

	NOU::boolean ConfigurationSource::setVoidPtr(const NOU::NOU_DAT_ALG::StringView8 &qualified, void *v)
	{
		NOU::boolean ret = setVoidPtrImpl(qualified, v);

		//only if the value could be set and the required behavior is set
		if (ret && hasStorageBehavior(StorageBehavior::STORE_ON_UPDATE))
		{
			ret = store(qualified);
		}

		return ret;
	}
}