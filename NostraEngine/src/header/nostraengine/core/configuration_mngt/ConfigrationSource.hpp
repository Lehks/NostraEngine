#ifndef NOU_CORE_CONFIGURATION_SOURCE_HPP
#define NOU_CORE_CONFIGURATION_SOURCE_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOE::NOE_CORE
{
	/**
	\brief A class that represents a single configuration file. See the class documentation of ConfigurationManager
	for further details.
	*/
	class NOU_CLASS ConfigurationSource
	{
	public:
		/**
		\brief The different behaviors that a configuration source can have.

		\details
		The different behaviors that a configuration source can have. It is possible that a single source has multiple
		behaviors (the literals can combined using the "|" operator).

		\note
		The storage behavior works more as a promise that the configuration source will store the source file <b>at 
		least</b> as often as the behavior requires it, but it <b>may</b> also store the file more often. E.g. a 
		source that has only the behavior <tt>STORE_ON_TERMINATE</tt> set, <b>needs</b> to store the file when the 
		configuration management is being terminated, but it <b>may</b> also store the file on flush or on update.
		This is to allow more complex sources, like databases, where a user may not have full control on when the
		source is being stored.
		*/
		class StorageBehavior
		{
			enum Value
			{
				/**
				\brief The entires will be stored to the source file when ConfigurationManager::terminate() is getting
				called.
				*/
				STORE_ON_TERMINATE = 2,

				/**
				\brief The entires will be stored to the source file when ConfigurationManager::flush() is getting
				called.
				*/
				STORE_ON_FLUSH     = 4,

				/**
				\brief The entires will be stored whenever they are updated. This behavior will overshadow all other
				behaviors (there will never be something to store when the configuration manager is being flushed or
				the engine is being terminated, since the changes will be written immediately).
				*/
				STORE_ON_UPDATE    = 8
			};
		};

	private:

		/**
		\brief The storage behavior of the source.
		*/
		StorageBehavior::Value m_storageBehavior;
	};
}

#endif