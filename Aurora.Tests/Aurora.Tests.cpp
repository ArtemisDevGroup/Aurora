#include <stdio.h>

#include <Aurora/String.h>
#include <Aurora/Color.h>

using namespace Aurora;

#include <Windows.h>

int main() {
	printf("\x1B[38;2;255;0;0mGay\n");
	printf("\x1B[38;2;0;0;255mGay\n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);

	printf("Gay\n");
}