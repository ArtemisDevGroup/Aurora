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
	ProcessInfo* lpProcInfo = ProcessInfo::Create();

	BasePointer<A_I32> pt(0x99, { 10, 20, 30, 40, 50 });
	WritePtr(lpProcInfo->GetModule(), pt, 10);

	lpProcInfo->Release();
}