#ifndef NOU_CORE_CONFIGURATION_SOURCE_HPP
#define NOU_CORE_CONFIGURATION_SOURCE_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/Initializable.hpp"

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
	class NOU_CLASS ConfigurationSource : public Initializable
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

		/**
		\brief This enumeration provides different literals to identify the types in a configuration file.
		*/
		enum class TypeID
		{
			/**
			\brief The ID for the type <tt>NOU::boolean</tt>.
			*/
			BOOLEAN,

			/**
			\brief The ID for the type <tt>NOU::NOU_DAT_ALG::String8</tt>.
			*/
			STRING,

			/**
			\brief The ID for the type <tt>NOU::int32</tt>.
			*/
			INT_32,

			/**
			\brief The ID for the type <tt>NOU::int64</tt>.
			*/
			INT_64,

			/**
			\brief The ID for the type <tt>NOU::float32</tt>.
			*/
			FLOAT_32,

			/**
			\brief The ID for the type <tt>NOU::float64</tt>.
			*/
			FLOAT_64,

			/**
			\brief The ID for the type <tt>void*</tt>.
			*/
			NOT_SET,

			/**
			\brief An invalid type. This type is set for entries that are invalid for any reason.
			*/
			INVALID
		};

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

		/**
		\brief Initializes the configuration source.

		\details
		Initializes the configuration source.

		This member function is supposed to load the configuration file and, if this function succeeded, turn
		this instance into a state where it is possible to call any other function in this instance.

		\note
		The function getName() needs to be callable before this function was called.
		*/
		virtual Initializable::ExitCode initializeImpl() = 0;

		/**
		\brief Terminates the configuration source.

		\details
		Terminates the configuration source.

		This member function is supposed to close the connection to the configuration source file. It
		explicitly is NOT supposed to store data to that file.
		*/
		virtual Initializable::ExitCode terminateImpl() = 0;

		/**
		\brief Stores all entires in the configuration to its source file.

		\details
		Stores all entires in the configuration to its source file.

		This function is called by the function flush() and terminate() when the storage behavior 
		STORE_ON_TERMINATE is set.
		*/
		virtual void storeAll() = 0;

		/**
		\brief The name of the entry to check.

		\return True, if the entry with the specified name exists, false if not.

		\brief Returns whether an entry exists in this configuration source.

		\details
		Returns whether an entry exists in this configuration source. This function will be called by
		hasEntry().
		*/
		virtual NOU::boolean hasEntryImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const = 0;

		/**
		\brief The name of the entry to get the type of.

		\return The type of the entry with the specified name, or TypeID::INVALID if the entry does not exist.

		\brief Returns the type of an entry in the configuration source.

		\details
		Returns the type of an entry in the configuration source. This function will be called by getTypeOf().
		*/
		virtual TypeID getTypeOfImpl(const NOU::NOU_DAT_ALG::StringView8 &qualified) const = 0;

	public:
		/**
		\param storageBehavior The initial storage behavior.

		\brief Constructs a new instance.
		*/
		ConfigurationSource(StorageBehavior storageBehavior = 
			StorageBehavior::STORE_ON_TERMINATE | StorageBehavior::STORE_ON_FLUSH);

		/**
		\brief Returns a unique name of the configuration source.

		\details
		Returns a unique name of the configuration source.

		This name is the "source_name" part of the fully qualified name of an entry.

		If there are multiple sources that share the same name, the configuration manager will trigger a
		warning.
		*/
		virtual const NOU::NOU_DAT_ALG::StringView8& getName() = 0;

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

		/**
		\return A value from the Initializable::ExitCode enum, in accordance to what the different literals
		        are supposed to indicate as defined by the class Initializable.

		\brief Called when the source is initialized.

		\details
		Called when the source is initialized. As of now, this always and only calls initializeImpl().
		*/
		virtual Initializable::ExitCode initialize() override final;

		/**
		\brief Called when the source is terminated.

		\details Called when the source is terminated. As of now, this always calls terminateImpl() and, if 
		the storage behavior STORE_ON_TERMINATE is set, also calls storeAll().
		*/
		virtual void terminate() override final;

		/**
		\brief If the behavior STORE_ON_FLUSH is set, stores all of the entires to the source file.
		*/
		void flush();

		/**
		\brief The name of the entry to check.

		\return True, if the entry with the specified name exists, false if not.

		\brief Returns whether an entry exists in this configuration source.
		*/
		NOU::boolean hasEntry(const NOU::NOU_DAT_ALG::StringView8 &qualified) const;

		/**
		\brief The name of the entry to get the type of.

		\return The type of the entry with the specified name, or TypeID::INVALID if the entry does not exist.

		\brief Returns the type of an entry in the configuration source.
		*/
		TypeID getTypeOf(const NOU::NOU_DAT_ALG::StringView8 &qualified) const;
	};
}

#endif