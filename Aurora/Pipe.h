#ifndef __AURORA_PIPE_H__
#define __AURORA_PIPE_H__

#include "Definitions.h"
#include "Interfaces.h"
#include "Exceptions.h"

#include <Windows.h>

namespace Aurora {
	enum class PipeOpenMode {
		Inbound = PIPE_ACCESS_INBOUND,
		Outbound = PIPE_ACCESS_OUTBOUND,
		Duplex = PIPE_ACCESS_DUPLEX
	};

	enum class PipeMode {
		WriteMode_Byte = PIPE_TYPE_BYTE,
		WriteMode_Message = PIPE_TYPE_MESSAGE,

		ReadMode_Byte = PIPE_READMODE_BYTE,
		ReadMode_Message = PIPE_READMODE_MESSAGE,

		WaitMode_Wait = PIPE_WAIT,
		WaitMode_NoWait = PIPE_NOWAIT,

		ClientMode_AcceptRemote = PIPE_ACCEPT_REMOTE_CLIENTS,
		ClientMode_RejectRemote = PIPE_REJECT_REMOTE_CLIENTS,

		Byte = WriteMode_Byte | ReadMode_Byte,
		Message = WriteMode_Message | ReadMode_Message
	};

	struct PipeModeFlags : EnumFlags<PipeMode, A_DWORD> { using EnumFlags::EnumFlags; using enum PipeMode; };

	class NamedPipeServer : public IDisposable {
		A_CHAR szName[MAX_PATH];
		HANDLE hPipe;

	public:
		NamedPipeServer(
			_In_z_ A_LPCSTR lpName,
			_In_ PipeOpenMode dwOpenMode,
			_In_ PipeModeFlags dwPipeMode,
			_In_range_(1, PIPE_UNLIMITED_INSTANCES) A_DWORD dwMaxInstances = PIPE_UNLIMITED_INSTANCES,
			_In_ LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr
		);

		A_VOID Create();
		A_VOID Connect();
		A_VOID Disconnect();

		A_VOID Read(
			_Out_writes_bytes_(dwNumberOfBytesToRead) A_LPVOID lpBuffer,
			_In_ A_DWORD dwNumberOfBytesToRead,
			_Out_opt_ A_LPDWORD lpNumberOfBytesRead = nullptr
		);

		A_VOID Read(
			_Out_writes_z_(dwSize) A_LPSTR lpString,
			_In_ A_DWORD dwSize
		);

		template<typename T>
		A_VOID Read(_Out_ T* lpBuffer) {
			AuroraContextStart();

			Read(
				(A_LPVOID)lpBuffer,
				sizeof(T),
				nullptr
			);

			AuroraContextEnd();
		}

		A_VOID Write(
			_In_reads_bytes_(dwNumberOfBytesToWrite) A_LPCVOID lpBuffer,
			_In_ A_DWORD dwNumberOfBytesToWrite,
			_Out_opt_ A_LPDWORD lpNumberOfBytesWritten = nullptr
		);

		A_VOID Write(_In_z_ A_LPCSTR lpString);
		
		template<typename T>
		A_VOID Write(_In_ const T* lpBuffer) {
			AuroraContextStart();

			Write(
				(A_LPCVOID)lpBuffer,
				sizeof(T),
				nullptr
			);

			AuroraContextEnd();
		}

		virtual A_VOID IDisposable::Clone(_Out_ A_LPVOID lpDestination) const { /* Set context and throw NotImplementedException */ }

		NamedPipeServer(const NamedPipeServer&) = delete;

		virtual A_VOID IDisposable::Release() {
			if (hPipe) {
				CloseHandle(hPipe);
				hPipe = nullptr;
			}
		}

		~NamedPipeServer() { Release(); }
	};

	class NamedPipeClient {

	};

	class AnonymousPipe {

	};
}

#endif // !__AURORA_PIPE_H__