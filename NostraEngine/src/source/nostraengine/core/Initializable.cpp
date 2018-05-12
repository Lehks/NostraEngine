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

    /**
	\brief compares two Initializables depending on their priority
	\return true if the right one has higher priority, false if otherwise
	*/
	NOU::boolean Initializable::operator<(const Initializable &i) const
    {
        return this->getPriority() < i.getPriority();
    }
	
	/**
	\brief compares two Initializables depending on their priority
	\return true if the right one has higher priority, false if otherwise
	*/
	NOU::boolean Initializable::operator>(const Initializable &i) const
    {
        return this->getPriority() > i.getPriority();
    }
	/**
	\brief compares two Initializables depending on their priority
	\return true if the right one has higher or the same priority, false if otherwise
	*/
	NOU::boolean Initializable::operator<=(const Initializable &i) const
    {
        return this->getPriority() <= i.getPriority();
    }
	
	/**
	\brief compares two Initializables depending on their priority
	\return true if the left one has higher or the same priority, false if otherwise
	*/
	NOU::boolean Initializable::operator>=(const Initializable &i) const
    {
        return this->getPriority() >= i.getPriority();
    }    
	/**
	\brief compares two Initializables depending on their priority
	\return true if they have the same priority, false if otherwise
	*/
	NOU::boolean Initializable::operator==(const Initializable &i) const
    {
        return this->getPriority() == i.getPriority();
    }
	/**
	\brief subtracts two Initializables from each other
	\return left Initializables' priority - right Initializables' priority
	*/
	NOU::int64 Initializable::operator-(const Initializable &i) const
    {
        return this->getPriority() - i.getPriority();
    }
}