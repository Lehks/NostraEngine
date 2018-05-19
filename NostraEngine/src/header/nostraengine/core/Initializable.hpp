#ifndef NOE_CORE_INITIALIZABLE_HPP
#define NOE_CORE_INITIALIZABLE_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostrautils/NostraUtils.hpp"



/**
\file core/NostraEngine

\author	 Leslie Marxen
\version 1.0.0
\since   1.0.0

\brief This File provides an interface for classes that need to be Initialized
*/
namespace NOE::NOE_CORE {


	enum class ExitCode
	{
		SUCCESS,
		WARNING,
		ERROR
	};


	/**
	\brief This class will be used as interface for other subclasses that need to be initialized before specific tasks can happen.
		   It also provides a constructor which sets a basic priority for when some objects have to be initialized before others.
	*/
	class NOU_CLASS Initializable 
	{
		private:
			/**
			\brief The priority rating of the current object. 0 is the lowest priority where -1 is the highest
			*/
			NOU::uint32 m_priority;
			/**
			\brief The size of the HaspMap.
			*/
			static const NOU::int32 S_MAP_SIZE = 1000;
			/**
			\brief The HashMap to sore variables such as Path's.
			*/
			static NOU::NOU_DAT_ALG::HashMap<NOU::NOU_DAT_ALG::String8, NOU::NOU_DAT_ALG::String8> s_hashMap;
		public:
			/**
			\brief The Constructor of the Initializable Interface
			\param priority sets the internal priority rating of the object
			*/
			Initializable(NOU::uint32 priority = -1);

			/**
			\brief The destructor of the initializable Interface
			*/
			~Initializable();

			/**
			\brief returns a name given to an instance of the class. Necessary for errorhandling
			*/
			virtual NOU::NOU_DAT_ALG::StringView8 getName() = 0;

			/**
			\brief If something has to be initialized before usage it has to be called in this method
			*/
			virtual ExitCode initialize() = 0;

			/**
			\brief If something has to be done after the init stage but before the main loop
				   it has to be called in this method
			*/
			virtual ExitCode postInitialize();

			/**
			\brief If something has to be terminated after usage it has to be called in this method
			*/
			virtual void terminate()  = 0;


			/**
			\brief sets the priority rating
			\param priority the priority rating
			*/
			void setPriority(NOU::uint32 priority);

			/**
			\brief gets the priority rating
			\return the priority rating
			*/
			NOU::uint32 getPriority() const;

			/**
			\brief Returns the static HashMap as a reference.
			\return the HashMap reference
			*/
			NOU::NOU_DAT_ALG::HashMap<NOU::NOU_DAT_ALG::String8 ,NOU::NOU_DAT_ALG::String8> & getMap();

			/**
			\brief compares two Initializables depending on their priority
			\return true if the right one has higher priority, false if otherwise
			\param i the right operator
			*/
			NOU::boolean operator<(const Initializable &i) const;
			
			/**
			\brief compares two Initializables depending on their priority
			\return true if the right one has higher priority, false if otherwise
			\param i the right operator
			*/
			NOU::boolean operator>(const Initializable &i) const;

			/**
			\brief compares two Initializables depending on their priority
			\return true if the right one has higher or the same priority, false if otherwise
			\param i the right operator
			*/
			NOU::boolean operator<=(const Initializable &i) const;
			
			/**
			\brief compares two Initializables depending on their priority
			\return true if the left one has higher or the same priority, false if otherwise
			\param i the right operator
			*/
			NOU::boolean operator>=(const Initializable &i) const;

			/**
			\brief compares two Initializables depending on their priority
			\return true if they have the same priority, false if otherwise
			\param i the right operator
			*/
			NOU::boolean operator==(const Initializable &i) const;
			/**
			\brief subtracts two Initializables from each other
			\return left Initializables' priority - right Initializables' priority
			\param i the right operator
			*/
			NOU::int64 operator-(const Initializable &i) const;
	};
}
#endif