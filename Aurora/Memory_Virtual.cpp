#include "Memory.h"

namespace Aurora {
	AllocationTypeFlags AURORA_API operator|(_In_ AllocationType dwLeft, _In_ AllocationType dwRight) { return AllocationTypeFlags((A_DWORD)dwLeft | (A_DWORD)dwRight); }

	constexpr VirtualAllocation32::VirtualAllocation32(
		_In_opt_ A_ADDR32 uAddress,
		_In_ A_U64 uSize,
		_In_ AllocationTypeFlags dwAllocationType,
		_In_ MemoryProtection dwProtect
	) noexcept : uRequestedAddress(uAddress), uRealAddress(0), uSize(uSize), dwAllocationType(dwAllocationType), dwProtect(dwProtect), hProcess(nullptr) {}

	constexpr A_VOID VirtualAllocation32::SetExternalHandle(_In_ HANDLE hProcess) noexcept { this->hProcess = hProcess; }

	constexpr A_ADDR32 VirtualAllocation32::GetAllocationAddress() const noexcept { return uRealAddress; }
	constexpr A_U64 VirtualAllocation32::GetAllocationSize() const noexcept { return uSize; }
	constexpr MemoryProtection VirtualAllocation32::GetAllocationProtection() const noexcept { return dwProtect; }
	constexpr AllocationTypeFlags VirtualAllocation32::GetAllocationTypeFlags() const noexcept { return dwAllocationType; }
	constexpr _Ret_maybenull_ HANDLE VirtualAllocation32::GetExternalHandle() const noexcept { return hProcess; }

	A_VOID VirtualAllocation32::Allocate() {
		AuroraContextStart();

		if (hProcess) {
			LPVOID lpAllocation = VirtualAllocEx(
				hProcess,
				(LPVOID)uRequestedAddress,
				uSize,
				dwAllocationType,
				(DWORD)dwProtect
			);

			if (!lpAllocation) AuroraThrow(WindowsApiException, "VirtualAllocEx");

			uRealAddress = (A_ADDR32)lpAllocation;
		}
		else {
			LPVOID lpAllocation = VirtualAlloc(
				(LPVOID)uRequestedAddress,
				uSize,
				dwAllocationType,
				(DWORD)dwProtect
			);

			if (!lpAllocation) AuroraThrow(WindowsApiException, "VirtualAlloc");

			uRealAddress = (A_ADDR32)lpAllocation;
		}

		AuroraContextEnd();
	}

	A_VOID VirtualAllocation32::Release(_In_ FreeType dwFreeType) {
		AuroraContextStart();

		if (hProcess) {
			if (!VirtualFreeEx(
				hProcess,
				(LPVOID)uRealAddress,
				dwFreeType == FreeType::Release ? 0 : uSize,
				(DWORD)dwFreeType
			)) AuroraThrow(WindowsApiException, "VirtualFreeEx");
		}
		else {
			if (!VirtualFree(
				(LPVOID)uRealAddress,
				dwFreeType == FreeType::Release ? 0 : uSize,
				(DWORD)dwFreeType
			)) AuroraThrow(WindowsApiException, "VirtualFree");
		}

		AuroraContextEnd();
	}

	A_VOID VirtualAllocation32::Release() {
		AuroraContextStart();
		Release(FreeType::Release);
		AuroraContextEnd();
	}

	A_BOOL Read32(
		_In_Address32_ A_ADDR32 uAddress,
		_Out_writes_bytes_(dwSize) A_LPVOID lpBuffer,
		_In_ A_DWORD dwSize
	) {
		__try {
			for (A_I32 i = 0; i < dwSize; i++)
				((A_LPBYTE)lpBuffer)[i] = *(A_LPBYTE)(uAddress + i);
			return true;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return false;
		}
	}

	A_VOID VirtualAllocation32::Read(
		_In_ A_U64 uIndex,
		_Out_writes_bytes_(uSize) A_LPVOID lpBuffer,
		_In_ A_DWORD dwSize
	) const {
		AuroraContextStart();
		
		if (hProcess) {
			if (!ReadProcessMemory(
				hProcess,
				(LPCVOID)(uRealAddress + uIndex),
				lpBuffer,
				uSize,
				nullptr
			)) AuroraThrow(WindowsApiException, "ReadProcessMemory");
		}
		else {
			if (!Read32(
				uRealAddress + uIndex,
				lpBuffer,
				dwSize
			)) AuroraThrow(Read32Exception, uRealAddress + uIndex, dwSize);
		}

		AuroraContextEnd();
	}
}