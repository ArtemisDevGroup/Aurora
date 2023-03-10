#ifndef __AURORA_PIPE_H__
#define __AURORA_PIPE_H__

#include "Definitions.h"
#include "Interfaces.h"
#include "Exceptions.h"

#include <Windows.h>

namespace Aurora {
	/// <summary>
	/// Represents the access mode of a pipe server or client instance.
	/// </summary>
	enum class PipeOpenMode {
		/// <summary>
		/// The pipe instance accepts inbound data.
		/// </summary>
		Inbound = PIPE_ACCESS_INBOUND,

		/// <summary>
		/// The pipe instance accepts outbound data.
		/// </summary>
		Outbound = PIPE_ACCESS_OUTBOUND,

		/// <summary>
		/// The pipe instance accepts both inbound and outbound data.
		/// </summary>
		Duplex = PIPE_ACCESS_DUPLEX
	};

	/// <summary>
	/// Represents different settings related to the pipe server instance.
	/// </summary>
	enum class PipeMode {
		/// <summary>
		/// The pipe writes data as a stream of bytes.
		/// </summary>
		WriteMode_Byte = PIPE_TYPE_BYTE,

		/// <summary>
		/// The pipe writes data as messages (chunks of bytes).
		/// </summary>
		WriteMode_Message = PIPE_TYPE_MESSAGE,

		/// <summary>
		/// The pipe reads data as a stream of bytes.
		/// </summary>
		ReadMode_Byte = PIPE_READMODE_BYTE,

		/// <summary>
		/// The pipe reads data as messages (chunks of bytes).
		/// </summary>
		ReadMode_Message = PIPE_READMODE_MESSAGE,

		/// <summary>
		/// Blocking mode is enabled. Any operations are not completed until there is data to read, all data is written, or a client is connected.
		/// </summary>
		WaitMode_Wait = PIPE_WAIT,

		/// <summary>
		/// Nonblocking mode is enabled. In this mode, any operation always returns immediately.
		/// </summary>
		WaitMode_NoWait = PIPE_NOWAIT,

		/// <summary>
		/// Accepts remote clients.
		/// </summary>
		ClientMode_AcceptRemote = PIPE_ACCEPT_REMOTE_CLIENTS,

		/// <summary>
		/// Reject remote clients.
		/// </summary>
		ClientMode_RejectRemote = PIPE_REJECT_REMOTE_CLIENTS,

		/// <summary>
		/// A preset for byte read and write operations to the pipe.
		/// </summary>
		Byte = WriteMode_Byte | ReadMode_Byte | WaitMode_Wait | ClientMode_AcceptRemote,

		/// <summary>
		/// A preset for message read and write operations to the pipe.
		/// </summary>
		Message = WriteMode_Message | ReadMode_Message | WaitMode_Wait | ClientMode_AcceptRemote
	};

	/// <summary>
	/// Represents different settings related to the pipe server instance.
	/// </summary>
	struct AURORA_API PipeModeFlags : EnumFlags<PipeMode, A_DWORD> { using EnumFlags::EnumFlags; using enum PipeMode; };

	/// <summary>
	/// An interface containing the shared features between a named pipe server and client.
	/// </summary>
	class AURORA_API INamedPipeBase : public IDisposable {
		HANDLE* phPipe;

	public:
		/// <summary>
		/// Sets the handle to pass to the ReadFile and WriteFile functions.
		/// </summary>
		/// <param name="lpPipeHandle">- A pointer to the handle to operate on.</param>
		INamedPipeBase(_In_ LPHANDLE lpPipeHandle);

		/// <summary>
		/// A purely virtual function that opens or creates an instance of a named pipe for the class to operate on.
		/// </summary>
		virtual A_VOID Create() = 0;

		/// <summary>
		/// Reads data from the end of the pipe.
		/// </summary>
		/// <param name="lpBuffer">- A pointer to a buffer to receive the data from the pipe.</param>
		/// <param name="dwNumberOfBytesToRead">- The number of bytes to attempt to read from the pipe.</param>
		/// <param name="lpNumberOfBytesRead">- A pointer to a DWORD to receive the number of bytes successfully read from the pipe. This parameter is optional.</param>
		/// <exception cref="ParameterInvalidException"/>
		/// <exception cref="WindowsApiException"/>
		A_VOID Read(
			_Out_writes_bytes_(dwNumberOfBytesToRead) A_LPVOID lpBuffer,
			_In_ A_DWORD dwNumberOfBytesToRead,
			_Out_opt_ A_LPDWORD lpNumberOfBytesRead = nullptr
		);

		/// <summary>
		/// Reads a string from the end of the pipe.
		/// </summary>
		/// <param name="lpString">- A pointer to a buffer to receive the read string.</param>
		/// <param name="dwSize">- The size of the buffer in characters.</param>
		/// <exception cref="ParameterInvalidException"/>
		/// <exception cref="WindowsApiException"/>
		A_VOID Read(
			_Out_writes_z_(dwSize) A_LPSTR lpString,
			_In_ A_DWORD dwSize
		);

		/// <summary>
		/// Reads data from the end of the pipe.
		/// </summary>
		/// <typeparam name="T">- The type of the data to read.</typeparam>
		/// <returns>The read data.</returns>
		/// <exception cref="ParameterInvalidException"/>
		/// <exception cref="WindowsApiException"/>
		template<typename T>
		inline T Read() {
			AuroraContextStart();

			T ret = T();

			Read(
				(A_LPVOID)&ret,
				sizeof(T),
				nullptr
			);

			AuroraContextEnd();
			return ret;
		}

		/// <summary>
		/// Writes data to the end of the pipe.
		/// </summary>
		/// <param name="lpBuffer">- A pointer to a buffer containing the data to write.</param>
		/// <param name="dwNumberOfBytesToWrite">- The number of bytes to write to the pipe</param>
		/// <param name="lpNumberOfBytesWritten">- A pointer to a DWORD to receive the number of bytes successfully written to the pipe. This parameter is optional.</param>
		/// <exception cref="ParameterInvalidException"/>
		/// <exception cref="WindowsApiException"/>
		A_VOID Write(
			_In_reads_bytes_(dwNumberOfBytesToWrite) A_LPCVOID lpBuffer,
			_In_ A_DWORD dwNumberOfBytesToWrite,
			_Out_opt_ A_LPDWORD lpNumberOfBytesWritten = nullptr
		);

		/// <summary>
		/// Writes a string to the end of the pipe.
		/// </summary>
		/// <param name="lpString">- A pointer to the string to write.</param>
		/// <exception cref="ParameterInvalidException"/>
		/// <exception cref="WindowsApiException"/>
		A_VOID Write(_In_z_ A_LPCSTR lpString);

		/// <summary>
		/// Writes data to the end of the pipe.
		/// </summary>
		/// <typeparam name="T">- The type of the data to write.</typeparam>
		/// <param name="refBuffer">- A reference to the data to write.</param>
		/// <exception cref="ParameterInvalidException"/>
		/// <exception cref="WindowsApiException"/>
		template<typename T>
		A_VOID Write(_In_ const T& refBuffer) {
			AuroraContextStart();

			Write(
				(A_LPCVOID)&refBuffer,
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

		/// <summary>
		/// Releases the current instance handle.
		/// </summary>
		virtual A_VOID IDisposable::Release();
		~INamedPipeBase();
	};

	/// <summary>
	/// A class for creating and interacting with a named pipe server.
	/// </summary>
	class AURORA_API NamedPipeServer : public INamedPipeBase {
		A_CHAR szName[MAX_PATH];
		PipeOpenMode dwOpenMode;
		PipeModeFlags dwPipeMode;
		A_DWORD dwMaxInstances;
		SECURITY_ATTRIBUTES SecurityAttributes;
		A_BOOL bSecurityAttributesActive;
		HANDLE hPipe;

	public:
		/// <summary>
		/// Sets the parameters of a named pipe server instance.
		/// </summary>
		/// <param name="lpName">- The name of the pipe, either as-is or prefixed with '\\.\pipe\'.</param>
		/// <param name="dwOpenMode">- A constant defining the open mode of the pipe.</param>
		/// <param name="dwPipeMode">- Bit flags defining the pipe settings.</param>
		/// <param name="dwMaxInstances">- </param>
		/// <param name="lpSecurityAttributes"></param>
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

	class AURORA_API NamedPipeClient : public INamedPipeBase {
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

	class AURORA_API AnonymousPipe : public IDisposable {
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