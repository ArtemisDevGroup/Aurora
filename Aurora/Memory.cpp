#include "Memory.h"

#include <Windows.h>

namespace Aurora {
	A_VOID AURORA_API UnsafeRead(
		_In_range_(1,MAXLONGLONG) A_ADDR uAddress,
		_Out_writes_bytes_(dwSize) A_LPVOID lpBuffer,
		_In_ A_DWORD dwSize
	) {
		AuroraContextStart();

		if (!uAddress) AuroraThrow(ParameterInvalidException, "uAddress");
		if (!lpBuffer) AuroraThrow(ParameterInvalidException, "lpBuffer");

		for (A_DWORD i = 0; i < dwSize; i++)
			((A_LPBYTE)lpBuffer)[i] = *(A_LPBYTE)(uAddress + i);

		AuroraContextEnd();
	}

	A_BOOL ReadSEHFramed(
		_In_range_(1, MAXLONGLONG) A_ADDR uAddress,
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

	A_VOID AURORA_API Read(
		_In_range_(1, MAXLONGLONG) A_ADDR uAddress,
		_Out_writes_bytes_(dwSize) A_LPVOID lpBuffer,
		_In_ A_DWORD dwSize
	) {
		AuroraContextStart();
		if (!ReadSEHFramed(uAddress, lpBuffer, dwSize)) AuroraThrow(ReadException, uAddress, dwSize);
		AuroraContextEnd();
	}

	A_VOID AURORA_API ReadStringA(
		_In_ A_ADDR uAddress,
		_Out_writes_z_(dwCount) A_LPSTR lpBuffer,
		_In_ A_DWORD dwCount,
		_Out_opt_ A_LPDWORD lpNumberOfCharactersRead
	) {
		AuroraContextStart();

		try {
			for (A_I32 i = 0; i < dwCount - 1; i++) {
				lpBuffer[i] = Read<A_CHAR>(uAddress + i);
				if (lpBuffer[i] == '\0') {
					if (lpNumberOfCharactersRead)
						*lpNumberOfCharactersRead = i;
					throw 0;
				}
			}
		}
		catch (A_I32) {
			AuroraContextEnd();
			return;
		}

		lpBuffer[dwCount - 1] = '\0';
		if (lpNumberOfCharactersRead) *lpNumberOfCharactersRead = dwCount - 1;
		AuroraContextEnd();
	}

	A_VOID AURORA_API ReadStringW(
		_In_ A_ADDR uAddress,
		_Out_writes_z_(dwCount) A_LPWSTR lpBuffer,
		_In_ A_DWORD dwCount,
		_Out_opt_ A_LPDWORD lpNumberOfCharactersRead
	) {
		AuroraContextStart();

		try {
			for (A_I32 i = 0; i < dwCount - 1; i++) {
				lpBuffer[i] = Read<A_WCHAR>(uAddress + (i * 2));
				if (lpBuffer[i] == L'\000') {
					if (lpNumberOfCharactersRead)
						*lpNumberOfCharactersRead = i;
					throw 0;
				}
			}
		}
		catch (A_I32) {
			AuroraContextEnd();
			return;
		}

		lpBuffer[dwCount - 1] = L'\000';
		if (lpNumberOfCharactersRead) *lpNumberOfCharactersRead = dwCount - 1;
		AuroraContextEnd();
	}

	A_VOID AURORA_API UnsafeWrite(
		_In_range_(1, MAXLONGLONG) A_ADDR uAddress,
		_In_reads_bytes_(dwSize) A_LPCVOID lpBuffer,
		_In_ A_DWORD dwSize
	) {
		AuroraContextStart();

		if (!uAddress) AuroraThrow(ParameterInvalidException, "uAddress");
		if (!lpBuffer) AuroraThrow(ParameterInvalidException, "lpBuffer");

		for (A_I32 i = 0; i < dwSize; i++)
			*(A_LPBYTE)(uAddress + i) = ((A_LPCBYTE)lpBuffer)[i];

		AuroraContextEnd();
	}

	A_BOOL WriteSEHFramed(
		_In_range_(1, MAXLONGLONG) A_ADDR uAddress,
		_In_reads_bytes_(dwSize) A_LPCVOID lpBuffer,
		_In_ A_DWORD dwSize
	) {
		__try {
			Write(uAddress, lpBuffer, dwSize); // This could potentially throw a C++ exception if uAddress or lpBuffer is nullptr.
			return true;
		}
		// Here we check if the exception thrown is a memory access violation, the exception we are looking for. If it is not, we pass it on and continue searching for an exception handler.
		__except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
			return false;
		}
	}

	A_VOID AURORA_API Write(
		_In_range_(1, MAXLONGLONG) A_ADDR uAddress,
		_In_reads_bytes_(dwSize) A_LPCVOID lpBuffer,
		_In_ A_DWORD dwSize
	) {
		AuroraContextStart();
		if (!WriteSEHFramed(uAddress, lpBuffer, dwSize)) AuroraThrow(WriteException, uAddress, dwSize);
		AuroraContextEnd();
	}
}