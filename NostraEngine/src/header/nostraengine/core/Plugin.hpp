#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/core/NostraEngine.hpp"

extern "C"
{
	extern void *pluginPtr;

	NOU_FUNC NOU::uint32 noePluginGetVersion();
	NOU_FUNC const NOU::char8* noePluginGetName();
	NOU_FUNC NOU::uint32 noePluginStart(void* engineInstance);
}

#ifndef NOE_SET_AS_ACTIVE_PLUGIN_CLASS_WIN
#define NOE_SET_AS_ACTIVE_PLUGIN_CLASS_WIN(PLUGIN)
#endif

#ifndef NOE_SET_AS_ACTIVE_PLUGIN_CLASS_POSIX
#define NOE_SET_AS_ACTIVE_PLUGIN_CLASS_POSIX(PLUGIN) 
#endif

#ifndef NOE_SET_AS_ACTIVE_PLUGIN_CLASS

#if     NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
#define     NOE_SET_AS_ACTIVE_PLUGIN_CLASS(PLUGIN) NOE_SET_AS_ACTIVE_PLUGIN_CLASS_WIN(PLUGIN) 
#elif   NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#define     NOE_SET_AS_ACTIVE_PLUGIN_CLASS(PLUGIN) NOE_SET_AS_ACTIVE_PLUGIN_CLASS_POSIX(PLUGIN) 
#endif

#endif

namespace NOE::NOE_CORE
{
	enum class PluginStartResult : NOU::uint32
	{
		SUCCESS = 0,
		WARNING = 1,
		FAILED  = 2
	};

	class NOU_CLASS Plugin
	{
	public:
		Plugin(const Plugin &other) = delete;
		Plugin(Plugin &&) = delete;

		virtual const NOU::NOU_CORE::Version getVersion() const = 0;
		virtual const NOU::NOU_DAT_ALG::StringView8& getName() const = 0;
		virtual PluginStartResult start(NostraEngine &engineInstance) = 0;
	};

}