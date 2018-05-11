#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/core/NostraEngine.hpp"

#ifndef NOE_SET_AS_ACTIVE_PLUGIN_CLASS

#define     NOE_SET_AS_ACTIVE_PLUGIN_CLASS(PLUGIN)												 \
																								 \
extern "C" NOU_FUNC void noePluginStartup()														 \
{																								 \
	NOE::NOE_CORE::Plugin::set(new PLUGIN());													 \
}																								 \
																								 \
extern "C" NOU_FUNC void noePluginShutdown()													 \
{																								 \
	delete NOE::NOE_CORE::Plugin::get();														 \
}																								 \
																								 \
extern "C" NOU_FUNC NOU::uint32 noePluginGetVersion()											 \
{																								 \
	return NOE::NOE_CORE::Plugin::get()->getVersion().getRaw();									 \
}																								 \
																								 \
extern "C" NOU_FUNC const NOU::char8 * noePluginGetName()										 \
{																								 \
	return NOE::NOE_CORE::Plugin::get()->getName().rawStr();									 \
}																								 \
																								 \
extern "C" NOU_FUNC NOU::uint32 noePluginStart(void * engineInstance)							 \
{																								 \
	NOE::NostraEngine *engine = reinterpret_cast<NOE::NostraEngine*>(engineInstance);			 \
																								 \
	NOE::NOE_CORE::PluginStartResult result = NOE::NOE_CORE::Plugin::get()->start(*engine);		 \
																								 \
	return NOU::uint32(result);																	 \
}


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
	private:
		static Plugin *s_plugin;

	public:
		static void set(Plugin *plugin);
		static Plugin* get();

		Plugin() = default;

		Plugin(const Plugin &other) = delete;
		Plugin(Plugin &&) = delete;

		virtual const NOU::NOU_CORE::Version getVersion() const = 0;
		virtual const NOU::NOU_DAT_ALG::StringView8& getName() const = 0;
		virtual PluginStartResult start(NostraEngine &engineInstance) = 0;
	};
}