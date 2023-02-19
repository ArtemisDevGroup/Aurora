#ifndef __AURORA_THREAD_H__
#define __AURORA_THREAD_H__

#include "Definitions.h"
#include "Interfaces.h"
#include "Exceptions.h"
#include "Enumerations.h"

#include <Windows.h>

namespace Aurora {
	template<typename ArgumentType = void>
	class Thread : public IDisposable {
	public:
		typedef ExitCode(__cdecl* ThreadFunction)(ArgumentType Args);

	private:
		HANDLE hThread;
		A_DWORD dwThreadId;

		struct StaticThreadArgs {
			ThreadFunction lpfnThread;
			ArgumentType Args;
		} ArgStruct;

		static A_DWORD __stdcall StaticThread(_In_ StaticThreadArgs* pArgs) { return (A_DWORD)pArgs->lpfnThread(pArgs->Args); }

	public:
		Thread(_In_ ThreadFunction lpfnThread) noexcept : hThread(nullptr), dwThreadId(0) {
			ArgStruct.lpfnThread = lpfnThread;
		}

		A_VOID Start(_In_ ArgumentType Args) {
			AuroraContextStart();

			ArgStruct.Args = Args;

			hThread = CreateThread(
				nullptr,
				0,
				(LPTHREAD_START_ROUTINE)StaticThread,
				&ArgStruct,
				0,
				&dwThreadId
			);

			if (!hThread) AuroraThrow(WindowsApiException, "CreateThread");

			AuroraContextEnd();
		}

		WaitResult Wait(_In_ A_DWORD dwMilliseconds = INFINITE) const {
			AuroraContextStart();

			A_DWORD dwResult = WaitForSingleObject(hThread, dwMilliseconds);
			if (dwResult == WAIT_FAILED) AuroraThrow(WindowsApiException, "WaitForSingleObject");

			AuroraContextEnd();
			return (WaitResult)dwResult;
		}

		ExitCode GetExitCode() const {
			AuroraContextStart();

			A_DWORD dwResult;
			if (!GetExitCodeThread(hThread, &dwResult)) AuroraThrow(WindowsApiException, "GetExitCodeThread");

			AuroraContextEnd();
			return (ExitCode)dwResult;
		}

		constexpr A_DWORD GetThreadId() const noexcept { return dwThreadId; }

		A_VOID Terminate() const {
			AuroraContextStart();

			if (!TerminateThread(hThread, (A_DWORD)ExitCode::Terminated)) AuroraThrow(WindowsApiException, "TerminateThread");

			AuroraContextEnd();
		}

		A_VOID IDisposable::Clone(_Out_ void* pDestination) const {
			AuroraContextStart();

			Thread<ArgumentType>* pDst = (Thread<ArgumentType>*)pDestination;
			pDst->ArgStruct = ArgStruct;

			if (!DuplicateHandle(
				GetCurrentProcess(),
				hThread,
				GetCurrentProcess(),
				&pDst->hThread,
				0,
				FALSE,
				DUPLICATE_SAME_ACCESS
			)) AuroraThrow(WindowsApiException, "DuplicateHandle");

			AuroraContextEnd();
		}

		Thread(const Thread<ArgumentType>& cpy) { cpy.Clone(this); }

		A_VOID IDisposable::Release() {
			if (hThread) {
				CloseHandle(hThread);
				hThread = nullptr;
			}
		}

		~Thread() { Release(); }
	};

	template<>
	class Thread<void> : public IDisposable {
	public:
		typedef ExitCode(__cdecl* ThreadFunction)();

	private:
		ThreadFunction lpfnThread;
		HANDLE hThread;
		A_DWORD dwThreadId;

		static A_DWORD __stdcall StaticThread(_In_ ThreadFunction lpfnThread) { return (A_DWORD)lpfnThread(); }

	public:
		Thread(_In_ ThreadFunction lpfnThread) noexcept : lpfnThread(lpfnThread), hThread(nullptr), dwThreadId(0) {}

		A_VOID Start() {
			AuroraContextStart();

			hThread = CreateThread(
				nullptr,
				0,
				(LPTHREAD_START_ROUTINE)StaticThread,
				lpfnThread,
				0,
				&dwThreadId
			);

			if (!hThread) AuroraThrow(WindowsApiException, "CreateThread");

			AuroraContextEnd();
		}

		WaitResult Wait(_In_ A_DWORD dwMilliseconds = INFINITE) const {
			AuroraContextStart();

			A_DWORD dwResult = WaitForSingleObject(hThread, dwMilliseconds);
			if (dwResult == WAIT_FAILED) AuroraThrow(WindowsApiException, "WaitForSingleObject");

			AuroraContextEnd();
			return (WaitResult)dwResult;
		}

		ExitCode GetExitCode() const {
			AuroraContextStart();

			A_DWORD dwResult;
			if (!GetExitCodeThread(hThread, &dwResult)) AuroraThrow(WindowsApiException, "GetExitCodeThread");

			AuroraContextEnd();
			return (ExitCode)dwResult;
		}

		constexpr A_DWORD GetThreadId() const noexcept { return dwThreadId; }

		A_VOID Terminate() const {
			AuroraContextStart();

			if (!TerminateThread(hThread, (A_DWORD)ExitCode::Terminated)) AuroraThrow(WindowsApiException, "TerminateThread");

			AuroraContextEnd();
		}

		A_VOID IDisposable::Clone(_Out_ void* pDestination) const {
			AuroraContextStart();

			Thread<>* pDst = (Thread<>*)pDestination;
			pDst->lpfnThread = lpfnThread;

			if (!DuplicateHandle(
				GetCurrentProcess(),
				hThread,
				GetCurrentProcess(),
				&pDst->hThread,
				0,
				FALSE,
				DUPLICATE_SAME_ACCESS
			)) AuroraThrow(WindowsApiException, "DuplicateHandle");

			AuroraContextEnd();
		}

		Thread(const Thread<>& cpy) { cpy.Clone(this); }

		A_VOID IDisposable::Release() {
			if (hThread) {
				CloseHandle(hThread);
				hThread = nullptr;
			}
		}

		~Thread() { Release(); }
	};
}

#endif // !__AURORA_THREAD_H__