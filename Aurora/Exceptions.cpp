#include "Exceptions.h"

#define AURORA_CONTEXT_KEY_INVALID 0

#define MAX_THREADCOUNT 64

namespace Aurora {
	//------------------------------------------------------------------------>
	// Identifiers
	namespace Identifiers {
		AURORA_API const Identifier WindowsApiExceptionId = Identifier::Create("WindowsApiException", sizeof(WindowsApiException));
		AURORA_API const Identifier ParameterInvalidExceptionId = Identifier::Create("ParameterInvalidException", sizeof(ParameterInvalidException));
		AURORA_API const Identifier ErrnoExceptionId = Identifier::Create("ErrnoException", sizeof(ErrnoException));
		AURORA_API const Identifier IndexOutOfBoundsExceptionId = Identifier::Create("IndexOutOfBoundsException", sizeof(IndexOutOfBoundsException));
		AURORA_API const Identifier NotImplementedExceptionId = Identifier::Create("NotImplementedException", sizeof(NotImplementedException));
		AURORA_API const Identifier PointerChainInvalidExceptionId = Identifier::Create("PointerChainInvalidException", sizeof(PointerChainInvalidException));
		AURORA_API const Identifier Read32ExceptionId = Identifier::Create("Read32Exception", sizeof(Read32Exception));
		AURORA_API const Identifier Read64ExceptionId = Identifier::Create("Read64Exception", sizeof(Read64Exception));
		AURORA_API const Identifier Write32ExceptionId = Identifier::Create("Write32Exception", sizeof(Write32Exception));
		AURORA_API const Identifier Write64ExceptionId = Identifier::Create("Write64Exception", sizeof(Write64Exception));
		AURORA_API const Identifier ObjectNotFoundExceptionId = Identifier::Create("ObjectNotFoundException", sizeof(ObjectNotFoundException));
	}
	//------------------------------------------------------------------------>
	// GlobalExceptionContext
	A_CHAR g_szExceptionContextList[MAX_THREADCOUNT][MAX_CALL_TRACE][MAX_NAME];
	A_DWORD g_szdwThreadIds[MAX_THREADCOUNT];
	A_BOOL g_szbIndexIsTaken[MAX_THREADCOUNT];
	A_I32 g_sznTraceIndex[MAX_THREADCOUNT];
	ThrowEventHandler g_lpszfnNextThrowEventFunctions[MAX_THREADCOUNT][MAX_INVOKE];
	A_LPVOID g_lpszNextThrowEventParams[MAX_THREADCOUNT][MAX_INVOKE];
	//-----------------------------------
	A_I32 GetIndexOf(_In_ A_DWORD dwThreadId) {
		for (A_I32 i = 0; i < MAX_THREADCOUNT; i++) {
			if (g_szbIndexIsTaken[i] && g_szdwThreadIds[i] == dwThreadId) return i;
		}
		return INVALID_INDEX;
	}
	//-----------------------------------
	A_I32 GetNextFreeIndex() {
		for (A_I32 i = 0; i < MAX_THREADCOUNT; i++)
			if (!g_szbIndexIsTaken[i]) return i;
		return INVALID_INDEX;
	}
	//-----------------------------------
	A_VOID AllocateIndex(_In_ A_I32 nIndex, _In_ A_DWORD dwThreadId) {
		g_szbIndexIsTaken[nIndex] = true;
		g_szdwThreadIds[nIndex] = dwThreadId;
		g_sznTraceIndex[nIndex] = 0;
	}
	//-----------------------------------
	A_VOID ReleaseIndex(_In_ A_I32 nIndex) {
		g_szbIndexIsTaken[nIndex] = false;
		g_szdwThreadIds[nIndex] = 0;
		g_sznTraceIndex[nIndex] = 0;

		for (A_I32 i = 0; i < MAX_INVOKE; i++) {
			g_lpszfnNextThrowEventFunctions[nIndex][i] = nullptr;
			g_lpszNextThrowEventParams[nIndex][i] = nullptr;
		}
	}
	//-----------------------------------
	A_VOID AddTraceToIndex(_In_ A_I32 nIndex, _In_z_ A_LPCSTR lpTrace) {
		if (g_szbIndexIsTaken[nIndex]) {
			strcpy_s(g_szExceptionContextList[nIndex][g_sznTraceIndex[nIndex]], lpTrace);
			g_sznTraceIndex[nIndex]++;
		}
	}
	//-----------------------------------
	A_VOID RemoveLastTraceFromIndex(_In_ A_I32 nIndex) {
		if (g_szbIndexIsTaken[nIndex]) {
			g_sznTraceIndex[nIndex]--;
			g_szExceptionContextList[nIndex][g_sznTraceIndex[nIndex]][0] = '\0';
		}
	}
	//-----------------------------------
	_Check_return_ A_DWORD GlobalExceptionContext::SetContext(_In_z_ A_LPCSTR lpContext) {
		A_DWORD dwThreadId = GetCurrentThreadId();
		A_I32 nIndex = GetIndexOf(dwThreadId);
	
		if (nIndex == INVALID_INDEX) {
			nIndex = GetNextFreeIndex();
			AllocateIndex(nIndex, dwThreadId);
			AddTraceToIndex(nIndex, lpContext);
			return dwThreadId;
		}
		else {
			AddTraceToIndex(nIndex, lpContext);
			return AURORA_CONTEXT_KEY_INVALID;
		}
	}
	//-----------------------------------
	_Check_return_ _Ret_maybenull_ FunctionsArray GlobalExceptionContext::GetContext() noexcept {
		A_I32 nIndex = GetIndexOf(GetCurrentThreadId());

		if (nIndex != INVALID_INDEX)
			return g_szExceptionContextList[nIndex];
		else return nullptr;
	}
	//-----------------------------------
	_Check_return_ A_I32 GlobalExceptionContext::GetContextCount() noexcept {
		A_I32 nIndex = GetIndexOf(GetCurrentThreadId());
		if (nIndex != INVALID_INDEX)
			return g_sznTraceIndex[nIndex];
		else return INVALID_INDEX;
	}
	//-----------------------------------
	A_VOID GlobalExceptionContext::ResetContext(_In_ A_DWORD dwKey) noexcept {
		if (dwKey == AURORA_CONTEXT_KEY_INVALID) {
			A_I32 nIndex = GetIndexOf(GetCurrentThreadId());
			if (nIndex != INVALID_INDEX)
				RemoveLastTraceFromIndex(nIndex);
		}
		else {
			A_I32 nIndex = GetIndexOf(dwKey);
			if (nIndex != INVALID_INDEX)
				ReleaseIndex(nIndex);
		}
	}
	//------------------------------------------------------------------------>
	// NextThrowEventManager
	A_I32 NextThrowEventManager::QueueEvent(_In_ ThrowEventHandler lpfnHandler, _In_opt_ A_LPVOID lpParameter) {
		A_I32 nIndex = GetIndexOf(GetCurrentThreadId());
		if (nIndex != INVALID_INDEX)
			for (A_I32 i = 0; i < MAX_INVOKE; i++)
				if (!g_lpszfnNextThrowEventFunctions[nIndex][i]) {
					g_lpszfnNextThrowEventFunctions[nIndex][i] = lpfnHandler;
					return i;
				}
		return INVALID_INDEX;
	}
	//-----------------------------------
	A_VOID NextThrowEventManager::Invoke(_In_ IException* lpException) {
		A_I32 nIndex = GetIndexOf(GetCurrentThreadId());
		if (nIndex != INVALID_INDEX)
			for (A_I32 i = 0; i < MAX_INVOKE; i++)
				if (g_lpszfnNextThrowEventFunctions[nIndex][i])
					g_lpszfnNextThrowEventFunctions[nIndex][i](lpException, g_lpszNextThrowEventParams[nIndex][i]);
	}
	//-----------------------------------
	A_VOID NextThrowEventManager::ClearEventQueue(_In_ A_I32 nIndex) {
		A_I32 nLevel1Index = GetIndexOf(GetCurrentThreadId());
		if (nLevel1Index != INVALID_INDEX) {
			if (nIndex == INVALID_INDEX)
				for (A_I32 i = 0; i < MAX_INVOKE; i++) {
					g_lpszfnNextThrowEventFunctions[nLevel1Index][i] = nullptr;
					g_lpszNextThrowEventParams[nLevel1Index][i] = nullptr;
				}
			else {
				g_lpszfnNextThrowEventFunctions[nLevel1Index][nIndex] = nullptr;
				g_lpszNextThrowEventParams[nLevel1Index][nIndex] = nullptr;
			}
		}
	}
	//------------------------------------------------------------------------>
	// IException
	IException::IException(_In_z_ A_LPCSTR lpMessage, _In_ const Identifier& Id) : Id(Id) {
		strcpy_s(szMessage, lpMessage);
	}
	//-----------------------------------
	constexpr _Check_return_ _Ret_z_ A_LPCSTR IException::GetMessage() const noexcept { return szMessage; }
	//-----------------------------------
	constexpr _Check_return_ const Identifier& IException::GetIdentifier() const noexcept { return Id; }
	//-----------------------------------
	A_BOOL IException::operator==(const IException& operand) const {
		return !(strcmp(szMessage, operand.szMessage)) && Id == operand.Id;
	}
	//-----------------------------------
	constexpr A_BOOL IException::operator==(const Identifier& operand) const noexcept {
		return Id == operand;
	}
	//-----------------------------------
	A_BOOL IException::operator==(_In_z_ A_LPCSTR lpMessage) const {
		return !(strcmp(szMessage, lpMessage));
	}
	//-----------------------------------
	A_BOOL IException::operator!=(const IException& operand) const {
		return !!(strcmp(szMessage, operand.szMessage)) || Id != operand.Id;
	}
	//-----------------------------------
	constexpr A_BOOL IException::operator!=(const Identifier& operand) const noexcept {
		return Id != operand;
	}
	//-----------------------------------
	A_BOOL IException::operator!=(_In_z_ A_LPCSTR lpMessage) const {
		return !!(strcmp(szMessage, lpMessage));
	}
	//------------------------------------------------------------------------>
	// WindowsApiException
	WindowsApiException::WindowsApiException(_In_z_ A_LPCSTR lpWindowsApiFunction) : IException("A Windows API call failed.", Identifiers::WindowsApiExceptionId) {
		strcpy_s(szWindowsApiFunction, lpWindowsApiFunction);

		dwWindowsApiCode = GetLastError();
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwWindowsApiCode, LANG_SYSTEM_DEFAULT, szWindowsApiMessage, MAX_MSG, nullptr);
	}
	//-----------------------------------
	constexpr _Check_return_ A_DWORD WindowsApiException::GetWindowsCode() const noexcept { return dwWindowsApiCode; }
	//-----------------------------------
	constexpr _Check_return_ _Ret_z_ A_LPCSTR WindowsApiException::GetWindowsMessage() const noexcept { return szWindowsApiMessage; }
	//-----------------------------------
	constexpr _Check_return_ _Ret_z_ A_LPCSTR WindowsApiException::GetWindowsFunction() const noexcept { return szWindowsApiFunction; }
	//------------------------------------------------------------------------>
	// ParameterInvalidException
	ParameterInvalidException::ParameterInvalidException(_In_z_ A_LPCSTR lpParameterName) : IException("A parameter was invalid.", Identifiers::ParameterInvalidExceptionId) { strcpy_s(szParameterName, lpParameterName); }
	//-----------------------------------
	constexpr _Check_return_ _Ret_z_ A_LPCSTR ParameterInvalidException::GetParameterName() const noexcept { return szParameterName; }
	//------------------------------------------------------------------------>
	// ErrnoException
	ErrnoException::ErrnoException(_In_ errno_t nErrorCode) : IException("A C standard function has failed.", Identifiers::ErrnoExceptionId), nErrorCode(nErrorCode)  {
		strerror_s(szErrnoString, nErrorCode);
	}
	//-----------------------------------
	constexpr _Check_return_ errno_t ErrnoException::GetErrorCode() const noexcept { return nErrorCode; }
	//-----------------------------------
	constexpr _Check_return_ _Ret_z_ A_LPCSTR ErrnoException::GetErrorMessage() const noexcept { return szErrnoString; }
	//------------------------------------------------------------------------>
	// IndexOutOfBoundsException
	IndexOutOfBoundsException::IndexOutOfBoundsException(_In_ A_I32 nIndex, _In_ A_I32 nHighestValidIndex) : IException("An index was out of array bounds.", Identifiers::IndexOutOfBoundsExceptionId), nIndex(nIndex), nMaxValidIndex(nHighestValidIndex) {}
	//-----------------------------------
	constexpr _Check_return_ A_I32 IndexOutOfBoundsException::GetIndex() const noexcept { return nIndex; }
	//-----------------------------------
	constexpr _Check_return_ A_I32 IndexOutOfBoundsException::GetHighestValidIndex() const noexcept { return nMaxValidIndex; }
	//------------------------------------------------------------------------>
	// NotImplementedException
	NotImplementedException::NotImplementedException() : IException("This feature has not yet been implemented", Identifiers::NotImplementedExceptionId) {}
	//------------------------------------------------------------------------>
	// PointerChainInvalidException
	PointerChainInvalidException::PointerChainInvalidException(_In_ A_I32 nChainLevel) : IException("A pointer in the chain was invalid.", Identifiers::PointerChainInvalidExceptionId), nChainLevel(nChainLevel) {}
	//-----------------------------------
	constexpr A_I32 PointerChainInvalidException::GetChainLevel() const noexcept { return nChainLevel; }
	//------------------------------------------------------------------------>
	// Read32Exception
	Read32Exception::Read32Exception(_In_ A_ADDR32 uAddress, _In_ A_DWORD dwSize) : IMemoryExceptionBase("A read operation has failed.", Identifiers::Read32ExceptionId, uAddress, dwSize) {}
	//------------------------------------------------------------------------>
	// Read64Exception
	Read64Exception::Read64Exception(_In_ A_ADDR64 uAddress, _In_ A_DWORD dwSize) : IMemoryExceptionBase("A read operation has failed", Identifiers::Read64ExceptionId, uAddress, dwSize) {}
	//------------------------------------------------------------------------>
	// Write32Exception
	Write32Exception::Write32Exception(_In_ A_ADDR32 uAddress, _In_ A_DWORD dwSize) : IMemoryExceptionBase("A write operation has failed", Identifiers::Write32ExceptionId, uAddress, dwSize) {}
	//------------------------------------------------------------------------>
	// Write64Exception
	Write64Exception::Write64Exception(_In_ A_ADDR64 uAddress, _In_ A_DWORD dwSize) : IMemoryExceptionBase("A write operation has failed", Identifiers::Write64ExceptionId, uAddress, dwSize) {}
	//------------------------------------------------------------------------>
	// ObjectNotFoundException
	ObjectNotFoundException::ObjectNotFoundException(_In_z_ A_LPCSTR lpObjectType, _In_z_ A_LPCSTR lpObjectName) : IException("An object was not found.", Identifiers::ObjectNotFoundExceptionId) {
		strcpy_s(szObjectType, lpObjectType);
		strcpy_s(szObjectName, lpObjectName);
	}
	constexpr _Check_return_ _Ret_z_ A_LPCSTR ObjectNotFoundException::GetObjectType() const noexcept { return szObjectType; }
	//-----------------------------------
	constexpr _Check_return_ _Ret_z_ A_LPCSTR ObjectNotFoundException::GetObjectName() const noexcept { return szObjectName; }
}