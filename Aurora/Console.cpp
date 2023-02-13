#include "Console.h"

#include <stdio.h>
#include <Windows.h>

namespace Aurora {
	FILE* g_pStdOut;
	FILE* g_pStdIn;

	A_VOID AURORA_API CreateConsole() {
		AuroraContextStart();
		if (!AllocConsole()) AuroraThrow(WindowsApiException, "AllocConsole");
		AuroraContextEnd();
	}

	A_VOID AURORA_API ReleaseConsole() {
		AuroraContextStart();
		if (!FreeConsole()) AuroraThrow(WindowsApiException, "FreeConsole");
		AuroraContextEnd();
	}

	A_VOID AURORA_API OpenStream(_In_ StandardStream Stream) {
		AuroraContextStart();
		errno_t nErrno = 0;

		switch (Stream) {
		case StandardStream::In:
			if ((nErrno = freopen_s(&g_pStdIn, "CONIN$", "r", stdin)) != 0) AuroraThrow(ErrnoException, nErrno);
			break;
		case StandardStream::Out:
			if ((nErrno = freopen_s(&g_pStdOut, "CONOUT$", "w", stdout)) != 0) AuroraThrow(ErrnoException, nErrno);
			break;
		default:
			AuroraThrow(ParameterInvalidException, "Stream");
		}

		AuroraContextEnd();
	}

	A_VOID AURORA_API CloseStream(_In_ StandardStream Stream) {
		AuroraContextStart();

		switch (Stream) {

		}

		AuroraContextEnd();
	}

	A_VOID AURORA_API CloseAllStreams();

	A_VOID AURORA_API SetConsoleForegroundColor(_In_ const RGB& TrueColor) {	
		printf("\x1B[38;2;%hhu;%hhu;%hhum", TrueColor.uR, TrueColor.uG, TrueColor.uB);
	}

	A_VOID AURORA_API ResetConsoleForegroundColor() {
		printf("\x1B[1;39m");
	}

	A_VOID AURORA_API SetConsoleBackgroundColor(_In_ const RGB& TrueColor) {
		printf("\x1B[48;2;%hhu;%hhu;%hhum", TrueColor.uR, TrueColor.uG, TrueColor.uB);
	}

	A_VOID AURORA_API ResetConsoleBackgroundColor() {
		printf("\x1B[1;49m");
	}

	A_VOID AURORA_API SetConsoleForegroundColorLegacy(_In_ ConsoleColorLegacyFlags wColorFlags) {
		AuroraContextStart();

		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdOut == INVALID_HANDLE_VALUE) AuroraThrow(WindowsApiException, "GetStdHandle");

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) AuroraThrow(WindowsApiException, "GetConsoleScreenBufferInfo");

		WORD wAttributes = csbi.wAttributes;
		if (!!(wAttributes & (1 << 0))) wAttributes ^= (1 << 0);
		if (!!(wAttributes & (1 << 1))) wAttributes ^= (1 << 1);
		if (!!(wAttributes & (1 << 2))) wAttributes ^= (1 << 2);
		if (!!(wAttributes & (1 << 3))) wAttributes ^= (1 << 3);

		wAttributes |= wColorFlags.GetForegroundLiteral();

		if (!SetConsoleTextAttribute(hStdOut, wAttributes)) AuroraThrow(WindowsApiException, "SetConsoleTextAttribute");

		AuroraContextEnd();
	}

	A_VOID AURORA_API SetConsoleBackgroundColorLegacy(_In_ ConsoleColorLegacyFlags wColorFlags) {
		AuroraContextStart();

		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdOut == INVALID_HANDLE_VALUE) AuroraThrow(WindowsApiException, "GetStdHandle");

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) AuroraThrow(WindowsApiException, "GetConsoleScreenBufferInfo");

		WORD wAttributes = csbi.wAttributes;
		if (!!(wAttributes & (1 << 4))) wAttributes ^= (1 << 4);
		if (!!(wAttributes & (1 << 5))) wAttributes ^= (1 << 5);
		if (!!(wAttributes & (1 << 6))) wAttributes ^= (1 << 6);
		if (!!(wAttributes & (1 << 7))) wAttributes ^= (1 << 7);

		wAttributes |= wColorFlags.GetForegroundLiteral();

		if (!SetConsoleTextAttribute(hStdOut, wAttributes)) AuroraThrow(WindowsApiException, "SetConsoleTextAttribute");

		AuroraContextEnd();
	}
}