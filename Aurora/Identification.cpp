#include "Identification.h"

#include <stdlib.h>
#include <time.h>

namespace Aurora {
	constexpr Identifier::Identifier() : desc() {}

	constexpr Identifier Identifier::Create(_In_ const String& TypeName, _In_ A_DWORD dwObjectSize) {
		Identifier ret;
		
		ret.desc.TypeName = TypeName;
		ret.desc.dwObjectSize = dwObjectSize;

		for (A_I32 i = 0; i < ret.desc.TypeName.size(); i++) {
			((A_BYTE*)&ret.desc.dwIdentifier)[i % sizeof(A_DWORD)] += TypeName[i];

			if (!(i % 4)) ret.desc.dwIdentifier = _rotl(ret.desc.dwIdentifier, ret.desc.dwObjectSize % 16 + 1);
		}

		return ret;
	}

#pragma intrinsic(_rotl)

	A_DWORD g_dwGlobalRotl = 16;
	A_DWORD g_szdwRegisteredList[256];
	A_DWORD g_dwListIndex = 0;

	constexpr A_VOID Identifier::IdHelper_AddToList(_In_ const Identifier& id) {
		g_szdwRegisteredList[g_dwListIndex] = id.desc.dwIdentifier;
		if (g_dwListIndex++ == 256) g_dwListIndex = 0;
	}

	constexpr A_BOOL Identifier::IdHelper_IsUnique(_In_ const Identifier& id) {
		for (A_I32 i = 0; i < 256; i++)
			if (g_szdwRegisteredList[i] == id.desc.dwIdentifier)
				return false;
		return true;
	}

	constexpr A_VOID Identifier::IdHelper_Rotl(_Inout_ Identifier& id) {
		id.desc.dwIdentifier = _rotl(id.desc.dwIdentifier, g_dwGlobalRotl);
		g_dwGlobalRotl += id.desc.dwObjectSize;
	}

	constexpr Identifier Identifier::CreateUnique(_In_ const String& TypeName, _In_ A_DWORD dwObjectSize) {
		Identifier ret = Create(TypeName, dwObjectSize);
		do { IdHelper_Rotl(ret); } while (!IdHelper_IsUnique(ret));
		IdHelper_AddToList(ret);
		return ret;
	}

	constexpr const IdentityDescriptor* Identifier::GetDesc() const { return &desc; }

	constexpr A_BOOL Identifier::operator==(const Identifier& operand) {
		return desc.dwIdentifier == operand.desc.dwIdentifier;
	}

	constexpr A_BOOL Identifier::operator!=(const Identifier& operand) {
		return desc.dwIdentifier != operand.desc.dwIdentifier;
	}
}