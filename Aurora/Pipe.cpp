#include "Pipe.h"

#include <stdio.h>

namespace Aurora {
	INamedPipeBase::INamedPipeBase(_In_ LPHANDLE lpPipeHandle) : phPipe(lpPipeHandle) {}

	A_VOID INamedPipeBase::Read(
		_Out_writes_bytes_(dwNumberOfBytesToRead) A_LPVOID lpBuffer,
		_In_ A_DWORD dwNumberOfBytesToRead,
		_Out_opt_ A_LPDWORD lpNumberOfBytesRead
	) {
		AuroraContextStart();

		if (!lpBuffer) AuroraThrow(ParameterInvalidException, "lpBuffer");

		if (!ReadFile(
			*phPipe,
			lpBuffer,
			dwNumberOfBytesToRead,
			lpNumberOfBytesRead,
			nullptr
		)) AuroraThrow(WindowsApiException, "ReadFile");

		AuroraContextEnd();
	}

	A_VOID INamedPipeBase::Read(
		_Out_writes_z_(dwSize) A_LPSTR lpString,
		_In_ A_DWORD dwSize
	) {
		AuroraContextStart();

		if (!lpString) AuroraThrow(ParameterInvalidException, "lpString");

		A_LPSTR lpBuffer = new A_CHAR[dwSize];
		A_DWORD dwNumberOfBytesRead;

		if (!ReadFile(
			*phPipe,
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

	A_VOID INamedPipeBase::Write(
		_In_reads_bytes_(dwNumberOfBytesToWrite) A_LPCVOID lpBuffer,
		_In_ A_DWORD dwNumberOfBytesToWrite,
		_Out_opt_ A_LPDWORD lpNumberOfBytesWritten
	) {
		AuroraContextStart();

		if (!lpBuffer) AuroraThrow(ParameterInvalidException, "lpBuffer");

		if (!WriteFile(
			*phPipe,
			lpBuffer,
			dwNumberOfBytesToWrite,
			lpNumberOfBytesWritten,
			nullptr
		)) AuroraThrow(WindowsApiException, "WriteFile");

		AuroraContextEnd();
	}

	A_VOID INamedPipeBase::Write(_In_z_ A_LPCSTR lpString) {
		AuroraContextStart();

		if (!lpString) AuroraThrow(ParameterInvalidException, "lpString");

		if (!WriteFile(
			*phPipe,
			lpString,
			strlen(lpString) + 1,
			nullptr,
			nullptr
		)) AuroraThrow(WindowsApiException, "WriteFile");

		AuroraContextEnd();
	}

	A_VOID INamedPipeBase::Clone(_Reserved_ A_LPVOID) const {
		AuroraContextStart();
		AuroraThrow(NotImplementedException);
		AuroraContextEnd();
	}

	A_VOID INamedPipeBase::Release() {
		if (*phPipe) {
			CloseHandle(*phPipe);
			*phPipe = nullptr;
		}
	}

	INamedPipeBase::~INamedPipeBase() { Release(); }

	NamedPipeServer::NamedPipeServer(
		_In_z_ A_LPCSTR lpName,
		_In_ PipeOpenMode dwOpenMode,
		_In_ PipeModeFlags dwPipeMode,
		_In_range_(1, PIPE_UNLIMITED_INSTANCES) A_DWORD dwMaxInstances,
		_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes
	) : INamedPipeBase(&hPipe), dwOpenMode(dwOpenMode), dwPipeMode(dwPipeMode), dwMaxInstances(dwMaxInstances), hPipe(nullptr), SecurityAttributes({ 0 }) {
		if (!strncmp(lpName, "\\\\.\\pipe\\", 9)) strcpy_s(szName, lpName);
		else sprintf_s(szName, "\\\\.\\pipe\\%s", lpName);

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

	NamedPipeClient::NamedPipeClient(
		_In_z_ A_LPCSTR lpName,
		_In_ PipeOpenMode dwOpenMode,
		_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes
	) : INamedPipeBase(&hPipe), dwOpenMode(dwOpenMode), SecurityAttributes({ 0 }) {
		if (!strncmp(lpName, "\\\\.\\pipe\\", 9)) strcpy_s(szName, lpName);
		else sprintf_s(szName, "\\\\.\\pipe\\%s", lpName);

		if (lpSecurityAttributes) {
			memcpy(&SecurityAttributes, lpSecurityAttributes, sizeof(SECURITY_ATTRIBUTES));
			bSecurityAttributesActive = true;
		}
		else bSecurityAttributesActive = false;
	}

	A_VOID NamedPipeClient::Create() {
		AuroraContextStart();

		A_DWORD dwDesiredAccess;
		switch (dwOpenMode) {
		case PipeOpenMode::Inbound:
			dwDesiredAccess = GENERIC_READ;
			break;
		case PipeOpenMode::Outbound:
			dwDesiredAccess = GENERIC_WRITE;
			break;
		case PipeOpenMode::Duplex:
			dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
			break;
		default:
			dwDesiredAccess = 0;
			break;
		}

		hPipe = CreateFileA(
			szName,
			dwDesiredAccess,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			bSecurityAttributesActive ? &SecurityAttributes : nullptr,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			nullptr
		);

		if (hPipe == INVALID_HANDLE_VALUE) AuroraThrow(WindowsApiException, "CreateFileA");

		AuroraContextEnd();
	}

	AnonymousPipe::AnonymousPipe(
		_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		_In_ SIZE_T nSize
	) : nSize(nSize), hReadPipe(nullptr), hWritePipe(nullptr), SecurityAttributes({ 0 }) {
		if (lpSecurityAttributes) {
			memcpy(&SecurityAttributes, lpSecurityAttributes, sizeof(SECURITY_ATTRIBUTES));
			bSecurityAttributesActive = true;
		}
		else bSecurityAttributesActive = false;
	}

	A_VOID AnonymousPipe::Create() {
		AuroraContextStart();

		if (!CreatePipe(
			&hReadPipe,
			&hWritePipe,
			bSecurityAttributesActive ? &SecurityAttributes : nullptr,
			nSize
		)) AuroraThrow(WindowsApiException, "CreatePipe");

		AuroraContextEnd();
	}

	A_VOID AnonymousPipe::Read(
		_Out_writes_bytes_(dwNumberOfBytesToRead) A_LPVOID lpBuffer,
		_In_ A_DWORD dwNumberOfBytesToRead,
		_Out_opt_ A_LPDWORD lpNumberOfBytesRead
	) {
		AuroraContextStart();

		if (!lpBuffer) AuroraThrow(ParameterInvalidException, "lpBuffer");

		if (!ReadFile(
			hReadPipe,
			lpBuffer,
			dwNumberOfBytesToRead,
			lpNumberOfBytesRead,
			nullptr
		)) AuroraThrow(WindowsApiException, "ReadFile");

		AuroraContextEnd();
	}

	A_VOID AnonymousPipe::Read(
		_Out_writes_z_(dwSize) A_LPSTR lpString,
		_In_ A_DWORD dwSize
	) {
		AuroraContextStart();

		if (!lpString) AuroraThrow(ParameterInvalidException, "lpString");

		A_LPSTR lpBuffer = new A_CHAR[dwSize];
		A_DWORD dwNumberOfBytesRead;

		if (!ReadFile(
			hReadPipe,
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

	A_VOID AnonymousPipe::Write(
		_In_reads_bytes_(dwNumberOfBytesToWrite) A_LPCVOID lpBuffer,
		_In_ A_DWORD dwNumberOfBytesToWrite,
		_Out_opt_ A_LPDWORD lpNumberOfBytesWritten
	) {
		AuroraContextStart();

		if (!lpBuffer) AuroraThrow(ParameterInvalidException, "lpBuffer");

		if (!WriteFile(
			hWritePipe,
			lpBuffer,
			dwNumberOfBytesToWrite,
			lpNumberOfBytesWritten,
			nullptr
		)) AuroraThrow(WindowsApiException, "WriteFile");

		AuroraContextEnd();
	}

	A_VOID AnonymousPipe::Write(_In_z_ A_LPCSTR lpString) {
		AuroraContextStart();

		if (!lpString) AuroraThrow(ParameterInvalidException, "lpString");

		if (!WriteFile(
			hWritePipe,
			lpString,
			strlen(lpString) + 1,
			nullptr,
			nullptr
		)) AuroraThrow(WindowsApiException, "WriteFile");

		AuroraContextEnd();
	}

	A_VOID AnonymousPipe::Clone(_Reserved_ A_LPVOID) const {
		AuroraContextStart();
		AuroraThrow(NotImplementedException);
		AuroraContextEnd();
	}

	A_VOID AnonymousPipe::Release() {
		if (hReadPipe) {
			CloseHandle(hReadPipe);
			hReadPipe = nullptr;
		}

		if (hWritePipe) {
			CloseHandle(hWritePipe);
			hWritePipe = nullptr;
		}
	}

	AnonymousPipe::~AnonymousPipe() { Release(); }
}