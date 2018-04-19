#include "nostraengine/core/Initializable.hpp"

namespace NOE
{
    Initializable::Initializable(NOU:uint32 priority) : 
        m_priority(priority){}

    Initializable::Initializable(NOU::uint32 priority)
    {
        m_priority = priority;
    }

    NOU::uint32 Initializable::getPriority()
    {
        return m_priority;
    }
}