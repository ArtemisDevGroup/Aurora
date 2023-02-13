#ifndef __AURORA_EXCEPTIONS_H__
#define __AURORA_EXCEPTIONS_H__

#include "Definitions.h"
#include "Identification.h"
#include "String.h"

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

namespace Aurora {
	namespace Identifiers {
		AURORA_API extern const Identifier WindowsApiExceptionId;
		AURORA_API extern const Identifier ParameterInvalidExceptionId;
		AURORA_API extern const Identifier ErrnoExceptionId;
	}

	class AURORA_API GlobalExceptionContext {
	public:
		GlobalExceptionContext() = delete;
		GlobalExceptionContext(const GlobalExceptionContext&) = delete;
		~GlobalExceptionContext() = delete;

		static A_DWORD SetContext(_In_ const String& Context);
		static const List<String>& GetContext();
		static A_VOID ResetContext(_In_ A_DWORD dwKey);
	};

	class AURORA_API IException {
		String Message;
		Identifier Id;

	public:
		IException(_In_ const String& Message, _In_ const Identifier& Id);

		constexpr const String& GetMessage() const;
		constexpr const Identifier& GetIdentifier() const;

		A_BOOL operator==(const IException&) const;
		constexpr A_BOOL operator==(const Identifier&) const;
		A_BOOL operator==(const String&) const;

		A_BOOL operator!=(const IException&) const;
		constexpr A_BOOL operator!=(const Identifier&) const;
		A_BOOL operator!=(const String&) const;
	};

	template<class Derived>
	class AURORA_API IExceptionContext {
		List<String> Functions;
		String CoreFunction;
		String FilePath;
		A_I32 nLine;

	public:
		inline IExceptionContext() : Functions(), CoreFunction(), FilePath(), nLine(0) {}

		inline Derived WithContext(_In_ const String& Function, _In_ const String& File, _In_ A_I32 nLine) {
			this->Functions = GlobalExceptionContext::GetContext();
			GlobalExceptionContext::ResetContext(GetCurrentThreadId());

			this->CoreFunction = Function;
			this->FilePath = File;
			this->nLine = nLine;
			return *(Derived*)this;
		}

		constexpr const List<String>& GetFunctions() const { return Functions; }
		constexpr const String& GetCoreFunction() const { return CoreFunction; }
		constexpr const String& GetFile() const { return FilePath; }
		constexpr A_I32 GetLine() const { return nLine; }
	};

	class WindowsApiException : public IException, public IExceptionContext<WindowsApiException> {
		A_DWORD dwWindowsApiCode;
		String WindowsApiMessage;
		String WindowsApiFunction;

	public:
		WindowsApiException(_In_ const String& WindowsApiFunction);
		constexpr A_DWORD GetWindowsCode() const;
		constexpr const String& GetWindowsMessage() const;
		constexpr const String& GetWindowsFunction() const;
	};

	class ParameterInvalidException : public IException, public IExceptionContext<ParameterInvalidException> {
		String ParameterName;

	public:
		ParameterInvalidException(_In_ const String& ParameterName);
		constexpr const String& GetParameterName() const;
	};

	class ErrnoException : public IException, public IExceptionContext<ParameterInvalidException> {
		errno_t nErrorCode;
		A_CHAR szErrnoString[MAX_MSG];

	public:
		ErrnoException(_In_ errno_t nErrorCode);
		constexpr errno_t GetErrorCode() const;
		constexpr A_LPCSTR GetErrorMessage() const;
	};
}

#endif // !__AURORA_EXCEPTIONS_H__