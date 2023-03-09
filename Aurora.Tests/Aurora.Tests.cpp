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

#include <Aurora/Pipe.h>

using namespace Aurora;

int main() {
	NamedPipeServer server(
		"\\\\.\\pipe\\cppcs_testpipe",
		PipeOpenMode::Inbound,
		PipeModeFlags::Message
	);

	try {
		server.Create();
	}
	catch (WindowsApiException& e) {
		printf("%s\n", e.GetWindowsMessage());
	}
	
	server.Connect();
	printf("Connected to client.\n");
	
	WCHAR szBuffer[64] = { L'\000' };
	server.Read(szBuffer, 64 * 2);
	
	wprintf_s(L"%s\n", szBuffer);

	server.Disconnect();
	server.Release();

	return 0;
}