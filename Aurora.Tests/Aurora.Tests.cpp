#include <stdio.h>

//------------------------
// TODO:
// All files:
//		Add copyright and author notice to the top of every file.
//		Inline document everything.
// Array.h: Global.
// Binary.h: Global.
// Color.h:	Implement HEX.
// Console.h: Add more functions.
// Definitions.h: Global.
// Events.h: Global.
// Exceptions.h: Global.
// Identification.h: Global.
// Interfaces.h: Take a look into if it is needed in the first place.
// String.h: Fix everything.
// Thread.h: Global.
// Vector.h: Global.
// 
// Color.cpp: Same as h.
// Console.cpp: Same as h.
// Exceptions.cpp: Global.
// Identification.cpp: Global.
// String.cpp: Fix everything.
//------------------------

#include <Windows.h>

class MyException {};

void ThrowsCPPException() { throw MyException(); }
void SEHExceptionFramed() {
	__try {
		char c = *(char*)0;
	}
	__except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		printf("Exception got caught in SEH block.");
	}
}

int main() {
	try {
		SEHExceptionFramed();
	}
	catch (MyException&) {
		printf("Exception got caught in C++ try-catch.");
	}
}