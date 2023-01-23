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

	public:
		constexpr Identifier(_In_z_ LPCSTR lpTypeName, _In_ DWORD dwObjectSize);

		constexpr const IdentityDescriptor* GetDesc() const;
	};
}

#endif // !__AURORA_IDENTIFICATION_H__