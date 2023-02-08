#include <stdio.h>

#include <Aurora/String.h>
#include <Aurora/Color.h>

using namespace Aurora;

#include <Windows.h>

int main() {
	// printf("\x1B[38;2;255;0;0mtest\n");
	// printf("Another test\n");

	RGB rgb(255, 200, 255);
	printf("%s\n", rgb.ToString().GetCString());
	printf("%s\n", rgb.ToHSL().ToString().GetCString());
}