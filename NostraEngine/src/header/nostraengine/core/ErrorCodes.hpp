#ifndef NOE_CORE_ERROR_CODES_HPP
#define NOE_CORE_ERROR_CODES_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOE::NOE_CORE
{
	/**
	\brief The error codes that are provided by the Nostra Engine for the Nostra Utils error handler.
	*/
	class ErrorCodes
	{
	public:
		enum Codes
		{
			/**
			\brief The execution of an SQL statement failed.
			*/
			SQL_EXECUTION_ERROR = NOU::NOU_CORE::ErrorCodes::LAST_ELEMENT + 1, //must be the first element

			/**
			\brief Not an actual error, but always the last element in the enum.
			*/
			LAST_ELEMENT
		};
	};

	class ErrorPool : public NOU::NOU_CORE::ErrorPool
	{
	private:
		NOU::NOU_DAT_ALG::Vector<NOU::NOU_CORE::Error> m_errors;

	public:
		ErrorPool();

		virtual const NOU::NOU_CORE::Error* queryError(NOU::NOU_CORE::Error::ErrorType id) const override;
	};
}

#endif