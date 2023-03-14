#include <stdio.h>

//------------------------
// TODO:
// All files:
//		Add copyright and author notice to the top of every file.
//		Inline document everything.
// Console.h: Add more functions.
// Interfaces.h: Take a look into if it is needed in the first place.
// 
// Console.cpp: Same as h.
//------------------------

#include <Windows.h>
#include <type_traits>
#include <concepts>

#include <Aurora/Pipe.h>
#include <Aurora/Binary.h>
#include <Aurora/Memory.h>

using namespace Aurora;

int main() {
	HANDLE hFile = CreateFileA(
		"C:\\Users\\douglas.lyman\\Desktop\\test.txt",
		FILE_GENERIC_READ | FILE_GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);

	if (hFile == INVALID_HANDLE_VALUE) {
		printf("CreateFileA GetLastError: %lu", GetLastError());
		return -1;
	}

	LPCSTR lpString = "Test!";

	if (!WriteFile(
		hFile,
		lpString,
		strlen(lpString) + 1,
		nullptr,
		nullptr
	)) {
		printf("WriteFile GetLastError: %lu", GetLastError());
		return -1;
	}

	FlushFileBuffers(hFile);

	CloseHandle(hFile);
}