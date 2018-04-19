#ifndef NOE_CORE_INITIALIZABLE_HPP
#define NOE_CORE_INITIALIZABLE_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"

namespace NOE {

	class NOU_CLASS Initializable 
	{
		private:
			NOU::uint32 m_priority;

		public:
			Initializable(NOU::uint32 priority = 0);

			virtual NOU::int32 initialize() = 0;
			virtual NOU::int32 terminate()  = 0;

			void setPriority(NOU::uint32 priority);
			NOU::uint32 getPriority();
	};
}
#endif