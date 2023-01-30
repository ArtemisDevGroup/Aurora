#ifndef __AURORA_EXCEPTIONS_H__
#define __AURORA_EXCEPTIONS_H__

#include "Definitions.h"
#include "Identification.h"
#include "String.h"

#include <string.h>

#define AuroraContextStart() A_DWORD dwKey = Aurora::GlobalExceptionContext::SetContext(__FUNCTION__)
#define AuroraContextEnd() Aurora::GlobalExceptionContext::ResetContext(dwKey)

namespace Aurora {
	class AURORA_API GlobalExceptionContext {
	public:
		GlobalExceptionContext() = delete;
		GlobalExceptionContext(const GlobalExceptionContext&) = delete;
		~GlobalExceptionContext() = delete;

		static A_DWORD SetContext(_In_ const String& Context);
		static A_VOID ResetContext(_In_ A_DWORD dwKey);
	};

	class AURORA_API IException {
		String Message;
		Identifier Id;

	public:
		IException(_In_ const String& Message, _In_ const Identifier& Id);

		constexpr const String& GetMessage() const;
	};

	template<class Derived>
	class AURORA_API IExceptionContext {
		A_CHAR szFile[MAX_PATH];
		A_CHAR szFunction[MAX_NAME];
		A_I32 nLine;

	public:
		Derived WithContext(_In_z_ A_LPCSTR lpFunction, _In_z_ A_LPCSTR lpFile, _In_ A_I32 nLine) {
			strcpy_s(szFunction, lpFunction);
			strcpy_s(szFile, lpFile);
			this->nLine = nLine;

			return *(Derived*)this;
		}

		constexpr A_LPCSTR GetFunction() const { return szFunction; }
		constexpr A_LPCSTR GetFile() const { return szFile; }
		constexpr A_I32 GetLine() const { return nLine; }
	};
}

#endif // !__AURORA_EXCEPTIONS_H__