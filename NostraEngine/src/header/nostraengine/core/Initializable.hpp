#ifndef NOE_CORE_INITIALIZABLE_HPP
#define NOE_CORE_INITIALIZABLE_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"


/**
\file core/NostraEngine

\author	 Leslie Marxen
\version 1.0.0
\since   1.0.0

\brief This File provides an interface for classes that need to be Initialized
*/
namespace NOE {
	/**
	\brief This class will be used as interface for other subclasses that need to be initialized before specific tasks can happen.
		   It also provides a constructor which sets a basic priority for when some objects have to be initialized before others.
	*/
	class NOU_CLASS Initializable 
	{
		private:
			/**
			\brief The priority rating of the current object.
			*/
			NOU::uint32 m_priority;

		public:
			/**
			\brief The Constructor of the Initializable Interface
			\param priority sets the internal priority rating of the object
			*/
			Initializable(NOU::uint32 priority = 0);

			/**
			\brief If something has to be initialized before usage it has to be called in this method
			*/
			virtual NOU::int32 initialize() = 0;

			/**
			\brief If something has to be terminated after usage it has to be called in this method
			*/
			virtual NOU::int32 terminate()  = 0;


			/**
			\brief sets the priority rating
			\param priority the priority rating
			*/
			void setPriority(NOU::uint32 priority);

			/**
			\brief gets the priority rating
			\return the priority rating
			*/
			NOU::uint32 getPriority();
	};
}
#endif