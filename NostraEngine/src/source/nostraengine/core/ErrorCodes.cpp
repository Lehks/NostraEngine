#include "nostraengine/core/ErrorCodes.hpp"

namespace NOE::NOE_CORE
{
	ErrorPool::ErrorPool() :
		m_errors(ErrorCodes::LAST_ELEMENT - ErrorCodes::SQL_EXECUTION_ERROR)
	{
		m_errors.push(NOU::NOU_CORE::Error("SQL_EXECUTION_ERROR", ErrorCodes::SQL_EXECUTION_ERROR));
	}

	const NOU::NOU_CORE::Error* ErrorPool::queryError(NOU::NOU_CORE::Error::ErrorType id) const
	{
		if (id >= ErrorCodes::SQL_EXECUTION_ERROR && id < ErrorCodes::LAST_ELEMENT)
			return &m_errors[id];
		else
			return nullptr;
	}
}