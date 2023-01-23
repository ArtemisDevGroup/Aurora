#ifndef __AURORA_THREAD_H__
#define __AURORA_THREAD_H__

#include "Definitions.h"
#include "Interfaces.h"

#include <Windows.h>

namespace Aurora {
	class ExitCode {
		DWORD dwCode;
	public:
		constexpr ExitCode(_In_ DWORD dwExitCode) : dwCode(dwExitCode) {}

		static constexpr DWORD Success = 0;
		static constexpr DWORD UnknownError = -1;
		static constexpr DWORD Terminated = -2;

		constexpr operator DWORD() const { return dwCode; }
	};

	enum class WaitResult { Succeeded = WAIT_OBJECT_0, Abandoned = WAIT_ABANDONED, TimedOut = WAIT_TIMEOUT };

	template<typename ArgumentType = void>
	class Thread : public IDisposable {
	public:
		typedef ExitCode(__cdecl* ThreadFunction)(ArgumentType Args);

	private:
		HANDLE hThread;

		struct StaticThreadArgs {
			ThreadFunction lpfnThread;
			ArgumentType Args;
		} ArgStruct;

		static DWORD __stdcall StaticThread(_In_ StaticThreadArgs* pArgs) { return pArgs->lpfnThread(pArgs->Args); }

	public:
		Thread(_In_ ThreadFunction lpfnThread, _In_ ArgumentType Args) : hThread(nullptr) {
			ArgStruct.lpfnThread = lpfnThread;
			ArgStruct.Args = Args;
		}

		void Start() {
			hThread = CreateThread(
				nullptr,
				0,
				(LPTHREAD_START_ROUTINE)StaticThread,
				&ArgStruct,
				0,
				nullptr
			);

			if (!hThread) /* throw */;
		}

		WaitResult Wait(_In_ DWORD dwMilliseconds = INFINITE) const {
			DWORD dwResult = WaitForSingleObject(hThread, dwMilliseconds);
			if (dwResult == WAIT_FAILED) /* throw */;

			return (WaitResult)dwResult;
		}

		ExitCode GetExitCode() const {
			DWORD dwResult;
			if (!GetExitCodeThread(hThread, &dwResult)) /* throw */;

			return ExitCode(dwResult);
		}

		void Terminate() const {
			if (!TerminateThread(hThread, ExitCode::Terminated)) /* throw */;
		}

		void IDisposable::Clone(_Out_ void* pDestination) const {
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
			)) /* throw */;
		}

		Thread(const Thread<ArgumentType>& cpy) { cpy.Clone(this); }

		void IDisposable::Release() {
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

		static DWORD __stdcall StaticThread(_In_ ThreadFunction lpfnThread) { return lpfnThread(); }

	public:
		Thread(_In_ ThreadFunction lpfnThread) : lpfnThread(lpfnThread), hThread(nullptr) {}

		void Start() {
			hThread = CreateThread(
				nullptr,
				0,
				(LPTHREAD_START_ROUTINE)StaticThread,
				lpfnThread,
				0,
				nullptr
			);

			if (!hThread) /* throw */;
		}

		WaitResult Wait(_In_ DWORD dwMilliseconds = INFINITE) const {
			DWORD dwResult = WaitForSingleObject(hThread, dwMilliseconds);
			if (dwResult == WAIT_FAILED) /* throw */;

			return (WaitResult)dwResult;
		}

		ExitCode GetExitCode() const {
			DWORD dwResult;
			if (!GetExitCodeThread(hThread, &dwResult)) /* throw */;

			return ExitCode(dwResult);
		}

		void Terminate() const {
			if (!TerminateThread(hThread, ExitCode::Terminated)) /* throw */;
		}

		void IDisposable::Clone(_Out_ void* pDestination) const {
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
			)) /* throw */;
		}

		Thread(const Thread<>& cpy) { cpy.Clone(this); }

		void IDisposable::Release() {
			if (hThread) {
				CloseHandle(hThread);
				hThread = nullptr;
			}
		}

		~Thread() { Release(); }
	};
}

#endif // !__AURORA_THREAD_H__