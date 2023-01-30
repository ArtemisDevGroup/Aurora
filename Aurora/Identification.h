#ifndef __AURORA_IDENTIFICATION_H__
#define __AURORA_IDENTIFICATION_H__

#include "Definitions.h"

namespace Aurora {
	struct AURORA_API IdentityDescriptor {
		DWORD dwIdentifier;
		CHAR szTypeName[MAX_NAME];
		DWORD dwObjectSize;
	};

	class AURORA_API Identifier {
		IdentityDescriptor desc;

		static constexpr void IdHelper_AddToList(_In_ const Identifier& id);
		static constexpr bool IdHelper_IsUnique(_In_ const Identifier& id);
		static constexpr void IdHelper_Rotl(_Inout_ Identifier& id);
	public:
		constexpr Identifier();

		static constexpr Identifier Create(_In_z_ LPCSTR lpTypeName, _In_ DWORD dwObjectSize);
		static constexpr Identifier CreateUnique(_In_z_ LPCSTR lpTypeName, _In_ DWORD dwObjectSize);

		constexpr const IdentityDescriptor* GetDesc() const;

		constexpr bool operator==(const Identifier&);
		constexpr bool operator!=(const Identifier&);
	};
}

#endif // !__AURORA_IDENTIFICATION_H__