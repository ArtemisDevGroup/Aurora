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

	A_VOID NamedPipeServer::Connect() const {
		AuroraContextStart();
		if (!ConnectNamedPipe(hPipe, nullptr)) AuroraThrow(WindowsApiException, "ConnectNamedPipe");
		AuroraContextEnd();
	}

	A_VOID NamedPipeServer::Disconnect() const {
		AuroraContextStart();
		if (!DisconnectNamedPipe(hPipe)) AuroraThrow(WindowsApiException, "DisconnectNamedPipe");
		AuroraContextEnd();
	}

	A_VOID NamedPipeServer::Read(
		_Out_writes_bytes_(dwNumberOfBytesToRead) A_LPVOID lpBuffer,
		_In_ A_DWORD dwNumberOfBytesToRead,
		_Out_opt_ A_LPDWORD lpNumberOfBytesRead = nullptr
	) {
		AuroraContextStart();

		if (!ReadFile(
			hPipe,
			lpBuffer,
			dwNumberOfBytesToRead,
			lpNumberOfBytesRead,
			nullptr
		)) AuroraThrow(WindowsApiException, "ReadFile");

		AuroraContextEnd();
	}

	A_VOID NamedPipeServer::Read(
		_Out_writes_z_(dwSize) A_LPSTR lpString,
		_In_ A_DWORD dwSize
	) {
		AuroraContextStart();

		A_LPSTR lpBuffer = new A_CHAR[dwSize];
		A_DWORD dwNumberOfBytesRead;

		if (!ReadFile(
			hPipe,
			lpBuffer,
			dwSize,
			&dwNumberOfBytesRead,
			nullptr
		)) {
			delete[] lpBuffer;
			AuroraThrow(WindowsApiException, "ReadFile");
		}

		try { // Try-catch in order to not write null terminator twice.
			for (A_I32 i = 0; i < dwNumberOfBytesRead - 1; i++) {
				lpString[i] = lpBuffer[i];
				if (lpBuffer[i] == '\0') throw 0;
			}

			lpString[dwNumberOfBytesRead - 1] = '\0';
		}
		catch (int) {}

		AuroraContextEnd();
	}

	A_VOID NamedPipeServer::Write(
		_In_reads_bytes_(dwNumberOfBytesToWrite) A_LPCVOID lpBuffer,
		_In_ A_DWORD dwNumberOfBytesToWrite,
		_Out_opt_ A_LPDWORD lpNumberOfBytesWritten = nullptr
	) {
		AuroraContextStart();

		if (!WriteFile(
			hPipe,
			lpBuffer,
			dwNumberOfBytesToWrite,
			lpNumberOfBytesWritten,
			nullptr
		)) AuroraThrow(WindowsApiException, "WriteFile");

		AuroraContextEnd();
	}

	A_VOID NamedPipeServer::Write(_In_z_ A_LPCSTR lpString) {
		AuroraContextStart();

		if (!WriteFile(
			hPipe,
			lpString,
			strlen(lpString) + 1,
			nullptr,
			nullptr
		)) AuroraThrow(WindowsApiException, "WriteFile");

		AuroraContextEnd();
	}

	A_VOID NamedPipeServer::Clone(_Reserved_ A_LPVOID) const { /* throw NotImplementedException */ }

	A_VOID NamedPipeServer::Release() {
		if (hPipe) {
			CloseHandle(hPipe);
			hPipe = nullptr;
		}
	}
}