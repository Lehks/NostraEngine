#ifndef NOE_CORE_EVENT_CPP
#define NOE_CORE_EVENT_CPP

#include "nostraengine/core/Event.hpp"

namespace NOE::NOE_CORE
{
	Event::Event(EventObservable & origin)
	{
		this->origin = &origin;
	}


	Event::NouString Event::getName() const
	{
		return this->name;
	}


	EventObservable * Event::getOrigin()
	{
		return this->origin;
	}
}
#endif