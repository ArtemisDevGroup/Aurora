#ifndef __AURORA_LOGGER_H__
#define __AURORA_LOGGER_H__

#include "Definitions.h"
#include "Console.h"

namespace Aurora {
	class AURORA_API Logger {
		A_BOOL bLogToConsole;

		A_BOOL bLogToFile;
		HANDLE hFile;

	public:
		constexpr Logger() noexcept;

		Logger(
			_In_ A_BOOL bLogToConsole,
			_In_ A_BOOL blogToFile,
			_In_opt_z_ A_LPCSTR lpLogFileName = nullptr
		);
	};
}

#endif // !__AURORA_LOGGER_H__