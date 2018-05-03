#ifndef NOE_CORE_EVENT_OBSERVER_HPP
#define NOE_CORE_EVENT_OBSERVER_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/EventObservable.hpp"

namespace NOE::NOE_CORE
{
	class EventObservable;

	class EventObserver
	{
		public:
		using ObservableVector = typename NOU::NOU_DAT_ALG::Vector<EventObservable>;
		using sizeType = typename nostra::utils::sizeType;

		private:
			ObservableVector m_subscriptions;
			sizeType findSubject(EventObservable & subject) const;

		public:
			bool subscribe(EventObservable & subject);
			bool unsubscribe(EventObservable & subject);
			bool isSubscribed(const EventObservable & subject) const;
			virtual bool observe(const Event & e);
			virtual ~EventObserver();
	};
}
#endif