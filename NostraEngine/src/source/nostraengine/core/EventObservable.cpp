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

		this->m_observers.push(observer);

		return true;
	}


	bool EventObservable::unregisterObserver(EventObserver & observer)
	{
		sizeType idx = this->findObserver(observer);

		if (idx == -1) {
			return false;
		}

		observer.unsubscribe(*this);

		return true;
	}


	bool EventObservable::hasObserver(const EventObserver & observer) const
	{
		for (sizeType i = 0; i < this->m_observers.size(); i++)
		{
			if (&this->m_observers.at(i) == &observer) {
				return true;
			}
		}

		return false;
	}


	EventObservable::sizeType EventObservable::triggerEvent(const NouString name) const
	{
		if (!this->eventExists(name)) {
			return 0;
		}

		Event e = this->getEvent(name);
		sizeType count = 0;
		EventObserver observer;

		for (sizeType i = 0; i < this->m_observers.size(); i++)
		{
			observer = this->m_observers.at(i);

			if (observer.observe(e)) {
				count++;
			}
		}

		return count;
	}


	EventObservable::sizeType EventObservable::findObserver(const EventObserver & observer) const
	{
		for (sizeType i = 0; i < this->m_observers.size(); i++)
		{
			if (&this->m_observers.at(i) == &observer) {
				return i;
			}
		}

		return -1;
	}


	void EventObservable::addEvent(const NouString name, Event & e)
	{
		if (this->eventExists(name)) {
			return;
		}

		this->m_events.insert(std::make_pair(name, e));
	}


	void EventObservable::removeEvent(const NouString name)
	{
		if (this->m_events.count(name) > 0) {
			return;
		}

		this->m_events.erase(name);
	}


	bool EventObservable::eventExists(const NouString name) const
	{
		std::unordered_map<NouString, Event>::const_iterator found = this->m_events.find(name);

		return (found != this->m_events.end());
	}


	Event EventObservable::getEvent(const NouString name) const
	{
		std::unordered_map<NouString, Event>::const_iterator e = this->m_events.find(name);

		if (e != this->m_events.end()) {
			return e->second;
		}

		return Event(*this);
	}


	EventObservable::~EventObservable()
	{
		// Tell all observers to unsubscribe
		EventObserver obs;

		for (sizeType i = 0; i < this->m_observers.size(); i++)
		{
			obs = this->m_observers.at(i);

			obs.unsubscribe(*this);
		}
	}
}
#endif