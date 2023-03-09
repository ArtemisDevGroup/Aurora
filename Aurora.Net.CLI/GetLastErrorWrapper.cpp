#include <Windows.h>

using namespace System;

namespace Aurora {
	namespace Net {
		namespace CLI {
			public ref class GetLastErrorHelper {
			public:
				static UInt32 GetLastError() {
					return ::GetLastError();
				}

				static String^ FormatSystemErrorCode(UInt32 code) {
					WCHAR szBuffer[256];
					
					FormatMessageW(
						FORMAT_MESSAGE_FROM_SYSTEM,
						nullptr,
						code,
						LANG_SYSTEM_DEFAULT,
						szBuffer,
						256,
						nullptr
					);

					return gcnew String(szBuffer);
				}
			};
		}
	}
}