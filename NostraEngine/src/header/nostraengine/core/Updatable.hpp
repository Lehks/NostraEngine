#ifndef NOE_CORE_UPDATABLE_HPP
#define NOE_CORE_UPDATABLE_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostrautils/StdIncludes.hpp"

class NOU_CLASS Updatable{
public:
    virtual void earlyUpdate();
    virtual void update() = 0;
    virtual void lateUpdate();
};

#endif