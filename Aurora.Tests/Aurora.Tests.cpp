#include <stdio.h>

#include <Aurora/String.h>
#include <Aurora/Color.h>
#include <Aurora/Console.h>

using namespace Aurora;

#include <Windows.h>

#define PFUNC __PRETTY_FUNCTION__

void C() {
	AuroraContextStart();
	AuroraThrow(ParameterInvalidException, "Test");
	AuroraContextEnd();
}

void B() {
	AuroraContextStart();
	C();
	AuroraContextEnd();
}

void A() {
	AuroraContextStart();
	B();
	AuroraContextEnd();
}

int main() {
	try {
		A();
	}
	catch (ParameterInvalidException& e) {
		printf("Trace:\n");
		for (A_I32 i = 0; i < e.GetFunctionCount(); i++)
			printf("at %s\n", e.GetFunctions()[i]);
	}
}