#ifndef NOE_CORE_EVENT_HPP
#define NOE_CORE_EVENT_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/EventObservable.hpp"


namespace NOE::NOE_CORE
{
	class EventObservable;


	class Event
	{
		public:
			using NouString = typename NOU::NOU_DAT_ALG::String<NOU::char8>;

		private:
			/*
			\brief The name of this event.
			*/
			NouString name;

			/*
			\brief The observable that created this event.
			*/
			EventObservable *origin;

		public:
			/*
			\param origin Instance of the observable which creates this event.

			\brief 
			*/
			Event(EventObservable & origin);


			/*
			\return The name of this event.

			\brief Returns the name of this event.
			*/
			NouString getName() const;

			/*
			\return The observable instance which created this event.

			\brief  Returns the origin of this event.
			*/
			EventObservable * getOrigin();
	};
}
#endif