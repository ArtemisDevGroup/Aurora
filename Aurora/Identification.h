#ifndef __AURORA_IDENTIFICATION_H__
#define __AURORA_IDENTIFICATION_H__

#include "Definitions.h"
#include "String.h"

namespace Aurora {
	struct AURORA_API IdentityDescriptor {
		A_DWORD dwIdentifier;
		String TypeName;
		A_DWORD dwObjectSize;
	};

	class AURORA_API Identifier {
		IdentityDescriptor desc;

		static constexpr void IdHelper_AddToList(_In_ const Identifier& id);
		static constexpr bool IdHelper_IsUnique(_In_ const Identifier& id);
		static constexpr void IdHelper_Rotl(_Inout_ Identifier& id);
	public:
		constexpr Identifier();

		static constexpr Identifier Create(_In_ const String& TypeName, _In_ A_DWORD dwObjectSize);
		static constexpr Identifier CreateUnique(_In_ const String& TypeName, _In_ A_DWORD dwObjectSize);

		constexpr const IdentityDescriptor* GetDesc() const;

		constexpr A_BOOL operator==(const Identifier&);
		constexpr A_BOOL operator!=(const Identifier&);
	};
}

#endif // !__AURORA_IDENTIFICATION_H__