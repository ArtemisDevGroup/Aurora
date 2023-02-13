#include "Identification.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

namespace Aurora {
	Identifier::Identifier() : desc() {}

	Identifier Identifier::Create(_In_z_ A_LPCSTR lpTypeName, _In_ A_DWORD dwObjectSize) {
		Identifier ret;
		
		strcpy_s(ret.desc.szTypeName, lpTypeName);
		ret.desc.dwObjectSize = dwObjectSize;

		for (A_I32 i = 0; i < strlen(lpTypeName); i++) {
			((A_BYTE*)&ret.desc.dwIdentifier)[i % sizeof(A_DWORD)] += lpTypeName[i];

			if (!(i % 4)) ret.desc.dwIdentifier = IdHelper_rotl32(ret.desc.dwIdentifier, ret.desc.dwObjectSize % 16 + 1);
		}

		return ret;
	}

	A_DWORD g_dwGlobalRotl = 16;
	A_DWORD g_szdwRegisteredList[256];
	A_DWORD g_dwListIndex = 0;

	constexpr A_U32 Identifier::IdHelper_rotl32(_In_ A_U32 uValue, _In_ A_U32 uShift) noexcept {
		return uValue << uShift | uValue >> (32 - uShift);
	}

	constexpr A_VOID Identifier::IdHelper_AddToList(_In_ const Identifier& id) noexcept {
		g_szdwRegisteredList[g_dwListIndex] = id.desc.dwIdentifier;
		if (g_dwListIndex++ == 256) g_dwListIndex = 0;
	}

	constexpr A_BOOL Identifier::IdHelper_IsUnique(_In_ const Identifier& id) noexcept {
		for (A_I32 i = 0; i < 256; i++)
			if (g_szdwRegisteredList[i] == id.desc.dwIdentifier)
				return false;
		return true;
	}

	constexpr A_VOID Identifier::IdHelper_Rotl(_Inout_ Identifier& id) noexcept {
		id.desc.dwIdentifier = IdHelper_rotl32(id.desc.dwIdentifier, g_dwGlobalRotl);
		g_dwGlobalRotl += id.desc.dwObjectSize;
	}

	Identifier Identifier::CreateUnique(_In_z_ A_LPCSTR lpTypeName, _In_ A_DWORD dwObjectSize) {
		Identifier ret = Create(lpTypeName, dwObjectSize);
		do { IdHelper_Rotl(ret); } while (!IdHelper_IsUnique(ret));
		IdHelper_AddToList(ret);
		return ret;
	}

	constexpr const IdentityDescriptor* Identifier::GetDesc() const noexcept { return &desc; }

	constexpr A_BOOL Identifier::operator==(const Identifier& operand) const noexcept {
		return desc.dwIdentifier == operand.desc.dwIdentifier;
	}

	constexpr A_BOOL Identifier::operator!=(const Identifier& operand) const noexcept {
		return desc.dwIdentifier != operand.desc.dwIdentifier;
	}
}