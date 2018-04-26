#ifndef NOE_CORE_EVENT_OBSERVER_CPP
#define NOE_CORE_EVENT_OBSERVER_CPP

#include "nostraengine/core/EventObserver.hpp"


namespace NOE::NOE_CORE
{
	bool EventObserver::subscribe(const EventObservable & subject) const
	{
		if (this->isSubscribed(subject)) {
			return false;
		}

		subject.registerObserver(this);

		return true;
	}

	bool EventObserver::unsubscribe(const EventObservable & subject) const
	{
		if (!this->isSubscribed(subject)) {
			return false;
		}

		subject.unregisterObserver(this);

		return true;
	}

	bool EventObserver::isSubscribed(const EventObservable & subject) const
	{
		return subject.hasObserver(this);
	}
}
#endif