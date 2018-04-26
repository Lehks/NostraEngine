#ifndef NOE_CORE_EVENT_HPP
#define NOE_CORE_EVENT_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/EventObservable.hpp"


namespace NOE::NOE_CORE
{
	class Event
	{
		public:
			using NouString = typename NOU::NOU_DAT_ALG::String<NOU::char8>;

		private:
			NouString name;
			EventObservable * subject;
	};
}
#endif