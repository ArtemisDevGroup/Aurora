#include "Exceptions.h"
#include "Array.h"

#define AURORA_CONTEXT_KEY_INVALID 0

namespace Aurora {
	//------------------------------------------------------------------------>
	// Identifiers
	namespace Identifiers {
		AURORA_API const Identifier WindowsApiExceptionId = Identifier::Create("WindowsApiException", sizeof(WindowsApiException));
		AURORA_API const Identifier ParameterInvalidExceptionId = Identifier::Create("ParameterInvalidException", sizeof(ParameterInvalidException));
		AURORA_API const Identifier ErrnoExceptionId = Identifier::Create("ErrnoException", sizeof(ErrnoException));
	}
	//------------------------------------------------------------------------>
	// GlobalExceptionContext
	List<Pair<A_DWORD, List<String>>> g_ExceptionContextList;
	//-----------------------------------
	A_I32 IndexOf(_In_ A_DWORD dwThreadId) {
		for (A_I32 i = 0; i < g_ExceptionContextList.size(); i++) {
			if (g_ExceptionContextList[i].GetFirst() == dwThreadId) return i;
		}
		return INVALID_INDEX;
	}
	//-----------------------------------
	A_DWORD GlobalExceptionContext::SetContext(_In_ const String& Context) {
		A_DWORD dwThreadId = GetCurrentThreadId();
		A_I32 nIndex = IndexOf(dwThreadId);
		if (nIndex == INVALID_INDEX) {
			g_ExceptionContextList.Add({ dwThreadId, List<String>() });
			g_ExceptionContextList[g_ExceptionContextList.size() - 1].GetSecond().Add(Context);
			return dwThreadId;
		}
		else {
			g_ExceptionContextList[nIndex].GetSecond().Add(Context);
			return AURORA_CONTEXT_KEY_INVALID;
		}
	}
	//-----------------------------------
	const List<String>& GlobalExceptionContext::GetContext() {
		return g_ExceptionContextList[IndexOf(GetCurrentThreadId())].GetSecond();
	}
	//-----------------------------------
	A_VOID GlobalExceptionContext::ResetContext(_In_ A_DWORD dwKey) {
		A_I32 nIndex = IndexOf(dwKey);

		if (nIndex != INVALID_INDEX)
			g_ExceptionContextList.Remove(1, nIndex);
	}
	//------------------------------------------------------------------------>
	// IException
	IException::IException(_In_ const String& Message, _In_ const Identifier& Id) : Message(Message), Id(Id) {}
	//-----------------------------------
	constexpr const String& IException::GetMessage() const { return Message; }
	//-----------------------------------
	constexpr const Identifier& IException::GetIdentifier() const { return Id; }
	//-----------------------------------
	A_BOOL IException::operator==(const IException& operand) const {
		return Message == operand.Message && Id == operand.Id;
	}
	//-----------------------------------
	constexpr A_BOOL IException::operator==(const Identifier& operand) const {
		return Id == operand;
	}
	//-----------------------------------
	A_BOOL IException::operator==(const String& operand) const {
		return Message == operand;
	}
	//-----------------------------------
	A_BOOL IException::operator!=(const IException& operand) const {
		return Message != operand.Message || Id != operand.Id;
	}
	//-----------------------------------
	constexpr A_BOOL IException::operator!=(const Identifier& operand) const {
		return Id != operand;
	}
	//-----------------------------------
	A_BOOL IException::operator!=(const String& operand) const {
		return Message != operand;
	}
	//------------------------------------------------------------------------>
	// WindowsApiException
	WindowsApiException::WindowsApiException(_In_ const String& WindowsApiFunction) : IException("A Windows API call failed.", Identifiers::WindowsApiExceptionId), WindowsApiFunction(WindowsApiFunction) {
		dwWindowsApiCode = GetLastError();

		A_CHAR szMessageBuffer[MAX_MSG];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwWindowsApiCode, LANG_SYSTEM_DEFAULT, szMessageBuffer, MAX_MSG, nullptr);

		WindowsApiMessage = szMessageBuffer;
	}
	//-----------------------------------
	constexpr A_DWORD WindowsApiException::GetWindowsCode() const { return dwWindowsApiCode; }
	//-----------------------------------
	constexpr const String& WindowsApiException::GetWindowsMessage() const { return WindowsApiMessage; }
	//-----------------------------------
	constexpr const String& WindowsApiException::GetWindowsFunction() const { return WindowsApiFunction; }
	//------------------------------------------------------------------------>
	// ParameterInvalidException
	ParameterInvalidException::ParameterInvalidException(_In_ const String& ParameterName) : IException("", Identifiers::ParameterInvalidExceptionId), ParameterName(ParameterName) {}
	//-----------------------------------
	constexpr const String& ParameterInvalidException::GetParameterName() const { return ParameterName; }
	//------------------------------------------------------------------------>
	// ErrnoException
	ErrnoException::ErrnoException(_In_ errno_t nErrorCode) : IException("A C standard function has failed.", Identifiers::ErrnoExceptionId), nErrorCode(nErrorCode)  {
		strerror_s(szErrnoString, nErrorCode);
	}
	//-----------------------------------
	constexpr errno_t ErrnoException::GetErrorCode() const { return nErrorCode; }
	//-----------------------------------
	constexpr A_LPCSTR ErrnoException::GetErrorMessage() const { return szErrnoString; }
}