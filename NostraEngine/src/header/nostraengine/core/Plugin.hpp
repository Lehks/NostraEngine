#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/core/NostraEngine.hpp"

#ifndef NOE_SET_AS_ACTIVE_PLUGIN_CLASS

#define NOE_SET_AS_ACTIVE_PLUGIN_CLASS(PLUGIN)															   \
																										   \
/*version*/																								   \
extern "C" NOU_FUNC NOU::uint32 noePluginGetVersion()													   \
{																										   \
	return NOE::NOE_CORE::Plugin::get()->getVersion().getRaw();											   \
}																										   \
																										   \
/*startup*/																								   \
extern "C" NOU_FUNC void noePluginStartup(NOU::uint32 id)												   \
{																										   \
	NOE::NOE_CORE::Plugin::set(new PLUGIN());															   \
																										   \
	NOE::NOE_CORE::Plugin::get()->setID(id);															   \
}																										   \
																										   \
/*shutdown*/																							   \
extern "C" NOU_FUNC void noePluginShutdown()															   \
{																										   \
	delete NOE::NOE_CORE::Plugin::get();																   \
}																										   \
																										   \
/*receive*/																								   \
extern "C" void noePluginReceive(NOU::uint32 source, void *data, NOU::sizeType size,					   \
	NOU::uint32 flags)																					   \
{																										   \
	NOE::NOE_CORE::Plugin::get()->receive(source, data, size, flags);									   \
}																										   \
																										   \
/*initialize*/																							   \
extern "C" NOU_FUNC NOU::uint32 noePluginInitialize(void * engineInstance)								   \
{																										   \
	NOE::NostraEngine *engine = reinterpret_cast<NOE::NostraEngine*>(engineInstance);					   \
																										   \
	NOE::NOE_CORE::Plugin::InitResult result = NOE::NOE_CORE::Plugin::get()->initialize(*engine);		   \
																										   \
	return NOU::uint32(result);																			   \
}																										   \
																										   \
/*terminate*/																							   \
extern "C" NOU_FUNC NOU::uint32 noePluginTerminate(void *engineInstance)								   \
{																										   \
	NOE::NostraEngine *engine = reinterpret_cast<NOE::NostraEngine*>(engineInstance);					   \
																										   \
	NOE::NOE_CORE::Plugin::InitResult result = NOE::NOE_CORE::Plugin::get()->terminate(*engine);		   \
																										   \
	return NOU::uint32(result);																			   \
}

#endif

extern "C" NOU_FUNC NOU::uint32 noePluginGetVersion();

extern "C" NOU_FUNC void noePluginStartup(NOU::uint32 id);
extern "C" NOU_FUNC void noePluginShutdown();
extern "C" NOU_FUNC void noePluginReceive();

extern "C" NOU_FUNC NOU::uint32 noePluginInitialize(void *engineInstance);
extern "C" NOU_FUNC NOU::uint32 noePluginTerminate(void *engineInstance);

namespace NOE::NOE_CORE
{
	class NOU_CLASS Plugin
	{
	public:
		using ID = NOU::uint32;

		enum class InitResult : NOU::uint32
		{
			SUCCESS = 0,
			WARNING = 1,
			FAILED = 2
		};

		enum class SendResult
		{
			SUCCESS = 0,
			PLUGIN_NOT_FOUND,
			INVALID_RECIPIENT
		};

	private:
		friend void ::noePluginStartup(NOU::uint32);

		static Plugin *s_plugin;

		ID m_id;

		void setID(ID id);

	public:
		static void set(Plugin *plugin);
		static Plugin* get();

		Plugin() = default;
		virtual ~Plugin() = default;

		Plugin(const Plugin &other) = delete;
		Plugin(Plugin &&) = delete;

		SendResult send(ID recipient, void *data, NOU::sizeType size, NOU::uint32 flags);
		ID getID() const;

		virtual const NOU::NOU_CORE::Version getVersion() const = 0;
		virtual InitResult initialize(NostraEngine &engineInstance) = 0;
		virtual InitResult terminate(NostraEngine &engineInstance) = 0;
		virtual void receive(ID source, void *data, NOU::sizeType size, NOU::uint32 flags) = 0;
	};
}