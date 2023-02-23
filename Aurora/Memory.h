#ifndef __AURORA_MEMORY_H__
#define __AURORA_MEMORY_H__

#include "Definitions.h"
#include "Array.h"

typedef unsigned __int32 A_ADDR32; // Represents an address pointing to a virtual memory location in a 32-bit process.
typedef unsigned __int64 A_ADDR64; // Represents an address pointing to a virtual memory location in a 64-bit process.

#ifdef _WIN64
typedef A_ADDR64 A_ADDR; // Represents an address pointing to a virtual memory location in a 64-bit process.
#else
typedef A_ADDR32 A_ADDR; // Represents an address pointing to a virtual memory location in a 32-bit process.
#endif // _WIN64

namespace Aurora {
	class Pointer32 : public ArgumentList<A_ADDR32> { public: using ArgumentList<A_ADDR32>::ArgumentList; };
	class Pointer64 : public ArgumentList<A_ADDR64> { public: using ArgumentList<A_ADDR64>::ArgumentList; };

#ifdef _WIN64
	using Pointer = Pointer64;
#else
	using Pointer = Pointer32;
#endif // _WIN64

	A_VOID AURORA_API Read();
	A_VOID AURORA_API Read_s();
}

#endif // !__AURORA_MEMORY_H__