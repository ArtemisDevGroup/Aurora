#ifndef __AURORA_EXCEPTIONS_H__
#define __AURORA_EXCEPTIONS_H__

#include "Definitions.h"
#include "Identification.h"

#include <string.h>
#include <Windows.h>
#undef GetMessage

/// <summary>
/// <para>Sets the context of all thrown exceptions to report the current function as the origin of the call.</para>
/// <para>If this function is called inside an already contextualized call, this function will be added to the call trace.</para>
/// </summary>
#define AuroraContextStart() A_DWORD dwKey = Aurora::GlobalExceptionContext::SetContext(__FUNCTION__)
// Ends the contextualized call. Should be called right before returning.
#define AuroraContextEnd() Aurora::GlobalExceptionContext::ResetContext(dwKey)
// Throws an exception inside of a contextualized call.
#define AuroraThrow(Exception, ...) throw Exception(__VA_ARGS__).WithContext(__FUNCTION__, __FILE__, __LINE__)

#define MAX_CALL_TRACE 64

namespace Aurora {
	namespace Identifiers {
		AURORA_API extern const Identifier WindowsApiExceptionId;
		AURORA_API extern const Identifier ParameterInvalidExceptionId;
		AURORA_API extern const Identifier ErrnoExceptionId;
		AURORA_API extern const Identifier IndexOutOfBoundsExceptionid;
	}

	typedef const A_CHAR(*FunctionsArray)[MAX_NAME];

	class AURORA_API GlobalExceptionContext {
	public:
		GlobalExceptionContext() = delete;
		GlobalExceptionContext(const GlobalExceptionContext&) = delete;
		~GlobalExceptionContext() = delete;

		static _Check_return_ A_DWORD SetContext(_In_z_ A_LPCSTR lpContext);
		static _Check_return_ _Ret_maybenull_ FunctionsArray GetContext() noexcept;
		static _Check_return_ A_I32 GetContextCount() noexcept;
		static A_VOID ResetContext(_In_ A_DWORD dwKey) noexcept;
	};

	class AURORA_API IException {
		A_CHAR szMessage[MAX_MSG];
		Identifier Id;

	public:
		IException(_In_z_ A_LPCSTR lpMessage, _In_ const Identifier& Id);

		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetMessage() const noexcept;
		constexpr _Check_return_ const Identifier& GetIdentifier() const noexcept;

		A_BOOL operator==(const IException&) const;
		constexpr A_BOOL operator==(const Identifier&) const noexcept;
		A_BOOL operator==(_In_z_ A_LPCSTR) const;

		A_BOOL operator!=(const IException&) const;
		constexpr A_BOOL operator!=(const Identifier&) const noexcept;
		A_BOOL operator!=(_In_z_ A_LPCSTR) const;
	};

	template<class Derived>
	class AURORA_API IExceptionContext {
		A_CHAR lpszFunctions[MAX_CALL_TRACE][MAX_NAME];
		A_CHAR szCoreFunction[MAX_NAME];
		A_CHAR szFilePath[MAX_PATH];
		A_I32 nFunctionsIndex;
		A_I32 nLine;

	public:
		inline IExceptionContext() : lpszFunctions(), szCoreFunction(), szFilePath(), nFunctionsIndex(0), nLine(0) {}

		inline Derived WithContext(_In_z_ A_LPCSTR lpFunction, _In_z_ A_LPCSTR lpFile, _In_ A_I32 nLine) {
			for (A_I32 i = 0; i < GlobalExceptionContext::GetContextCount(); i++)
				strcpy_s(lpszFunctions[i], GlobalExceptionContext::GetContext()[i]);
			GlobalExceptionContext::ResetContext(GetCurrentThreadId());

			strcpy_s(szCoreFunction, lpFunction);
			strcpy_s(szFilePath, lpFile);
			this->nLine = nLine;
			return *(Derived*)this;
		}

		constexpr FunctionsArray GetFunctions() const { return lpszFunctions; }
		constexpr _Check_return_ A_I32 GetFunctionCount() const { return nFunctionsIndex; }
		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetCoreFunction() const { return szCoreFunction; }
		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetFile() const { return szFilePath; }
		constexpr _Check_return_ A_I32 GetLine() const { return nLine; }
	};

	class WindowsApiException : public IException, public IExceptionContext<WindowsApiException> {
		A_DWORD dwWindowsApiCode;
		A_CHAR szWindowsApiMessage[MAX_MSG];
		A_CHAR szWindowsApiFunction[MAX_NAME];

	public:
		WindowsApiException(_In_z_ A_LPCSTR lpWindowsApiFunction);
		constexpr _Check_return_ A_DWORD GetWindowsCode() const noexcept;
		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetWindowsMessage() const noexcept;
		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetWindowsFunction() const noexcept;
	};

	class ParameterInvalidException : public IException, public IExceptionContext<ParameterInvalidException> {
		A_CHAR szParameterName[MAX_NAME];

	public:
		ParameterInvalidException(_In_z_ A_LPCSTR lpParameterName);
		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetParameterName() const noexcept;
	};

	class ErrnoException : public IException, public IExceptionContext<ParameterInvalidException> {
		errno_t nErrorCode;
		A_CHAR szErrnoString[MAX_MSG];

	public:
		ErrnoException(_In_ errno_t nErrorCode);
		constexpr _Check_return_ errno_t GetErrorCode() const noexcept;
		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetErrorMessage() const noexcept;
	};

	class IndexOutOfBoundsException : public IException, public IExceptionContext<IndexOutOfBoundsException> {
		A_I32 nIndex;
		A_I32 nMaxValidIndex;

	public:
		IndexOutOfBoundsException(_In_ A_I32 nIndex, _In_ A_I32 nHighestValidIndex);
		constexpr _Check_return_ A_I32 GetIndex() const noexcept;
		constexpr _Check_return_ A_I32 GetHighestValidIndex() const noexcept;
	};
}

#endif // !__AURORA_EXCEPTIONS_H__