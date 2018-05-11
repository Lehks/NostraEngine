#include "nostraengine\core\Plugin.hpp"

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
}
