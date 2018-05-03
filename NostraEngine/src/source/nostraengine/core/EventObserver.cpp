#ifndef NOE_CORE_EVENT_OBSERVER_CPP
#define NOE_CORE_EVENT_OBSERVER_CPP

#include "nostraengine/core/EventObserver.hpp"


namespace NOE::NOE_CORE
{
	bool EventObserver::subscribe(EventObservable & subject)
	{
		if (this->isSubscribed(subject)) {
			return false;
		}
		
		if (subject.registerObserver(*this)) {
			this->m_subscriptions.push(subject);
		}

		return true;
	}


	bool EventObserver::unsubscribe(EventObservable & subject)
	{
		sizeType idx = this->findSubject(subject);

		if (idx == -1) {
			return false;
		}

		this->m_subscriptions.remove(idx);
		subject.unregisterObserver(*this);

		return true;
	}


	bool EventObserver::isSubscribed(const EventObservable & subject) const
	{
		for (sizeType i = 0; i < this->m_subscriptions.size(); i++)
		{
			if (&this->m_subscriptions.at(i) == &subject) {
				return true;
			}
		}

		return false;
	}


	EventObserver::sizeType EventObserver::findSubject(EventObservable & subject) const
	{
		for (sizeType i = 0; i < this->m_subscriptions.size(); i++)
		{
			if (&this->m_subscriptions.at(i) == &subject) {
				return i;
			}
		}

		return -1;
	}


	EventObserver::~EventObserver()
	{
		// Unsubscribe from all observables
		for (sizeType i = 0; i < this->m_subscriptions.size(); i++)
		{
			this->m_subscriptions.at(i).unregisterObserver(*this);
		}
	}
}
#endif