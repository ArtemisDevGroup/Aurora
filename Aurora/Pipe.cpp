#include "Pipe.h"

namespace Aurora {
	NamedPipeServer::NamedPipeServer(
		_In_z_ A_LPCSTR lpName,
		_In_ PipeOpenMode dwOpenMode,
		_In_ PipeModeFlags dwPipeMode,
		_In_range_(1, PIPE_UNLIMITED_INSTANCES) A_DWORD dwMaxInstances = PIPE_UNLIMITED_INSTANCES,
		_In_ LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr
	) : dwOpenMode(dwOpenMode), dwPipeMode(dwPipeMode), dwMaxInstances(dwMaxInstances), hPipe(nullptr) {
		strcpy_s(szName, lpName);
		if (lpSecurityAttributes) {
			memcpy(&SecurityAttributes, lpSecurityAttributes, sizeof(SECURITY_ATTRIBUTES));
			bSecurityAttributesActive = true;
		}
		else bSecurityAttributesActive = false;
	}

	A_VOID NamedPipeServer::Create() {
		AuroraContextStart();

		hPipe = CreateNamedPipeA(
			szName,
			(A_DWORD)dwOpenMode,
			dwPipeMode.nValue,
			dwMaxInstances,
			1024,
			1024,
			0,
			bSecurityAttributesActive ? &SecurityAttributes : nullptr
		);

		if (hPipe == INVALID_HANDLE_VALUE) AuroraThrow(WindowsApiException, "CreateNamedPipeA");

		AuroraContextEnd();
	}

	A_VOID NamedPipeServer::Connect() {

	}

	A_VOID NamedPipeServer::Release() {
		if (hPipe) {
			CloseHandle(hPipe);
			hPipe = nullptr;
		}
	}
}