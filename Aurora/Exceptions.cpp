#include "Exceptions.h"

#define AURORA_CONTEXT_KEY_INVALID 0

namespace Aurora {
	CHAR g_szExceptionContext[MAX_NAME];
	DWORD g_dwContextKey = AURORA_CONTEXT_KEY_INVALID;
	bool g_bHasContext = false;

	DWORD GlobalExceptionContext::SetContext(_In_z_ LPCSTR lpFunctionName) {
		if (!g_bHasContext) {
			strcpy_s(g_szExceptionContext, lpFunctionName);
			g_bHasContext = true;
			return g_dwContextKey++;
		}
		else return AURORA_CONTEXT_KEY_INVALID;
	}

	void GlobalExceptionContext::ResetContext(_In_ DWORD dwKey) { if (g_bHasContext && dwKey == g_dwContextKey) g_bHasContext = false; }

	IException::IException(_In_z_ LPCSTR lpMessage, _In_ const Identifier& id) : Id(id) { strcpy_s(szMessage, lpMessage); }
}