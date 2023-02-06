#ifndef __AURORA_EXCEPTIONS_H__
#define __AURORA_EXCEPTIONS_H__

#include "Definitions.h"
#include "Identification.h"
#include "String.h"

#include <string.h>

// Sets the context of all thrown exceptions to report the current function as the origin of the call.
#define AuroraContextStart() A_DWORD dwKey = Aurora::GlobalExceptionContext::SetContext(__FUNCTION__)
#define AuroraContextEnd() Aurora::GlobalExceptionContext::ResetContext(dwKey)

namespace Aurora {
	class AURORA_API GlobalExceptionContext {
	public:
		GlobalExceptionContext() = delete;
		GlobalExceptionContext(const GlobalExceptionContext&) = delete;
		~GlobalExceptionContext() = delete;

		static A_DWORD SetContext(_In_ const String& Context);
		static String GetContext();
		static A_DWORD GetContextKey();
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
		String Function;
		String CoreFunction;
		String FilePath;
		A_I32 nLine;

	public:
		Derived WithContext(_In_ const String& Function, _In_ const String& File, _In_ A_I32 nLine) { 
			this->Function = GlobalExceptionContext::GetContext();
			GlobalExceptionContext::ResetContext(GlobalExceptionContext::GetContextKey());

			this->CoreFunction = Function;
			this->FilePath = File;
			this->nLine = nLine;
			return *(Derived*)this;
		}

		constexpr const String& GetFunction() const { return Function; }
		constexpr const String& GetCoreFunction() const { return CoreFunction; }
		constexpr const String& GetFile() const { return FilePath; }
		constexpr A_I32 GetLine() const { return nLine; }
	};
}

#endif // !__AURORA_EXCEPTIONS_H__