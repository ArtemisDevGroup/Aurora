#include "Identification.h"

#include <stdlib.h>
#include <time.h>

namespace Aurora {
	constexpr Identifier::Identifier() : desc() {}

	constexpr Identifier Identifier::Create(_In_z_ LPCSTR lpTypeName, _In_ DWORD dwObjectSize) {
		Identifier ret;
		
		strcpy_s(ret.desc.szTypeName, lpTypeName);
		ret.desc.dwObjectSize = dwObjectSize;

		size_t uStrLen = strlen(lpTypeName);
		for (INT i = 0; i < uStrLen; i++) {
			((BYTE*)&ret.desc.dwIdentifier)[i % sizeof(DWORD)] += lpTypeName[i];

			if (!(i % 4)) ret.desc.dwIdentifier = _rotl(ret.desc.dwIdentifier, ret.desc.dwObjectSize % 16 + 1);
		}

		return ret;
	}

#pragma intrinsic(_rotl)

	DWORD g_dwGlobalRotl = 16;
	DWORD g_szdwRegisteredList[256];
	DWORD g_dwListIndex = 0;

	constexpr void Identifier::IdHelper_AddToList(_In_ const Identifier& id) {
		g_szdwRegisteredList[g_dwListIndex] = id.desc.dwIdentifier;
		if (g_dwListIndex++ == 256) g_dwListIndex = 0;
	}

	constexpr bool Identifier::IdHelper_IsUnique(_In_ const Identifier& id) {
		for (int i = 0; i < 256; i++)
			if (g_szdwRegisteredList[i] == id.desc.dwIdentifier)
				return false;
		return true;
	}

	constexpr void Identifier::IdHelper_Rotl(_Inout_ Identifier& id) {
		id.desc.dwIdentifier = _rotl(id.desc.dwIdentifier, g_dwGlobalRotl);
		g_dwGlobalRotl += id.desc.dwObjectSize;
	}

	constexpr Identifier Identifier::CreateUnique(_In_z_ LPCSTR lpTypeName, _In_ DWORD dwObjectSize) {
		Identifier ret = Create(lpTypeName, dwObjectSize);
		do { IdHelper_Rotl(ret); } while (!IdHelper_IsUnique(ret));
		IdHelper_AddToList(ret);
		return ret;
	}

	constexpr const IdentityDescriptor* Identifier::GetDesc() const { return &desc; }

	constexpr bool Identifier::operator==(const Identifier& operand) {
		return desc.dwIdentifier == operand.desc.dwIdentifier;
	}

	constexpr bool Identifier::operator!=(const Identifier& operand) {
		return desc.dwIdentifier != operand.desc.dwIdentifier;
	}
}