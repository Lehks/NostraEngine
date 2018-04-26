#ifndef NOE_CORE_EVENT_OBSERVER_HPP
#define NOE_CORE_EVENT_OBSERVER_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/EventObservable.hpp"

namespace NOE::NOE_CORE
{
	class EventObserver
	{
		public:
			bool subscribe(const EventObservable & subject) const;
			bool unsubscribe(const EventObservable & subject) const;
			bool isSubscribed(const EventObservable & subject) const;
			virtual bool observe(const Event & e);
	};
}
#endif