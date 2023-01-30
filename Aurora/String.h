#ifndef __AURORA_STRING_H__
#define __AURORA_STRING_H__

#include "Definitions.h"
#include "Interfaces.h"
#include "Array.h"

namespace Aurora {
	class AURORA_API String : public IDisposable {
		A_LPSTR lpString;
		A_DWORD dwLength;

	public:
		String();
		String(_In_z_ A_LPCSTR lpString);

		virtual A_VOID IDisposable::Clone(_Out_ A_LPVOID lpDestination) const;

		String(const String& cpy);

		virtual A_VOID IDisposable::Release();

		~String();

		/// <summary>
		/// Inserts the string at the index provided.
		/// </summary>
		/// <param name="str"></param>
		/// <param name="nIndex"></param>
		A_VOID Add(_In_ const String& str, _In_ A_I32 nIndex = -1);

		A_VOID Add(_In_ A_I8 nElement, _In_ A_I32 nIndex = -1);
		A_VOID Add(_In_ A_I16 nElement, _In_ A_I32 nIndex = -1);
		A_VOID Add(_In_ A_I32 nElement, _In_ A_I32 nIndex = -1);
		A_VOID Add(_In_ A_I64 nElement, _In_ A_I32 nIndex = -1);

		A_VOID Add(_In_ A_U8 uElement, _In_ A_I32 nIndex = -1);
		A_VOID Add(_In_ A_U16 uElement, _In_ A_I32 nIndex = -1);
		A_VOID Add(_In_ A_U32 uElement, _In_ A_I32 nIndex = -1);
		A_VOID Add(_In_ A_U64 uElement, _In_ A_I32 nIndex = -1);

		A_VOID Add(_In_ A_FL32 fElement, _In_ A_I32 nIndex = -1);
		A_VOID Add(_In_ A_FL64 fElement, _In_ A_I32 nIndex = -1);

		A_VOID Add(_In_ A_BOOL bElement, _In_ A_I32 nIndex = -1);
		A_VOID Add(_In_ A_LPVOID lpPointer, _In_ A_I32 nIndex = -1);
		A_VOID Add(_In_z_ A_LPCSTR lpString, _In_ A_I32 nIndex = -1);

		A_VOID Remove(_In_ A_I32 nCount = 1, _In_ A_I32 nIndex = -1);

		A_I32 FindFirst(_In_ const String& str);

		A_I32 FindFirst(_In_ A_I8 nElement);
		A_I32 FindFirst(_In_ A_I16 nElement);
		A_I32 FindFirst(_In_ A_I32 nElement);
		A_I32 FindFirst(_In_ A_I64 nElement);

		A_I32 FindFirst(_In_ A_U8 uElement);
		A_I32 FindFirst(_In_ A_U16 uElement);
		A_I32 FindFirst(_In_ A_U32 uElement);
		A_I32 FindFirst(_In_ A_U64 uElement);

		A_I32 FindFirst(_In_ A_FL32 fElement);
		A_I32 FindFirst(_In_ A_FL64 fElement);

		A_I32 FindFirst(_In_ A_BOOL bElement);
		A_I32 FindFirst(_In_ A_LPVOID lpPointer);
		A_I32 FindFirst(_In_z_ A_LPCSTR lpString);

		List<A_I32> Find(_In_ const String& str);

		List<A_I32> Find(_In_ A_I8 nElement);
		List<A_I32> Find(_In_ A_I16 nElement);
		List<A_I32> Find(_In_ A_I32 nElement);
		List<A_I32> Find(_In_ A_I64 nElement);

		List<A_I32> Find(_In_ A_U8 uElement);
		List<A_I32> Find(_In_ A_U16 uElement);
		List<A_I32> Find(_In_ A_U32 uElement);
		List<A_I32> Find(_In_ A_U64 uElement);

		List<A_I32> Find(_In_ A_FL32 fElement);
		List<A_I32> Find(_In_ A_FL64 fElement);

		List<A_I32> Find(_In_ A_BOOL bElement);
		List<A_I32> Find(_In_ A_LPVOID lpPointer);
		List<A_I32> Find(_In_z_ A_LPCSTR lpString);

		constexpr operator A_LPCSTR() const { return lpString; }

		constexpr A_LPCSTR cstr() const { return lpString; }
		constexpr A_DWORD size() const { return dwLength; }
	};
}

#endif // !__AURORA_STRING_H__