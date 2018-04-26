#ifndef NOE_CORE_EVENT_OBSERVABLE_CPP
#define NOE_CORE_EVENT_OBSERVABLE_CPP

#include "nostraengine/core/EventObservable.hpp"


namespace NOE::NOE_CORE
{
	bool EventObservable::registerObserver(const EventObserver & observer)
	{
		if (this->hasObserver(observer)) {
			return false;
		}

		this->observers.push(observer);

		return true;
	}


	bool EventObservable::unregisterObserver(const EventObserver & observer)
	{
		if (!this->hasObserver(observer)) {
			return false;
		}

		NOU::int32 limit = observers.size();

		for (NOU::int32 i = 0; i < limit; i++)
		{
			if (observers[i] == observer) {
				observers.remove(i);
				break;
			}
		}

		return true;
	}


	bool EventObservable::hasObserver(const EventObserver & observer) const
	{
		NOU::int32 limit = observers.size();
		
		for (NOU::int32 i = 0; i < limit; i++)
		{
			/*if (observers[i] == observer) {
				return true;
			}*/
		}
		
		return false;
	}


	bool EventObservable::triggerEvent(NouString name) const
	{

	}
}
#endif