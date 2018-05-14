#include "nostraengine\core\Plugin.hpp"

#include "nostraengine/core/PluginManager.hpp"

namespace NOE::NOE_CORE
{
	Plugin *Plugin::s_plugin;

	void Plugin::set(Plugin *plugin)
	{
		s_plugin = plugin;
	}

	Plugin* Plugin::get()
	{
		return s_plugin;
	}

	void Plugin::setID(ID id)
	{
		m_id = id;
	}

	Plugin::SendResult Plugin::send(ID recipient, void *data, NOU::sizeType size, NOU::uint32 flags)
	{
		return PluginManager::get().sendImpl(recipient, getID(), data, size, flags);
	}

	Plugin::ID Plugin::getID() const
	{
		return m_id;
	}
}
