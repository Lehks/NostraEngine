#include "nostraengine\core\Plugin.hpp"

void *pluginPtr = nullptr;

NOU_FUNC NOU::uint32 noePluginGetVersion()
{
	NOE::NOE_CORE::Plugin *plugin = reinterpret_cast<NOE::NOE_CORE::Plugin*>(pluginPtr);

	return plugin->getVersion().getRaw();
}

NOU_FUNC const NOU::char8 * noePluginGetName()
{
	NOE::NOE_CORE::Plugin *plugin = reinterpret_cast<NOE::NOE_CORE::Plugin*>(pluginPtr);

	return plugin->getName().rawStr();
}

NOU_FUNC NOU::uint32 noePluginStart(void * engineInstance)
{
	NOE::NostraEngine *engine = reinterpret_cast<NOE::NostraEngine*>(engineInstance);
	NOE::NOE_CORE::Plugin *plugin = reinterpret_cast<NOE::NOE_CORE::Plugin*>(pluginPtr);

	NOE::NOE_CORE::PluginStartResult result = plugin->start(*engine);

	return NOU::uint32(result);
}
