#ifndef NOE_CORE_UPDATABLE_HPP
#define NOE_CORE_UPDATABLE_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"

/**
\author  Leslie Marxen
\since   0.1.0
\version 0.1.0
\brief  This file provides an abstract class that provides some functionallity
        in terms of Updatabillity for later Objects 
 */



namespace NOE::NOE_CORE
{

    class Updatable
    {
        public:
            
            /**
            \brief  Abstract function that defines behaivour that needs to be executed before every render frame.
                    Defaults to an enmpty function, so nothing will be done by default. Can be overwritten to add 
                    unique behaviour
            */
			NOE_FUNC virtual void earlyUpdate();
            /**
            \brief Abstract function that defines some functionallity the implemented object does every Render iteration
            \detail For example if a player wants to move the ingame Player object, the object has to scan for input every
                    frame
            */
            virtual void update() = 0;
            /**
            \brief  Abstract function that defines behaivour that needs to be executed after every render frame.
                    Defaults to an enmpty function, so nothing will be done by default. Can be overwritten to add 
                    unique behaviour
            */
			NOE_FUNC virtual void lateUpdate();

            /**
            \brief A basic constructor for this interface, it suits no purpose than automatically adding the current object to the update vector
            */
			NOE_FUNC Updatable();
        
            /**
            \brief A basic destructor for this interface, it suits no purpose than automatically removing the current object from the update vector
            */
			NOE_FUNC ~Updatable();
    };
}
#endif