#include <Windows.h>
#include <vcclr.h>

using namespace System;

namespace Aurora {
	namespace Net {
		namespace CLI {
			public ref class PipeHelper {
			public:
				static IntPtr CreatePipe(String^ name, UInt32 openMode, UInt32 pipeMode) {
					pin_ptr<const wchar_t> lpString = PtrToStringChars(name);
					
					DWORD dwOpenMode;

					switch (openMode) {
					case 0:
						dwOpenMode = PIPE_ACCESS_INBOUND;
						break;
					case 1:
						dwOpenMode = PIPE_ACCESS_OUTBOUND;
						break;
					case 2:
						dwOpenMode = PIPE_ACCESS_DUPLEX;
						break;
					default:
						dwOpenMode = 0;
						break;
					}

					HANDLE hPipe = CreateNamedPipeW(
						lpString,
						dwOpenMode,
						pipeMode,
						PIPE_UNLIMITED_INSTANCES,
						1024,
						1024,
						INFINITE,
						nullptr
					);

					return IntPtr(hPipe);
				}

				static IntPtr OpenPipe(String^ name, UInt32 openMode) {
					pin_ptr<const wchar_t> lpString = PtrToStringChars(name);

					DWORD dwDesiredAccess;

					switch (openMode) {
					case 0:
						dwDesiredAccess = GENERIC_READ;
						break;
					case 1:
						dwDesiredAccess = GENERIC_WRITE;
						break;
					case 2:
						dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
						break;
					default:
						dwDesiredAccess = 0;
						break;
					}

					HANDLE hPipe = CreateFileW(
						lpString,
						dwDesiredAccess,
						FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
						nullptr,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						nullptr
					);

					return IntPtr(hPipe);
				}

				static Void ClosePipe(IntPtr hPipe) {
					if (hPipe != IntPtr::Zero) CloseHandle(hPipe.ToPointer());
				}

				static Boolean WritePipe(IntPtr hPipe, array<Byte>^ data) {
					pin_ptr<const unsigned char> lpData = &data[0];

					return WriteFile(
						hPipe.ToPointer(),
						lpData,
						data->Length,
						nullptr,
						nullptr
					);
				}

				static Boolean ReadPipe(IntPtr hPipe, array<Byte>^ data) {
					pin_ptr<unsigned char> lpData = &data[0];

					return ReadFile(
						hPipe.ToPointer(),
						lpData,
						data->Length,
						nullptr,
						nullptr
					);
				}
			};
		}
	}
}