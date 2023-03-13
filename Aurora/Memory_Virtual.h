#ifdef __AURORA_MEMORY_H__
#ifndef __AURORA_MEMORY_VIRTUAL_H__
#define __AURORA_MEMORY_VIRTUAL_H__

#include "Definitions.h"
#include "Interfaces.h"

#include <Windows.h>

namespace Aurora {
	enum class AllocationType : A_DWORD {
		Commit = MEM_COMMIT,
		Reserve = MEM_RESERVE,
		TopDown = MEM_TOP_DOWN,
		Reset = MEM_RESET,
		ResetUndo = MEM_RESET_UNDO,
		LargePages = MEM_LARGE_PAGES,
		Physical = MEM_PHYSICAL,
		WriteWatch = MEM_WRITE_WATCH
	};

	struct AllocationTypeFlags : EnumFlags<AllocationType, A_DWORD> {
		using EnumFlags<AllocationType, A_DWORD>::EnumFlags;
		using enum AllocationType;
	};

	AllocationTypeFlags AURORA_API operator|(_In_ AllocationType dwLeft, _In_ AllocationType dwRight);

	enum class MemoryProtection : A_DWORD {
		Execute = PAGE_EXECUTE,
		Execute_Readonly = PAGE_EXECUTE_READ,
		Execute_ReadWrite = PAGE_EXECUTE_READWRITE,
		Execute_WriteCopy = PAGE_EXECUTE_WRITECOPY,
		NoAccess = PAGE_NOACCESS,
		Readonly = PAGE_READONLY,
		ReadWrite = PAGE_READWRITE,
		WriteCopy = PAGE_WRITECOPY
	};

	enum class FreeType : A_DWORD {
		Release = MEM_RELEASE,
		Decommit = MEM_DECOMMIT
	};

	class AURORA_API VirtualAllocation32 : public IDisposable {
		A_ADDR32 uRequestedAddress;
		A_ADDR32 uRealAddress;
		A_U64 uSize;
		AllocationTypeFlags dwAllocationType;
		MemoryProtection dwProtect;

		HANDLE hProcess;

	public:
		constexpr VirtualAllocation32() noexcept;

		constexpr VirtualAllocation32(
			_In_opt_ A_ADDR32 uAddress = 0,
			_In_ A_U64 uSize = 4096,
			_In_ AllocationTypeFlags dwAllocationType = AllocationTypeFlags::Reserve | AllocationTypeFlags::Commit,
			_In_ MemoryProtection dwProtect = MemoryProtection::ReadWrite
		) noexcept;

		constexpr A_ADDR32 GetAllocationAddress() const noexcept;
		constexpr A_U64 GetAllocationSize() const noexcept;
		constexpr MemoryProtection GetAllocationProtection() const noexcept;
		constexpr AllocationTypeFlags GetAllocationTypeFlags() const noexcept;
		constexpr _Ret_maybenull_ HANDLE GetExternalHandle() const noexcept;

		constexpr A_VOID SetExternalHandle(_In_ HANDLE hProcess) noexcept;

		A_VOID Allocate();
		virtual A_VOID IDisposable::Release();
		A_VOID Release(_In_ FreeType dwFreeType);

		A_VOID Read(
			_In_ A_U64 uIndex,
			_Out_writes_bytes_(uSize) A_LPVOID lpBuffer,
			_In_ A_DWORD dwSize
		) const;
	};
}

using Aurora::operator|;

#endif // !__AURORA_MEMORY_VIRTUAL_H__
#else
#error Do not directly include "Memory_Virtual.h", include "Memory.h" instead.
#endif // __AURORA_MEMORY_H__