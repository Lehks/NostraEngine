#include "nostraengine/core/Updatable.hpp"
#include "nostraengine/core/NostraEngine.hpp"


namespace NOE::NOE_CORE
{
    void Updatable::earlyUpdate()
    {

    }

    void Updatable::lateUpdate()
    {

    }

    Updatable::Updatable()
    {
        NostraEngine::get().addUpdatable(this);
    }

    Updatable::~Updatable()
    {
        NostraEngine::get().removeUpdatable(this);
    }
}