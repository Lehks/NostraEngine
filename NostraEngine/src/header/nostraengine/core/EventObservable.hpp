#ifndef NOE_CORE_EVENT_OBSERVABLE_HPP
#define NOE_CORE_EVENT_OBSERVABLE_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/EventObserver.hpp"
#include "nostraengine/core/Event.hpp"
#include <unordered_map>


namespace NOE::NOE_CORE
{
	class EventObserver;
	class Event;


	struct NouStringHash
	{
		std::size_t operator()(const NOU::NOU_DAT_ALG::String<NOU::char8> &str) const
		{
			return std::hash<std::string>()(std::string(str.rawStr()));
		}
	};


	class EventObservable
	{
		public:
			using NouString = typename NOU::NOU_DAT_ALG::String<NOU::char8>;
			using ObsVec    = typename NOU::NOU_DAT_ALG::Vector<EventObserver>;
			using sizeType  = typename nostra::utils::sizeType;

		private:
			/*
			\brief  Maps Event instances to a string identifier.
			*/
			std::unordered_map<NouString, Event, NouStringHash> m_events;

			/*
			\brief  Vector holding all observers which are subscribed to this observable.
			*/
			ObsVec m_observers;
			
			/*
			\param observer Observer instance
			\return         The corresponding index of the observer if found, -1 otherwise.

			\brief          Attempts to find the index for the given observer in m_observers.
			*/
			sizeType findObserver(const EventObserver & observer) const;


			/*
			\param name A unique name for the event
			\param e    The Event instance

			\brief      Registers an event in m_events. Once registered, it can be triggered using 
			            the triggerEvent() method.
			\
			*/
			void addEvent(const NouString name, Event & e);


			/*m
			\param name The name of the event.

			\brief      Removes an event from m_events.
			*/
			void removeEvent(const NouString name);


			/*
			\param name The name of the event.
			\return     True if found, False if not.

			\brief      Checks if a given event name is registered in m_events.
			*/
			bool eventExists(const NouString name) const;


			/*
			\param name The name of the event.
			\return     The instance of the Event that corresponds to the given name.

			\brief      Returns an event instance that was previously stored via addEvent().
			*/
			Event getEvent(const NouString & name);

		public:
			/*
			\param  observer The observer instance to register
			\return          True on success, False if already registered.

			\brief Registers the given Observer to this Observable. The observer will then receive
			       any future event triggered by this instance.
			*/
			bool registerObserver(const EventObserver & observer);


			/*
			\param  observer The observer instance to unregister.
			\return          True on success, False if not subscribed.

			\brief  Removes the given observer from this observable. It will no longer receive
				    any event updates.
			*/
			bool unregisterObserver(EventObserver & observer);


			/*
			\param  observer The observer instance to look for.
			\return          True if found, False otherwise.

			\brief  Checks if the given observer is subscribed to this instance.
			*/
			bool hasObserver(const EventObserver & observer) const;


			/*
			\param  name The event name
			\return      The amount of times the event has been handled by observers.

			\brief  Triggers an event. The event must have previously been registered
					through the addEvent() method.
			*/
			sizeType triggerEvent(const NouString name);


			/*
			\brief  Overload to disconnect all observers.
			*/
			virtual ~EventObservable();
	};
}
#endif