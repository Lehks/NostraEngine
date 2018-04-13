#ifndef NOE_CORE_INITIALIZABLE_HPP
#define NOE_CORE_INITIALIZABLE_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostrautils/core/StdIncludes.hpp"
#include "nostraengine/core/StdIncludes.hpp"

namespace NOE {

	class NOU_CLASS Initializable {

		Initializable();

		virtual NOU::int32 initialize() = 0;
		virtual NOU::int32 terminate()  = 0;
	};
}
#endif