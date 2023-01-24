#include "Identification.h"

#include <stdlib.h>
#include <time.h>

namespace Aurora {
	constexpr Identifier::Identifier(_In_z_ LPCSTR lpTypeName, _In_ DWORD dwObjectSize) : desc() {
		time_t t = time(nullptr);
		desc.dwIdentifier = *(DWORD*)&t;
		desc.dwObjectSize = dwObjectSize;
	}

	constexpr const IdentityDescriptor* Identifier::GetDesc() const { return &desc; }
}