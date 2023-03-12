#ifndef __AURORA_PROCESS_INFO_H__
#define __AURORA_PROCESS_INFO_H__

#include "Definitions.h"
#include "Interfaces.h"
#include "Exceptions.h"
#include "Array.h"

#include <Windows.h>
#undef GetModuleHandle

namespace Aurora {
	class ProcessInfo32;
	class ProcessInfo64;

	/// <summary>
	/// Contains information about a module in a 32-bit process.
	/// </summary>
	class AURORA_API ModuleInfo32 {
		A_CHAR szModuleName[MAX_NAME];
		A_CHAR szModulePath[MAX_PATH];
		HMODULE hModule;
		A_ADDR32 uModuleBaseAddress;
		A_DWORD dwModuleSize;

		ProcessInfo32* lpOwningProcess;

	public:
		ModuleInfo32() = delete;
		ModuleInfo32(const ModuleInfo32&) = delete;

		/// <summary>
		/// Gathers information about a module.
		/// </summary>
		/// <param name="lpOwningProcess">- A pointer to a process info instance belonging to the owning process.</param>
		/// <param name="hModule">- A handle to the module to gather information about</param>
		/// <exception cref="WindowsApiException"/>
		ModuleInfo32(_In_ ProcessInfo32* lpOwningProcess, _In_ HMODULE hModule);

		/// <summary>
		/// Gets the name of the module represented by the current instance.
		/// </summary>
		/// <returns>The name of the module.</returns>
		constexpr A_LPCSTR GetModuleName() const noexcept;

		/// <summary>
		/// Gets the absolute path of the module represented by the current instance.
		/// </summary>
		/// <returns>The path of the module.</returns>
		constexpr A_LPCSTR GetModulePath() const noexcept;

		/// <summary>
		/// Gets the handle of the module represented by the current instance.
		/// </summary>
		/// <returns>The handle of the module.</returns>
		constexpr HMODULE GetModuleHandle() const noexcept;

		/// <summary>
		/// Gets the base address of the allocation belonging to the module represented by the current instance.
		/// </summary>
		/// <returns>The base address of the module allocation.</returns>
		constexpr A_ADDR32 GetModuleBaseAddress() const noexcept;

		/// <summary>
		/// Gets the size of the allocation belonging to the module represented by the current instance.
		/// </summary>
		/// <returns>The size of the module allocation.</returns>
		constexpr A_DWORD GetModuleSize() const noexcept;

		/// <summary>
		/// Gets a pointer to a process info object representing the process where the current instance of the module is loaded.
		/// </summary>
		/// <returns>A pointer to the owning process.</returns>
		constexpr ProcessInfo32* GetOwningProcess() const noexcept;
	};

	/// <summary>
	/// Contains information about a module in a 64-bit process.
	/// </summary>
	class AURORA_API ModuleInfo64 {
		A_CHAR szModuleName[MAX_NAME];
		A_CHAR szModulePath[MAX_PATH];
		HMODULE hModule;
		A_ADDR64 uModuleBaseAddress;
		A_DWORD dwModuleSize;

		ProcessInfo64* lpOwningProcess;

	public:
		ModuleInfo64() = delete;
		ModuleInfo64(const ModuleInfo64&) = delete;

		/// <summary>
		/// Gathers information about a module.
		/// </summary>
		/// <param name="lpOwningProcess">- A pointer to a process info instance belonging to the owning process.</param>
		/// <param name="hModule">- A handle to the module to gather information about</param>
		/// <exception cref="WindowsApiException"/>
		ModuleInfo64(_In_ ProcessInfo64* lpOwningProcess, _In_ HMODULE hModule);

		/// <summary>
		/// Gets the name of the module represented by the current instance.
		/// </summary>
		/// <returns>The name of the module.</returns>
		constexpr A_LPCSTR GetModuleName() const noexcept;

		/// <summary>
		/// Gets the absolute path of the module represented by the current instance.
		/// </summary>
		/// <returns>The path of the module.</returns>
		constexpr A_LPCSTR GetModulePath() const noexcept;

		/// <summary>
		/// Gets the handle of the module represented by the current instance.
		/// </summary>
		/// <returns>The handle of the module.</returns>
		constexpr HMODULE GetModuleHandle() const noexcept;

		/// <summary>
		/// Gets the base address of the allocation belonging to the module represented by the current instance.
		/// </summary>
		/// <returns>The base address of the module allocation.</returns>
		constexpr A_ADDR64 GetModuleBaseAddress() const noexcept;

		/// <summary>
		/// Gets the size of the allocation belonging to the module represented by the current instance.
		/// </summary>
		/// <returns>The size of the module allocation.</returns>
		constexpr A_DWORD GetModuleSize() const noexcept;

		/// <summary>
		/// Gets a pointer to a process info object representing the process where the current instance of the module is loaded.
		/// </summary>
		/// <returns>A pointer to the owning process.</returns>
		constexpr ProcessInfo64* GetOwningProcess() const noexcept;
	};

	/// <summary>
	/// Contains information about a 32-bit process.
	/// </summary>
	class AURORA_API ProcessInfo32 : public IDisposable {
		A_CHAR szProcessName[MAX_NAME];
		A_CHAR szProcessPath[MAX_PATH];
		HANDLE hProcess;
		A_DWORD dwProcessId;
		List<ModuleInfo32*> ModuleList;

		ProcessInfo32(_In_opt_z_ A_LPCSTR lpProcessName);

	public:
		ProcessInfo32() = delete;
		ProcessInfo32(const ProcessInfo32&) = delete;
		~ProcessInfo32();

		/// <summary>
		/// Fetches information about a 32-bit process and returns a heap allocated object containing the information.
		/// </summary>
		/// <param name="lpProcessName">
		/// <para>- The name of the process to fetch information from.</para>
		/// <para>'nullptr' (default) will fetch information about the current process instead.</para>
		/// </param>
		/// <returns>A pointer to the allocated object.</returns>
		/// <exception cref="WindowsApiException"/>
		static _Check_return_ _Ret_valid_ ProcessInfo32* Create(_In_opt_z_ A_LPCSTR lpProcessName = nullptr);

		/// <summary>
		/// This function is disabled for this class. Always throws NotImplementedException.
		/// </summary>
		/// <param name="">This functions parameters are reserved.</param>
		/// <exception cref="NotImplementedException"/>
		A_VOID IDisposable::Clone(_Reserved_ A_LPVOID) const;

		/// <summary>
		/// Destructs the instance and deletes it from the heap.
		/// </summary>
		A_VOID IDisposable::Release();

		/// <summary>
		/// Gets the name of the process associated with the instance.
		/// </summary>
		/// <returns>The process name.</returns>
		constexpr A_LPCSTR GetProcessName() const noexcept;

		/// <summary>
		/// Gets a path to the process executable associated with the instance.
		/// </summary>
		/// <returns>A process executable path.</returns>
		constexpr A_LPCSTR GetProcessPath() const noexcept;

		/// <summary>
		/// <para>Gets a handle to the process associated with the instance.</para>
		/// <para>The handle has the following access rights:</para>
		/// <para> - PROCESS_VM_READ</para>
		/// <para> - PROCESS_VM_WRITE</para>
		/// <para> - PROCESS_VM_OPERATION</para>
		/// <para> - PROCESS_CREATE_PROCESS</para>
		/// <para> - PROCESS_CREATE_THREAD</para>
		/// <para> - PROCESS_QUERY_INFORMATION</para>
		/// <para> - SYNCHRONIZE</para>
		/// </summary>
		/// <returns>A handle to the process.</returns>
		constexpr HANDLE GetProcessHandle() const noexcept;

		/// <summary>
		/// Gets the id of the process associated with the instance.
		/// </summary>
		/// <returns>The process id.</returns>
		constexpr A_DWORD GetProcessId() const noexcept;

		/// <summary>
		/// Gets a reference to the list of modules loaded in the process associated with the instance.
		/// </summary>
		/// <returns>The loaded module list.</returns>
		constexpr const List<ModuleInfo32*>& GetModuleList() const noexcept;

		/// <summary>
		/// Gets a pointer to the module with the provided name.
		/// </summary>
		/// <param name="lpModuleName">- The name of the module to find.</param>
		/// <returns>A pointer to a ModuleInfo32 instance containing information about the module.</returns>
		/// <exception cref="ObjectNotFoundException"/>
		ModuleInfo32* GetModule(_In_opt_z_ A_LPCSTR lpModuleName = nullptr) const;
	}; 

	/// <summary>
	/// Contains information about a 64-bit process.
	/// </summary>
	class AURORA_API ProcessInfo64 : public IDisposable {
		A_CHAR szProcessName[MAX_NAME];
		A_CHAR szProcessPath[MAX_PATH];
		HANDLE hProcess;
		A_DWORD dwProcessId;
		List<ModuleInfo64*> ModuleList;

		ProcessInfo64(_In_opt_z_ A_LPCSTR lpProcessName);

	public:
		ProcessInfo64() = delete;
		ProcessInfo64(const ProcessInfo64&) = delete;
		~ProcessInfo64();

		/// <summary>
		/// Fetches information about a 64-bit process and returns a heap allocated object containing the information.
		/// </summary>
		/// <param name="lpProcessName">
		/// <para>- The name of the process to fetch information from.</para>
		/// <para>'nullptr' (default) will fetch information about the current process instead.</para>
		/// </param>
		/// <returns>A pointer to the allocated object.</returns>
		/// <exception cref="WindowsApiException"/>
		static _Check_return_ _Ret_valid_ ProcessInfo64* Create(_In_opt_z_ A_LPCSTR lpProcessName = nullptr);

		/// <summary>
		/// This function is disabled for this class. Always throws NotImplementedException.
		/// </summary>
		/// <param name="">This functions parameters are reserved.</param>
		/// <exception cref="NotImplementedException"/>
		A_VOID IDisposable::Clone(_Reserved_ A_LPVOID) const;

		/// <summary>
		/// Destructs the instance and deletes it from the heap.
		/// </summary>
		A_VOID IDisposable::Release();

		/// <summary>
		/// Gets the name of the process associated with the instance.
		/// </summary>
		/// <returns>The process name.</returns>
		constexpr A_LPCSTR GetProcessName() const noexcept;

		/// <summary>
		/// Gets a path to the process executable associated with the instance.
		/// </summary>
		/// <returns>A process executable path.</returns>
		constexpr A_LPCSTR GetProcessPath() const noexcept;

		/// <summary>
		/// <para>Gets a handle to the process associated with the instance.</para>
		/// <para>The handle has the following access rights:</para>
		/// <para> - PROCESS_VM_READ</para>
		/// <para> - PROCESS_VM_WRITE</para>
		/// <para> - PROCESS_VM_OPERATION</para>
		/// <para> - PROCESS_CREATE_PROCESS</para>
		/// <para> - PROCESS_CREATE_THREAD</para>
		/// <para> - PROCESS_QUERY_INFORMATION</para>
		/// <para> - SYNCHRONIZE</para>
		/// </summary>
		/// <returns>A handle to the process.</returns>
		constexpr HANDLE GetProcessHandle() const noexcept;

		/// <summary>
		/// Gets the id of the process associated with the instance.
		/// </summary>
		/// <returns>The process id.</returns>
		constexpr A_DWORD GetProcessId() const noexcept;

		/// <summary>
		/// Gets a reference to the list of modules loaded in the process associated with the instance.
		/// </summary>
		/// <returns>The loaded module list.</returns>
		constexpr const List<ModuleInfo64*>& GetModuleList() const noexcept;

		/// <summary>
		/// Gets a pointer to the module with the provided name.
		/// </summary>
		/// <param name="lpModuleName">- The name of the module to find.</param>
		/// <returns>A pointer to a ModuleInfo64 instance containing information about the module.</returns>
		/// <exception cref="ObjectNotFoundException"/>
		ModuleInfo64* GetModule(_In_opt_z_ A_LPCSTR lpModuleName = nullptr) const;
	};

#ifdef _WIN64
	/// <summary>
	/// Contains information about a module in a 64-bit process.
	/// </summary>
	using ModuleInfo = ModuleInfo64;

	/// <summary>
	/// Contains information about a 64-bit process.
	/// </summary>
	using ProcessInfo = ProcessInfo64;
#else
	/// <summary>
	/// Contains information about a module in a 32-bit process.
	/// </summary>
	using ModuleInfo = ModuleInfo32;

	/// <summary>
	/// Contains information about a 32-bit process.
	/// </summary>
	using ProcessInfo = ProcessInfo32;
#endif // _WIN64

	/// <summary>
	/// A static class for managing a global instance of a ProcessInfo object regarding the current process.
	/// </summary>
	class AURORA_API GlobalProcessInfo {
	public:
		GlobalProcessInfo() = delete;
		GlobalProcessInfo(const GlobalProcessInfo&) = delete;

		/// <summary>
		/// Initializes the global ProcessInfo instance.
		/// </summary>
		static A_VOID InitializeGlobalInstance();

		/// <summary>
		/// Releases the global ProcessInfo instance.
		/// </summary>
		static A_VOID ReleaseGlobalInstance();

		/// <summary>
		/// Gets the global ProcessInfo instance and returns a pointer to it.
		/// </summary>
		/// <returns>A pointer to the ProcessInfo instance.</returns>
		static constexpr _Check_return_ _Ret_valid_ ProcessInfo* GetGlobalInstance() noexcept;
	};
}

#endif // !__AURORA_PROCESS_INFO_H__