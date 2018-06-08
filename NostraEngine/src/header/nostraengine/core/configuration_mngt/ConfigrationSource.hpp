#ifndef NOU_CORE_CONFIGURATION_SOURCE_HPP
#define NOU_CORE_CONFIGURATION_SOURCE_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOE::NOE_CORE
{
	namespace internal
	{
		/**
		\brief The different behaviors that a configuration source can have.

		\details
		The different behaviors that a configuration source can have. It is possible that a single source has
		multiple behaviors (the literals can combined using the "|" operator).

		\note
		The storage behavior works more as a promise that the configuration source will store the source file 
		<b>at least</b> as often as the behavior requires it, but it <b>may</b> also store the file more 
		often. E.g. a source that has only the behavior <tt>STORE_ON_TERMINATE</tt> set, <b>needs</b> to store
		the file when the configuration management is being terminated, but it <b>may</b> also store the file 
		on flush or on update. This is to allow more complex sources, like databases, where a user may not 
		have full control on when the source is being stored.
		*/
		enum class StorageBehavior
		{
			/**
			\brief The entires will be stored to the source file when ConfigurationManager::terminate() is 
			getting called.
			*/
			STORE_ON_TERMINATE = 1,

			/**
			\brief The entires will be stored to the source file when ConfigurationManager::flush() is getting
			called.
			*/
			STORE_ON_FLUSH = 2,

			/**
			\brief The entires will be stored whenever they are updated. This behavior will overshadow all 
			other behaviors (there will never be something to store when the configuration manager is being 
			flushed or the engine is being terminated, since the changes will be written immediately).
			*/
			STORE_ON_UPDATE = 4
		};

		//implement here, a) b/c of constexpr, and b) b/c ConfigurationSource::ConfigurationSource() uses it

		/**
		\param a The first storage behavior.
		\param b The second storage behavior.

		\return a | b

		\brief Allows bitwise OR for the literals in StorageBehavior.
		*/
		constexpr StorageBehavior operator | (StorageBehavior a, StorageBehavior b)
		{
			using UnderlType = NOU::NOU_CORE::UnderlyingType_t<StorageBehavior>;

			return static_cast<StorageBehavior>(static_cast<UnderlType>(a) | static_cast<UnderlType>(b));
		}

		/**
		\param a The first storage behavior.
		\param b The second storage behavior.

		\return a & b

		\brief Allows bitwise AND for the literals in StorageBehavior.
		*/
		constexpr StorageBehavior operator & (StorageBehavior a, StorageBehavior b)
		{
			using UnderlType = NOU::NOU_CORE::UnderlyingType_t<StorageBehavior>;

			return static_cast<StorageBehavior>(static_cast<UnderlType>(a) & static_cast<UnderlType>(b));
		}

		/**
		\param a The first storage behavior.
		\param b The second storage behavior.

		\return ~a

		\brief Allows bitwise NOT for the literals in StorageBehavior.
		*/
		constexpr StorageBehavior operator ~ (StorageBehavior a)
		{
			using UnderlType = NOU::NOU_CORE::UnderlyingType_t<StorageBehavior>;

			return static_cast<StorageBehavior>(~static_cast<UnderlType>(a));
		}
	}

	/**
	\brief A class that represents a single configuration file. See the class documentation of 
	ConfigurationManager for further details.
	*/
	class NOU_CLASS ConfigurationSource
	{
	public:
		/**
		\brief An alias for internal::StorageBehavior in this class scope.

		\details
		An alias for internal::StorageBehavior in this class scope.

		The fact that internal::StorageBehavior is implemented in its namespace and not in this class is
		for technical and aesthetic reasons. Those are:
		1. The enumeration needs some operators overloaded. The bitwise-or operator is used in this classes'
		   constructor, hence at least this operator needs to be defined at that point. If the enum was
		   defined in this class, the definition of this operator function needs to be in this class as well.
		   However, this is impossible, as C++ would assume that, if the overloading of the operator is done 
		   in this class, the overload is of the signature <tt>operator | (const ConfigurationSource&, 
		   StorageBehavior)</tt> and not <tt>operator | (StorageBehavior, StorageBehavior)</tt>.
		2. The coding-conventions that are used to write this engine forbid the definition of a member
		   function in its class.
		*/
		using StorageBehavior = internal::StorageBehavior;

	private:

		/**
		\brief The storage behavior of the source.
		*/
		StorageBehavior m_storageBehavior;

	protected:
		/**
		\brief Adds the passed storage behavior(s) to the already set behaviors.

		\details
		Adds the passed storage behavior(s) to the already set behaviors.
		Setting behaviors twice has no additional effect.

		By default, this method is protected, hence it is not visible from the outside. This can of
		course be changed by overriding this method in a child class and making that override public.
		*/
		void addStorageBehavior(StorageBehavior behavior);

		/**
		\brief Removes the passed storage behavior(s) to the already set behaviors.

		\details
		Removes the passed storage behavior(s) to the already set behaviors.
		Removing behaviors twice has no additional effect.

		By default, this method is protected, hence it is not visible from the outside. This can of
		course be changed by overriding this method in a child class and making that override public.
		*/
		void removeStorageBehavior(StorageBehavior behavior);

	public:
		/**
		\param storageBehavior The initial storage behavior.

		\brief Constructs a new instance.
		*/
		ConfigurationSource(StorageBehavior storageBehavior = 
			StorageBehavior::STORE_ON_TERMINATE | StorageBehavior::STORE_ON_FLUSH);

		/**
		\return The current storage behavior(s).

		\brief Returns the current storage behavior(s).

		\note
		Often, the returned value of this method is not suitable whether the source has a certain behavior 
		set, e.g. the code
		\code{.cpp}
		//"source" is an instance of a child class of this class
		source.getStorageBehavior() == StorageBehavior::STORE_ON_TERMINATE
		\endcode
		would return false, if both the behaviors STORE_ON_TERMINATE and STORE_ON_FLUSH are set. For that 
		purpose, hasStorageBehavior() is better suited.
		*/
		StorageBehavior getStorageBehavior() const;

		/**
		\param storageBehavior The storage behavior(s) to check.

		\return True, if the source has the passed storage behavior(s), false if not.

		\brief Checks whether the source has the passed storage behavior(s).
		*/
		NOU::boolean hasStorageBehavior(StorageBehavior storageBehavior) const;
	};
}

#endif