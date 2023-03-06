#include "ProcessInfo.h"

#undef UNICODE
#include <TlHelp32.h>
#include <Psapi.h>

namespace Aurora {
	//------------------------------------------------------------------------>
	// ModuleInfo32
	ModuleInfo32::ModuleInfo32(_In_ ProcessInfo32* lpOwningProcess, _In_ HMODULE hModule) : lpOwningProcess(lpOwningProcess), hModule(hModule) {
		AuroraContextStart();

		MODULEINFO modNfo = { NULL };
		if (!K32GetModuleInformation(lpOwningProcess->GetProcessHandle(), hModule, &modNfo, sizeof(modNfo))) AuroraThrow(WindowsApiException, "K32GetModuleInformation");
		uModuleBaseAddress = (A_ADDR32)modNfo.lpBaseOfDll;
		dwModuleSize = modNfo.SizeOfImage;

		if (!K32GetModuleBaseNameA(lpOwningProcess->GetProcessHandle(), hModule, szModuleName, sizeof(szModuleName))) AuroraThrow(WindowsApiException, "K32GetModuleBaseNameA");
		if (!K32GetModuleFileNameExA(lpOwningProcess->GetProcessHandle(), hModule, szModulePath, sizeof(szModulePath))) AuroraThrow(WindowsApiException, "K32GetModuleFileNameExA");

		AuroraContextEnd();
	}
	//-----------------------------------
	constexpr A_LPCSTR ModuleInfo32::GetModuleName() const noexcept { return szModuleName; }
	//-----------------------------------
	constexpr A_LPCSTR ModuleInfo32::GetModulePath() const noexcept { return szModulePath; }
	//-----------------------------------
	constexpr HMODULE ModuleInfo32::GetModuleHandle() const noexcept { return hModule; }
	//-----------------------------------
	constexpr A_ADDR32 ModuleInfo32::GetModuleBaseAddress() const noexcept { return uModuleBaseAddress; }
	//-----------------------------------
	constexpr A_DWORD ModuleInfo32::GetModuleSize() const noexcept { return dwModuleSize; }
	//-----------------------------------
	constexpr ProcessInfo32* ModuleInfo32::GetOwningProcess() const noexcept { return lpOwningProcess; }
	//------------------------------------------------------------------------>
	// ModuleInfo64
	ModuleInfo64::ModuleInfo64(_In_ ProcessInfo64* lpOwningProcess, _In_ HMODULE hModule) : lpOwningProcess(lpOwningProcess), hModule(hModule) {
		AuroraContextStart();

		MODULEINFO modNfo = { NULL };
		if (!K32GetModuleInformation(lpOwningProcess->GetProcessHandle(), hModule, &modNfo, sizeof(modNfo))) AuroraThrow(WindowsApiException, "K32GetModuleInformation");
		uModuleBaseAddress = (A_ADDR64)modNfo.lpBaseOfDll;
		dwModuleSize = modNfo.SizeOfImage;

		if (!K32GetModuleBaseNameA(lpOwningProcess->GetProcessHandle(), hModule, szModuleName, sizeof(szModuleName))) AuroraThrow(WindowsApiException, "K32GetModuleBaseNameA");
		if (!K32GetModuleFileNameExA(lpOwningProcess->GetProcessHandle(), hModule, szModulePath, sizeof(szModulePath))) AuroraThrow(WindowsApiException, "K32GetModuleFileNameExA");

		AuroraContextEnd();
	}
	//-----------------------------------
	constexpr A_LPCSTR ModuleInfo64::GetModuleName() const noexcept { return szModuleName; }
	//-----------------------------------
	constexpr A_LPCSTR ModuleInfo64::GetModulePath() const noexcept { return szModulePath; }
	//-----------------------------------
	constexpr HMODULE ModuleInfo64::GetModuleHandle() const noexcept { return hModule; }
	//-----------------------------------
	constexpr A_ADDR64 ModuleInfo64::GetModuleBaseAddress() const noexcept { return uModuleBaseAddress; }
	//-----------------------------------
	constexpr A_DWORD ModuleInfo64::GetModuleSize() const noexcept { return dwModuleSize; }
	//-----------------------------------
	constexpr ProcessInfo64* ModuleInfo64::GetOwningProcess() const noexcept { return lpOwningProcess; }
	//------------------------------------------------------------------------>
	// ProcessInfo32
	ProcessInfo32::ProcessInfo32(_In_opt_z_ A_LPCSTR lpProcessName) : dwProcessId(0) {
		AuroraContextStart();

		if (lpProcessName) {
			HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hSnapshot == INVALID_HANDLE_VALUE) AuroraThrow(WindowsApiException, "CreateToolhelp32Snapshot");
			// Making sure that if Process32First causes a throw, hSnapshot will still be closed accordingly.
			A_I32 nSnapCloseIndex = NextThrowEventManager::QueueEvent([](IException*, _In_opt_ A_LPVOID lpParameter) -> A_VOID { CloseHandle(lpParameter); }, hSnapshot);

			PROCESSENTRY32 pe32 = { NULL };
			pe32.dwSize = sizeof(pe32);
			
			if (!Process32First(hSnapshot, &pe32)) AuroraThrow(WindowsApiException, "Process32First");

			do {
				if (!strcmp(lpProcessName, pe32.szExeFile)) {
					dwProcessId = pe32.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnapshot, &pe32));

			CloseHandle(hSnapshot);
			NextThrowEventManager::ClearEventQueue(nSnapCloseIndex); // Popping that handler off of the event queue since hSnapshot is already closed.
		}
		else
			dwProcessId = GetCurrentProcessId();

		hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD | PROCESS_CREATE_PROCESS | PROCESS_QUERY_INFORMATION | SYNCHRONIZE, FALSE, dwProcessId);
		if (!hProcess) AuroraThrow(WindowsApiException, "OpenProcess"); // If valid, hProcess will be closed by the destructor in the event of a throw.

		if (!K32GetModuleBaseNameA(hProcess, nullptr, szProcessName, sizeof(szProcessName))) AuroraThrow(WindowsApiException, "K32GetModuleBaseNameA");
		if (!K32GetModuleFileNameExA(hProcess, nullptr, szProcessPath, sizeof(szProcessPath))) AuroraThrow(WindowsApiException, "K32GetModuleFileNameExA");

		HANDLE hSnapshot2 = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
		if (hSnapshot2 == INVALID_HANDLE_VALUE) AuroraThrow(WindowsApiException, "CreateToolhelp32Snapshot");
		A_I32 nSnap2CloseIndex = NextThrowEventManager::QueueEvent([](IException*, _In_opt_ A_LPVOID lpParameter) -> A_VOID { CloseHandle(lpParameter); }, hSnapshot2);

		MODULEENTRY32 me32 = { NULL };
		me32.dwSize = sizeof(me32);

		if (!Module32First(hSnapshot2, &me32)) AuroraThrow(WindowsApiException, "Module32First");

		do {
			ModuleList.Add(new ModuleInfo32(this, me32.hModule));
		} while (Module32Next(hSnapshot2, &me32));

		CloseHandle(hSnapshot2);
		NextThrowEventManager::ClearEventQueue(nSnap2CloseIndex);

		AuroraContextEnd();
	}
	//-----------------------------------
	_Check_return_ _Ret_valid_ ProcessInfo32* ProcessInfo32::Create(_In_opt_z_ A_LPCSTR lpProcessName) {
		AuroraContextStart();

		ProcessInfo32* lpProcInfo;
		NextThrowEventManager::QueueEvent([](IException*, _In_opt_ A_LPVOID lpParameter) -> A_VOID { delete *(ProcessInfo32**)lpParameter; }, &lpProcInfo); // Queuing the deletion of the object in case it's constructor throws.
		lpProcInfo = new ProcessInfo32(lpProcessName);

		AuroraContextEnd();
		return lpProcInfo;
	}
	//-----------------------------------
	A_VOID ProcessInfo32::Clone(_Reserved_ A_LPVOID) const {
		AuroraContextStart();
		AuroraThrow(NotImplementedException);
		AuroraContextEnd();
	}
	//-----------------------------------
	A_VOID ProcessInfo32::Release() { delete this; }
	//-----------------------------------
	ProcessInfo32::~ProcessInfo32() {
		if (hProcess) {
			CloseHandle(hProcess);
			hProcess = nullptr;
		}

		for (ModuleInfo32* lpModInfo : ModuleList)
			delete lpModInfo;
		ModuleList.Release();
	}
	//-----------------------------------
	constexpr A_LPCSTR ProcessInfo32::GetProcessName() const noexcept { return szProcessName; }
	//-----------------------------------
	constexpr A_LPCSTR ProcessInfo32::GetProcessPath() const noexcept { return szProcessPath; }
	//-----------------------------------
	constexpr HANDLE ProcessInfo32::GetProcessHandle() const noexcept { return hProcess; }
	//-----------------------------------
	constexpr A_DWORD ProcessInfo32::GetProcessId() const noexcept { return dwProcessId; }
	//-----------------------------------
	constexpr const List<ModuleInfo32*>& ProcessInfo32::GetModuleList() const noexcept { return ModuleList; }
	//-----------------------------------
	ModuleInfo32* ProcessInfo32::GetModule(_In_opt_z_ A_LPCSTR lpModuleName) const {
		AuroraContextStart();
		ModuleInfo32* lpReturn = nullptr;

		for (ModuleInfo32* lpModInfo : ModuleList)
			if (!strcmp(lpModInfo->GetModuleName(), lpModuleName ? lpModuleName : szProcessName)) {
				lpReturn = lpModInfo;
				break;
			}
		if (!lpReturn) AuroraThrow(ObjectNotFoundException, "ModuleInfo32", lpModuleName ? lpModuleName : szProcessName);
		AuroraContextEnd();
		return lpReturn;
	}
	//------------------------------------------------------------------------>
	// ProcessInfo64
	ProcessInfo64::ProcessInfo64(_In_opt_z_ A_LPCSTR lpProcessName) : dwProcessId(0) {
		AuroraContextStart();

		if (lpProcessName) {
			HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hSnapshot == INVALID_HANDLE_VALUE) AuroraThrow(WindowsApiException, "CreateToolhelp32Snapshot");
			// Making sure that if Process32First causes a throw, hSnapshot will still be closed accordingly.
			A_I32 nSnapCloseIndex = NextThrowEventManager::QueueEvent([](IException*, _In_opt_ A_LPVOID lpParameter) -> A_VOID { CloseHandle(lpParameter); }, hSnapshot);

			PROCESSENTRY32 pe32 = { NULL };
			pe32.dwSize = sizeof(pe32);

			if (!Process32First(hSnapshot, &pe32)) AuroraThrow(WindowsApiException, "Process32First");

			do {
				if (!strcmp(lpProcessName, pe32.szExeFile)) {
					dwProcessId = pe32.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnapshot, &pe32));

			CloseHandle(hSnapshot);
			NextThrowEventManager::ClearEventQueue(nSnapCloseIndex); // Popping that handler off of the event queue since hSnapshot is already closed.
		}
		else
			dwProcessId = GetCurrentProcessId();

		hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD | PROCESS_CREATE_PROCESS | PROCESS_QUERY_INFORMATION | SYNCHRONIZE, FALSE, dwProcessId);
		if (!hProcess) AuroraThrow(WindowsApiException, "OpenProcess"); // If valid, hProcess will be closed by the destructor in the event of a throw.

		if (!K32GetModuleBaseNameA(hProcess, nullptr, szProcessName, sizeof(szProcessName))) AuroraThrow(WindowsApiException, "K32GetModuleBaseNameA");
		if (!K32GetModuleFileNameExA(hProcess, nullptr, szProcessPath, sizeof(szProcessPath))) AuroraThrow(WindowsApiException, "K32GetModuleFileNameExA");

		HANDLE hSnapshot2 = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
		if (hSnapshot2 == INVALID_HANDLE_VALUE) AuroraThrow(WindowsApiException, "CreateToolhelp32Snapshot");
		A_I32 nSnap2CloseIndex = NextThrowEventManager::QueueEvent([](IException*, _In_opt_ A_LPVOID lpParameter) -> A_VOID { CloseHandle(lpParameter); }, hSnapshot2);

		MODULEENTRY32 me32 = { NULL };
		me32.dwSize = sizeof(me32);

		if (!Module32First(hSnapshot2, &me32)) AuroraThrow(WindowsApiException, "Module32First");

		do {
			ModuleList.Add(new ModuleInfo64(this, me32.hModule));
		} while (Module32Next(hSnapshot2, &me32));

		CloseHandle(hSnapshot2);
		NextThrowEventManager::ClearEventQueue(nSnap2CloseIndex);

		AuroraContextEnd();
	}
	//-----------------------------------
	_Check_return_ _Ret_valid_ ProcessInfo64* ProcessInfo64::Create(_In_opt_z_ A_LPCSTR lpProcessName) {
		AuroraContextStart();

		ProcessInfo64* lpProcInfo = nullptr;
		NextThrowEventManager::QueueEvent([](IException*, _In_ A_LPVOID lpParameter) -> A_VOID { delete *(ProcessInfo64**)lpParameter; }, &lpProcInfo); // Queuing the deletion of the object in case it's constructor throws.
		lpProcInfo = new ProcessInfo64(lpProcessName);

		AuroraContextEnd();
		return lpProcInfo;
	}
	//-----------------------------------
	A_VOID ProcessInfo64::Clone(_Reserved_ A_LPVOID) const {
		AuroraContextStart();
		AuroraThrow(NotImplementedException);
		AuroraContextEnd();
	}
	//-----------------------------------
	A_VOID ProcessInfo64::Release() { delete this; }
	//-----------------------------------
	ProcessInfo64::~ProcessInfo64() {
		if (hProcess) {
			CloseHandle(hProcess);
			hProcess = nullptr;
		}

		for (ModuleInfo64* lpModInfo : ModuleList)
			delete lpModInfo;
		ModuleList.Release();
	}
	//-----------------------------------
	constexpr A_LPCSTR ProcessInfo64::GetProcessName() const noexcept { return szProcessName; }
	//-----------------------------------
	constexpr A_LPCSTR ProcessInfo64::GetProcessPath() const noexcept { return szProcessPath; }
	//-----------------------------------
	constexpr HANDLE ProcessInfo64::GetProcessHandle() const noexcept { return hProcess; }
	//-----------------------------------
	constexpr A_DWORD ProcessInfo64::GetProcessId() const noexcept { return dwProcessId; }
	//-----------------------------------
	constexpr const List<ModuleInfo64*>& ProcessInfo64::GetModuleList() const noexcept { return ModuleList; }
	//-----------------------------------
	ModuleInfo64* ProcessInfo64::GetModule(_In_opt_z_ A_LPCSTR lpModuleName) const {
		AuroraContextStart();
		ModuleInfo64* lpReturn = nullptr;

		for (ModuleInfo64* lpModInfo : ModuleList)
			if (!strcmp(lpModInfo->GetModuleName(), lpModuleName ? lpModuleName : szProcessName)) {
				lpReturn = lpModInfo;
				break;
			}
		if (!lpReturn) AuroraThrow(ObjectNotFoundException, "ModuleInfo64", lpModuleName ? lpModuleName : szProcessName);
		AuroraContextEnd();
		return lpReturn;
	}
	//------------------------------------------------------------------------>
	// GlobalProcessInfo
	ProcessInfo* g_lpProcInfo = nullptr;
	//-----------------------------------
	A_VOID GlobalProcessInfo::InitializeGlobalInstance() {
		AuroraContextStart();
		g_lpProcInfo = ProcessInfo::Create();
		AuroraContextEnd();
	}
	//-----------------------------------
	A_VOID GlobalProcessInfo::ReleaseGlobalInstance() {
		if (g_lpProcInfo) {
			g_lpProcInfo->Release();
			g_lpProcInfo = nullptr;
		}
	}
	//-----------------------------------
	constexpr _Check_return_ _Ret_valid_ ProcessInfo* GlobalProcessInfo::GetGlobalInstance() noexcept { return g_lpProcInfo; }
}