#include "Exceptions.h"

#define AURORA_CONTEXT_KEY_INVALID 0

namespace Aurora {
	CHAR g_szExceptionContext[MAX_NAME];
	DWORD g_dwContextKey = AURORA_CONTEXT_KEY_INVALID;
	bool bHasContext = FALSE;

	DWORD GlobalExceptionContext::SetContext(_In_z_ LPCSTR lpFunctionName) {
		if (!bHasContext) {
			strcpy_s(g_szExceptionContext, lpFunctionName);
			bHasContext = true;
			return g_dwContextKey++;
		}
		else return AURORA_CONTEXT_KEY_INVALID;
	}

	void GlobalExceptionContext::ResetContext(_In_ DWORD dwKey) { if (bHasContext && dwKey == g_dwContextKey) bHasContext = false; }
}