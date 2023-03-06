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
#define AuroraContextStart() A_DWORD dwKey = Aurora::GlobalExceptionContext::SetContext(__FUNCSIG__)
// Ends the contextualized call. Should be called right before returning.
#define AuroraContextEnd() Aurora::GlobalExceptionContext::ResetContext(dwKey)
// Throws an exception inside of a contextualized call.
#define AuroraThrow(Exception, ...) throw Exception(__VA_ARGS__).WithContext(__FUNCSIG__, __FILE__, __LINE__)

#define MAX_CALL_TRACE 64

namespace Aurora {
	namespace Identifiers {
		AURORA_API extern const Identifier WindowsApiExceptionId;
		AURORA_API extern const Identifier ParameterInvalidExceptionId;
		AURORA_API extern const Identifier ErrnoExceptionId;
		AURORA_API extern const Identifier IndexOutOfBoundsExceptionId;
		AURORA_API extern const Identifier NotImplementedExceptionId;
		AURORA_API extern const Identifier PointerChainInvalidExceptionId;
		AURORA_API extern const Identifier Read32ExceptionId;
		AURORA_API extern const Identifier Read64ExceptionId;
		AURORA_API extern const Identifier Write32ExceptionId;
		AURORA_API extern const Identifier Write64ExceptionId;
		AURORA_API extern const Identifier ObjectNotFoundExceptionId;
	}

	typedef const A_CHAR(*FunctionsArray)[MAX_NAME];

	class AURORA_API GlobalExceptionContext {
	public:
		GlobalExceptionContext() = delete;
		GlobalExceptionContext(const GlobalExceptionContext&) = delete;

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

	typedef A_VOID(__cdecl* ThrowEventHandler)(_In_ IException* lpException, _In_opt_ A_LPVOID lpParameter);

	class AURORA_API NextThrowEventManager {
	public:
		NextThrowEventManager() = delete;
		NextThrowEventManager(const NextThrowEventManager&) = delete;

		static A_I32 QueueEvent(_In_ ThrowEventHandler lpfnHandler, _In_opt_ A_LPVOID lpParameter = nullptr);
		static A_VOID Invoke(_In_ IException* lpException);
		static A_VOID ClearEventQueue(_In_ A_I32 nIndex = INVALID_INDEX);
	};

	template<class Derived>
	class IExceptionContext {
		A_CHAR lpszFunctions[MAX_CALL_TRACE][MAX_NAME];
		A_CHAR szCoreFunction[MAX_NAME];
		A_CHAR szFilePath[MAX_PATH];
		A_I32 nFunctionCount;
		A_I32 nLine;

	public:
		inline IExceptionContext() : lpszFunctions(), szCoreFunction(), szFilePath(), nFunctionCount(0), nLine(0) {}

		inline Derived WithContext(_In_z_ A_LPCSTR lpFunction, _In_z_ A_LPCSTR lpFile, _In_ A_I32 nLine) {
			nFunctionCount = GlobalExceptionContext::GetContextCount();
			for (A_I32 i = 0; i < nFunctionCount; i++)
#pragma warning(push)
#pragma warning(disable:6011) // "Dereferencing NULL pointer 'GetContext()'." warning disabled due to 'GetContext()' not returning NULL as long as 'GetContextCount()' > 0.
				strcpy_s(lpszFunctions[i], GlobalExceptionContext::GetContext()[i]);
#pragma warning(pop)
			GlobalExceptionContext::ResetContext(GetCurrentThreadId());

			strcpy_s(szCoreFunction, lpFunction);
			strcpy_s(szFilePath, lpFile);
			this->nLine = nLine;

			NextThrowEventManager::Invoke((Derived*)this);

			return *(Derived*)this;
		}

		constexpr FunctionsArray GetFunctions() const { return lpszFunctions; }
		constexpr _Check_return_ A_I32 GetFunctionCount() const { return nFunctionCount; }
		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetCoreFunction() const { return szCoreFunction; }
		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetFile() const { return szFilePath; }
		constexpr _Check_return_ A_I32 GetLine() const { return nLine; }
	};

	class AURORA_API WindowsApiException : public IException, public IExceptionContext<WindowsApiException> {
		A_DWORD dwWindowsApiCode;
		A_CHAR szWindowsApiMessage[MAX_MSG];
		A_CHAR szWindowsApiFunction[MAX_NAME];

	public:
		WindowsApiException(_In_z_ A_LPCSTR lpWindowsApiFunction);
		constexpr _Check_return_ A_DWORD GetWindowsCode() const noexcept;
		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetWindowsMessage() const noexcept;
		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetWindowsFunction() const noexcept;
	};

	class AURORA_API ParameterInvalidException : public IException, public IExceptionContext<ParameterInvalidException> {
		A_CHAR szParameterName[MAX_NAME];

	public:
		ParameterInvalidException(_In_z_ A_LPCSTR lpParameterName);
		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetParameterName() const noexcept;
	};

	class AURORA_API ErrnoException : public IException, public IExceptionContext<ParameterInvalidException> {
		errno_t nErrorCode;
		A_CHAR szErrnoString[MAX_MSG];

	public:
		ErrnoException(_In_ errno_t nErrorCode);
		constexpr _Check_return_ errno_t GetErrorCode() const noexcept;
		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetErrorMessage() const noexcept;
	};

	class AURORA_API IndexOutOfBoundsException : public IException, public IExceptionContext<IndexOutOfBoundsException> {
		A_I32 nIndex;
		A_I32 nMaxValidIndex;

	public:
		IndexOutOfBoundsException(_In_ A_I32 nIndex, _In_ A_I32 nHighestValidIndex);
		constexpr _Check_return_ A_I32 GetIndex() const noexcept;
		constexpr _Check_return_ A_I32 GetHighestValidIndex() const noexcept;
	};

	class AURORA_API NotImplementedException : public IException, public IExceptionContext<NotImplementedException> { public: NotImplementedException(); };

	class AURORA_API PointerChainInvalidException : public IException, public IExceptionContext<PointerChainInvalidException> {
		A_I32 nChainLevel;

	public:
		PointerChainInvalidException(_In_ A_I32 nChainLevel);

		constexpr A_I32 GetChainLevel() const noexcept;
	};

	template<typename AddressType>
	class AURORA_API IMemoryExceptionBase : public IException, public IExceptionContext<IMemoryExceptionBase<AddressType>> {
		AddressType uAddress;
		A_DWORD dwSize;

	public:
		IMemoryExceptionBase(_In_z_ A_LPCSTR lpMessage, const Identifier& Id, _In_ AddressType uAddress, _In_ A_DWORD dwSize) : IException(lpMessage, Id), uAddress(uAddress), dwSize(dwSize) {}

		constexpr AddressType GetAddress() const noexcept { return uAddress; }
		constexpr A_DWORD GetSize() const noexcept { return dwSize; }
	};

	class AURORA_API Read32Exception : public IMemoryExceptionBase<A_ADDR32> { public: Read32Exception(_In_ A_ADDR32 uAddress, _In_ A_DWORD dwSize); };
	class AURORA_API Read64Exception : public IMemoryExceptionBase<A_ADDR64> { public: Read64Exception(_In_ A_ADDR64 uAddress, _In_ A_DWORD dwSize); };
	class AURORA_API Write32Exception : public IMemoryExceptionBase<A_ADDR32> { public: Write32Exception(_In_ A_ADDR32 uAddress, _In_ A_DWORD dwSize); };
	class AURORA_API Write64Exception : public IMemoryExceptionBase<A_ADDR64> { public: Write64Exception(_In_ A_ADDR64 uAddress, _In_ A_DWORD dwSize); };

#ifdef _WIN64
	using ReadException = Read64Exception;
	using WriteException = Write64Exception;
#else
	using ReadException = Read32Exception;
	using WriteException = Write32Exception;
#endif

	class AURORA_API ObjectNotFoundException : public IException, public IExceptionContext<ObjectNotFoundException> {
		A_CHAR szObjectType[MAX_NAME];
		A_CHAR szObjectName[MAX_NAME];

	public:
		ObjectNotFoundException(_In_z_ A_LPCSTR lpObjectType, _In_z_ A_LPCSTR lpObjectName);

		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetObjectType() const noexcept;
		constexpr _Check_return_ _Ret_z_ A_LPCSTR GetObjectName() const noexcept;
	};
}

#endif // !__AURORA_EXCEPTIONS_H__