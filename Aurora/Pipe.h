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

		Byte = WriteMode_Byte | ReadMode_Byte | WaitMode_Wait | ClientMode_AcceptRemote,
		Message = WriteMode_Message | ReadMode_Message | WaitMode_Wait | ClientMode_AcceptRemote
	};

	struct PipeModeFlags : EnumFlags<PipeMode, A_DWORD> { using EnumFlags::EnumFlags; using enum PipeMode; };

	class INamedPipeBase : public IDisposable {
		HANDLE* phPipe;
	public:
		INamedPipeBase(_In_ LPHANDLE lpPipeHandle);

		virtual A_VOID Create() = 0;

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

		/// <summary>
		/// This function is disabled for this class. Always throws NotImplementedException.
		/// </summary>
		/// <param name="">This functions parameters are reserved.</param>
		/// <exception cref="NotImplementedException"/>
		virtual A_VOID IDisposable::Clone(_Reserved_ A_LPVOID) const;
		INamedPipeBase(const INamedPipeBase&) = delete;

		virtual A_VOID IDisposable::Release();
		~INamedPipeBase();
	};

	class NamedPipeServer : public INamedPipeBase {
		A_CHAR szName[MAX_PATH];
		PipeOpenMode dwOpenMode;
		PipeModeFlags dwPipeMode;
		A_DWORD dwMaxInstances;
		SECURITY_ATTRIBUTES SecurityAttributes;
		A_BOOL bSecurityAttributesActive;
		HANDLE hPipe;

	public:
		NamedPipeServer(
			_In_z_ A_LPCSTR lpName,
			_In_ PipeOpenMode dwOpenMode,
			_In_ PipeModeFlags dwPipeMode,
			_In_range_(1, PIPE_UNLIMITED_INSTANCES) A_DWORD dwMaxInstances = PIPE_UNLIMITED_INSTANCES,
			_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr
		);

		NamedPipeServer(const NamedPipeServer&) = delete;

		virtual A_VOID INamedPipeBase::Create();

		A_VOID Connect() const;
		A_VOID Disconnect() const;
	};

	class NamedPipeClient : public INamedPipeBase {
		A_CHAR szName[MAX_PATH];
		PipeOpenMode dwOpenMode;
		SECURITY_ATTRIBUTES SecurityAttributes;
		A_BOOL bSecurityAttributesActive;
		HANDLE hPipe;

	public:
		NamedPipeClient(
			_In_z_ A_LPCSTR lpName,
			_In_ PipeOpenMode dwOpenMode,
			_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes
		);

		NamedPipeClient(const NamedPipeClient&) = delete;

		virtual A_VOID INamedPipeBase::Create();
	};

	class AnonymousPipe : public IDisposable {
		HANDLE hReadPipe;
		HANDLE hWritePipe;
		SIZE_T nSize;
		SECURITY_ATTRIBUTES SecurityAttributes;
		A_BOOL bSecurityAttributesActive;

	public:
		AnonymousPipe(
			_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr,
			_In_ SIZE_T nSize = 256
		);

		A_VOID Create();

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

		/// <summary>
		/// This function is disabled for this class. Always throws NotImplementedException.
		/// </summary>
		/// <param name="">This functions parameters are reserved.</param>
		/// <exception cref="NotImplementedException"/>
		virtual A_VOID IDisposable::Clone(_Reserved_ A_LPVOID) const;
		virtual A_VOID IDisposable::Release();

		~AnonymousPipe();
	};
}

#endif // !__AURORA_PIPE_H__