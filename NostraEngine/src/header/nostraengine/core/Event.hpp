#ifndef NOE_CORE_EVENT_HPP
#define NOE_CORE_EVENT_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"


namespace NOE::NOE_CORE
{
	class EventObservable;

	class Event
	{
		public:
			using NouString = typename NOU::NOU_DAT_ALG::String<NOU::char8>;

		private:
			NouString name;
			EventObservable *origin;

		public:
			Event(EventObservable & observable);
			NouString getName() const;
			EventObservable * getOrigin();
	};
}
#endif