#include "Memory.h"

#include <Windows.h>

namespace Aurora {
	A_VOID AURORA_API Read(
		_In_ A_ADDR uAddress,
		_Out_writes_bytes_(dwSize) A_LPVOID lpBuffer,
		_In_ A_DWORD dwSize
	) {
		AuroraContextStart();

		if (!uAddress) /* AuroraThrow() */;
		if (!lpBuffer) AuroraThrow(ParameterInvalidException, "lpBuffer");

		for (A_DWORD i = 0; i < dwSize; i++)
			*(A_LPBYTE)lpBuffer = *(A_LPBYTE)uAddress;

		AuroraContextEnd();
	}

	A_BOOL ReadSEHFramed(
		_In_ A_ADDR uAddress,
		_Out_writes_bytes_(dwSize) A_LPVOID lpBuffer,
		_In_ A_DWORD dwSize
	) {
		__try {
			Read(uAddress, lpBuffer, dwSize); // This could potentially throw a C++ exception if uAddress or lpBuffer is nullptr.
			return true;
		}
		// Here we check if the exception thrown is a memory access violation, the exception we are looking for. If it is not, we pass it on and continue searching for an exception handler.
		__except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
			return false;
		}
	}

	A_VOID AURORA_API Read_s(
		_In_ A_ADDR uAddress,
		_Out_writes_bytes_(dwSize) A_LPVOID lpBuffer,
		_In_ A_DWORD dwSize
	) {
		AuroraContextStart();

		if (!ReadSEHFramed(uAddress, lpBuffer, dwSize)) /* AuroraThrow() */;

		AuroraContextEnd();
	}
}