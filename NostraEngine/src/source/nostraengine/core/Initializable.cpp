#include "nostraengine/core/Initializable.hpp"

#include "nostraengine/core/NostraEngine.hpp"

namespace NOE::NOE_CORE
{


    Initializable::Initializable(NOU::uint32 priority) :
        m_priority(priority)
        { 
            NostraEngine::get().addInitializable(this);
        }

    void Initializable::setPriority(NOU::uint32 priority)
    {
        m_priority = priority;
    }

    NOU::uint32 Initializable::getPriority() const
    {
        return m_priority;
    }

	NOU::boolean Initializable::operator<(const Initializable &i) const
    {
        return this->getPriority() < i.getPriority();
    }

	NOU::boolean Initializable::operator>(const Initializable &i) const
    {
        return this->getPriority() > i.getPriority();
    }

	NOU::boolean Initializable::operator<=(const Initializable &i) const
    {
        return this->getPriority() <= i.getPriority();
    }

	NOU::boolean Initializable::operator>=(const Initializable &i) const
    {
        return this->getPriority() >= i.getPriority();
    }    

	NOU::boolean Initializable::operator==(const Initializable &i) const
    {
        return this->getPriority() == i.getPriority();
    }

	NOU::int64 Initializable::operator-(const Initializable &i) const
    {
        return this->getPriority() - i.getPriority();
    }

    NOU::int32 Initializable::preInitialize()
    {
        return 0;
    }

    NOU::int32 Initializable::postInitialize()
    {
        return 0;
    }
}