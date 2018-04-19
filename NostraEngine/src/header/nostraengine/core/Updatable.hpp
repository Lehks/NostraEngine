#ifndef NOE_CORE_UPDATABLE_HPP
#define NOE_CORE_UPDATABLE_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostrautils/StdIncludes.hpp"

/**
\author  Leslie Marxen
\since   0.1.0
\version 0.1.0
\brief  This file provides an abstract class that provides some functionallity
        in terms of Updatabillity for later Objects 
 */



namespace NOE
{

    class NOU_CLASS Updatable
    {
        public:
            
            /**
            \brief Abstract function that defines behaivour that needs to be executed before every render frame
            */
            virtual void earlyUpdate();
            /**
            \brief Abstract function that defines some functionallity the implemented object does every Render iteration
            \detail For example if a player wants to move the ingame Player object, the object has to scan for input every
                    frame
            */
            virtual void update() = 0;
            virtual void lateUpdate();
    };
}
#endif