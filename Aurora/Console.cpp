#include "Console.h"

#include <stdio.h>
#include <Windows.h>

namespace Aurora {
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
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(hStdOut, &csbi);
		WORD wAttributes = csbi.wAttributes;
		if (!!(wAttributes & (1 << 0))) wAttributes ^= (1 << 0);
		if (!!(wAttributes & (1 << 1))) wAttributes ^= (1 << 1);
		if (!!(wAttributes & (1 << 2))) wAttributes ^= (1 << 2);
		if (!!(wAttributes & (1 << 3))) wAttributes ^= (1 << 3);

		wAttributes |= wColorFlags.GetForegroundLiteral();

		SetConsoleTextAttribute(hStdOut, wAttributes);
	}

	A_VOID AURORA_API SetConsoleBackgroundColorLegacy(_In_ ConsoleColorLegacyFlags wColorFlags) {
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(hStdOut, &csbi);
		WORD wAttributes = csbi.wAttributes;
		if (!!(wAttributes & (1 << 4))) wAttributes ^= (1 << 4);
		if (!!(wAttributes & (1 << 5))) wAttributes ^= (1 << 5);
		if (!!(wAttributes & (1 << 6))) wAttributes ^= (1 << 6);
		if (!!(wAttributes & (1 << 7))) wAttributes ^= (1 << 7);

		wAttributes |= wColorFlags.GetBackgroundLiteral();

		SetConsoleTextAttribute(hStdOut, wAttributes);
	}
}