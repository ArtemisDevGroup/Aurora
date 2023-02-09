#include "Console.h"

#include <stdio.h>

namespace Aurora {
	A_VOID AURORA_API SetConsoleForegroundColor(_In_ const RGB& TrueColor) {	
		printf("\x1B[38;2;%hhu;%hhu;%hhum", TrueColor.uR, TrueColor.uG, TrueColor.uB);
	}
}