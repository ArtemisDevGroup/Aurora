#include "Exceptions.h"

#define AURORA_CONTEXT_KEY_INVALID 0

namespace Aurora {
	String g_ExceptionContext;
	A_DWORD g_dwContextKey = AURORA_CONTEXT_KEY_INVALID;
	A_BOOL g_bHasContext = false;

	A_DWORD GlobalExceptionContext::SetContext(_In_ const String& Context) {
		if (!g_bHasContext) {
			g_ExceptionContext = Context;
			g_bHasContext = true;
			return g_dwContextKey++;
		}
		else return AURORA_CONTEXT_KEY_INVALID;
	}

	A_VOID GlobalExceptionContext::ResetContext(_In_ A_DWORD dwKey) { if (g_bHasContext && dwKey == g_dwContextKey) g_bHasContext = false; }

	IException::IException(_In_ const String& Message, _In_ const Identifier& Id) : Message(Message), Id(Id) {}

	constexpr const String& IException::GetMessage() const { return Message; }
}