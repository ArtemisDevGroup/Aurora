#include <stdio.h>

#include <Aurora/String.h>

using namespace Aurora;

#include <Windows.h>

int main() {
	printf("\x1B[38;2;255;0;0mtest\n");
	printf("Another test\n");
}