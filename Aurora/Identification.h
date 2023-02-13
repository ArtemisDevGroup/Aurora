#ifndef __AURORA_IDENTIFICATION_H__
#define __AURORA_IDENTIFICATION_H__

#include "Definitions.h"

namespace Aurora {
	struct AURORA_API IdentityDescriptor {
		A_DWORD dwIdentifier;
		A_CHAR szTypeName[MAX_NAME];
		A_DWORD dwObjectSize;
	};

	class AURORA_API Identifier {
		IdentityDescriptor desc;

		static constexpr A_U32 IdHelper_rotl32(_In_ A_U32 uValue, _In_ A_U32 uShift) noexcept;
		static constexpr A_VOID IdHelper_AddToList(_In_ const Identifier& id) noexcept;
		static constexpr A_BOOL IdHelper_IsUnique(_In_ const Identifier& id) noexcept;
		static constexpr A_VOID IdHelper_Rotl(_Inout_ Identifier& id) noexcept;
	public:
		Identifier();

		static Identifier Create(_In_z_ A_LPCSTR lpTypeName, _In_ A_DWORD dwObjectSize);
		static Identifier CreateUnique(_In_z_ A_LPCSTR lpTypeName, _In_ A_DWORD dwObjectSize);

		constexpr const IdentityDescriptor* GetDesc() const noexcept;

		constexpr A_BOOL operator==(const Identifier&) const noexcept;
		constexpr A_BOOL operator!=(const Identifier&) const noexcept;
	};
}

#endif // !__AURORA_IDENTIFICATION_H__