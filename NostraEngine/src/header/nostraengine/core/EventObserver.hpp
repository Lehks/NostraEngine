#ifndef NOE_CORE_EVENT_OBSERVER_HPP
#define NOE_CORE_EVENT_OBSERVER_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/EventObservable.hpp"
#include "nostraengine/core/Event.hpp"


namespace NOE::NOE_CORE
{
	class EventObservable;
	class Event;

	class EventObserver
	{
		public:
		using ObservableVector = typename NOU::NOU_DAT_ALG::Vector<EventObservable>;
		using sizeType = typename nostra::utils::sizeType;

		private:
			/*
			\brief Holds a list of EventObservable references to which this observer has subscribed.
			*/
			ObservableVector m_subscriptions;


			/*
			\param  subject Reference of EventObservable.
			\return The index if found, -1 if not.

			\brief  Attempts to find the corresponding index of the given EventObservable that is stored in 
			        m_subscriptions.
			*/
			sizeType findSubject(EventObservable & subject) const;

		public:
			/*
			\param  subject Reference to EventObservable instance to which you want to subscribe.
			\return True on success, False if already subscribed.

			\brief  Subscribes the observer to a given observable instance. The observer will receive
			        events from the observable through the "observe" method.
			*/
			bool subscribe(EventObservable & subject);

			/*
			\param  subject Reference to EventObservable instance from which you want to unsubscribe.
			\return True on success, False if not subscribed.

			\brief  Unsubscribes the observer from a given observable. The observer will no longer receive events
				    from that observable.
			*/
			bool unsubscribe(EventObservable & subject);


			/*
			\param  subject The observable reference to check.
			\return True if subscribed, False if not.

			\brief  Checks if this observer is subscribed to the given observable.
			*/
			bool isSubscribed(const EventObservable & subject) const;


			/*
			\param  e The event that was triggered from a subscribed observable.
			\return True if the event was handled, False if not.

			\brief  All events coming from observables are passed to this method.
			        Return True at the end if you handled or consumed the event.
					Return False if you ignored the given event.
			*/
			virtual bool observe(const Event e);


			/*
			\brief  Overloaded to unsubscribe from all observables.
			*/
			virtual ~EventObserver();
	};
}
#endif