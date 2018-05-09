#ifndef NOE_CORE_RESOURCE_TYPE_HPP
#define NOE_CORE_RESOURCE_TYPE_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOE::NOE_CORE
{
	class NOU_CLASS ResourceType
	{
	public:
		using ID = NOU::int32;

		static constexpr ID INVALID_ID = 0;

		static const NOU::NOU_DAT_ALG::StringView8 SQL_EXISTS_TYPE;

		static const NOU::NOU_DAT_ALG::StringView8 SQL_GENERIC;

		static const NOU::NOU_DAT_ALG::StringView8 SQL_NAME_NAME;

		static const NOU::NOU_DAT_ALG::StringView8 SQL_DESCRIPTION_NAME;

	private:
		/**
		\brief The ID of the type.
		*/
		mutable ID m_id; //mutable for isValid()

						 /**
						 \param attribute The name of the attribute to get the value from.

						 \return The value of the attribute.

						 \brief Queries the value of the attribute \p attribute of the type.
						 */
		NOU::NOU_DAT_ALG::String8 getAttribute(const NOU::NOU_DAT_ALG::StringView8 &attribute) const;

		NOU::boolean checkIfExsists() const;
	public:
		explicit ResourceType(ID id = INVALID_ID);

		ID getID() const;

		NOU::NOU_DAT_ALG::String8 getName() const;

		NOU::NOU_DAT_ALG::String8 getDescription() const;

		/**
		\return True, if the type is valid, false if not.

		\brief Returns whether the type is valid (it exists in the database) or not.
		*/
		NOU::boolean isValid() const;

		/**
		\return isValid()

		\brief Same as isValid()
		*/
		operator NOU::boolean() const;
	};

	constexpr typename ResourceType::ID ResourceType::INVALID_ID;
}

#endif