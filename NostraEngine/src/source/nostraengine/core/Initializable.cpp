#include "nostraengine/core/Initializable.hpp"

namespace NOE::NOE_CORE
{
	Initializable::Initializable(NOU::uint32 priority) :
        m_priority(priority){}

    void Initializable::setPriority(NOU::uint32 priority)
    {
        m_priority = priority;
    }

    NOU::uint32 Initializable::getPriority()
    {
        return m_priority;
    }
}