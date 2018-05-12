#include "nostraengine/core/NostraEngine.hpp"

int main()
{
    NOE::NOE_CORE::NostraEngine::setActiveInstance(*(NOE::NOE_CORE::NostraEngine::createInstance()));
    NOE::NOE_CORE::NostraEngine &engine = NOE::NOE_CORE::NostraEngine::get();


    return 0;
}