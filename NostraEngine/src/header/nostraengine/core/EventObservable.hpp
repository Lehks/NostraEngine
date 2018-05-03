#ifndef NOE_CORE_EVENT_OBSERVABLE_HPP
#define NOE_CORE_EVENT_OBSERVABLE_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/EventObserver.hpp"
#include "nostraengine/core/Event.hpp"
#include <unordered_map>


namespace NOE::NOE_CORE
{
	class EventObservable
	{
		public:
			using NouString = typename NOU::NOU_DAT_ALG::String<NOU::char8>;
			using ObsVec    = typename NOU::NOU_DAT_ALG::Vector<EventObserver>;
			using sizeType  = typename nostra::utils::sizeType;

		private:
			std::unordered_map<NouString, Event> m_events;
			ObsVec m_observers;
			
			sizeType findObserver(const EventObserver & observer) const;

			void addEvent(const NouString name, Event & e);
			void removeEvent(const NouString name);
			bool eventExists(const NouString name) const;
			Event getEvent(const NouString name) const;

		public:
			bool registerObserver(const EventObserver & observer);
			bool unregisterObserver(EventObserver & observer);
			bool hasObserver(const EventObserver & observer) const;
			sizeType triggerEvent(const NouString name) const;
			virtual ~EventObservable();
	};
}
#endif