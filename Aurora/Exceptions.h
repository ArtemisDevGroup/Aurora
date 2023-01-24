#ifndef __AURORA_EXCEPTIONS_H__
#define __AURORA_EXCEPTIONS_H__

#include "Definitions.h"

#define AuroraContextStart() DWORD dwKey = Aurora::GlobalExceptionContext::SetContext(__FUNCTION__)
#define AuroraContextEnd() Aurora::GlobalExceptionContext::ResetContext(dwKey)

namespace Aurora {
	class AURORA_API GlobalExceptionContext {
	public:
		GlobalExceptionContext() = delete;
		GlobalExceptionContext(const GlobalExceptionContext&) = delete;
		~GlobalExceptionContext() = delete;

		static DWORD SetContext(_In_z_ LPCSTR lpFunctionName);
		static void ResetContext(_In_ DWORD dwKey);
	};

	class AURORA_API IException {
		CHAR szMessage[MAX_MSG];
		DWORD dwIdentifier;

	public:

	};

	template<class Derived>
	class AURORA_API IExceptionContext {
		CHAR szFile[MAX_PATH];
		CHAR szFunction[MAX_NAME];
		INT nLine;

	public:
		Derived WithContext(_In_z_ LPCSTR lpFunction, _In_z_ LPCSTR lpFile, _In_ INT nLine) {
			strcpy_s(szFunction, lpFunction);
			strcpy_s(szFile, lpFile);
			this->nLine = nLine;

			return *(Derived*)this;
		}

		constexpr LPCSTR GetFunction() const { return szFunction; }
		constexpr LPCSTR GetFile() const { return szFile; }
		constexpr INT GetLine() const { return nLine; }
	};
}

#endif // !__AURORA_EXCEPTIONS_H__