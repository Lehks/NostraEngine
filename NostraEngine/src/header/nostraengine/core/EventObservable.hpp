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
			using ObsVec = typename NOU::NOU_DAT_ALG::Vector<EventObserver>;

		private:
			unordered_map<NouString, Event *> events;
			ObsVec observers;

		public:
			bool registerObserver(const EventObserver & observer);
			bool unregisterObserver(const EventObserver & observer);
			bool hasObserver(const EventObserver & observer) const;
			bool triggerEvent(NouString name) const;
	};
}
#endif