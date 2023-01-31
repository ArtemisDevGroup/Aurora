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

		A_I32 FindFirst(_In_ const String& str) const;

		A_I32 FindFirst(_In_ A_I8 nElement) const;
		A_I32 FindFirst(_In_ A_I16 nElement) const;
		A_I32 FindFirst(_In_ A_I32 nElement) const;
		A_I32 FindFirst(_In_ A_I64 nElement) const;

		A_I32 FindFirst(_In_ A_U8 uElement) const;
		A_I32 FindFirst(_In_ A_U16 uElement) const;
		A_I32 FindFirst(_In_ A_U32 uElement) const;
		A_I32 FindFirst(_In_ A_U64 uElement) const;

		A_I32 FindFirst(_In_ A_FL32 fElement) const;
		A_I32 FindFirst(_In_ A_FL64 fElement) const;

		A_I32 FindFirst(_In_ A_BOOL bElement) const;
		A_I32 FindFirst(_In_ A_LPVOID lpPointer) const;
		A_I32 FindFirst(_In_z_ A_LPCSTR lpString) const;

		List<A_I32> Find(_In_ const String& str) const;

		List<A_I32> Find(_In_ A_I8 nElement) const;
		List<A_I32> Find(_In_ A_I16 nElement) const;
		List<A_I32> Find(_In_ A_I32 nElement) const;
		List<A_I32> Find(_In_ A_I64 nElement) const;

		List<A_I32> Find(_In_ A_U8 uElement) const;
		List<A_I32> Find(_In_ A_U16 uElement) const;
		List<A_I32> Find(_In_ A_U32 uElement) const;
		List<A_I32> Find(_In_ A_U64 uElement) const;

		List<A_I32> Find(_In_ A_FL32 fElement) const;
		List<A_I32> Find(_In_ A_FL64 fElement) const;

		List<A_I32> Find(_In_ A_BOOL bElement) const;
		List<A_I32> Find(_In_ A_LPVOID lpPointer) const;
		List<A_I32> Find(_In_z_ A_LPCSTR lpString) const;

		constexpr operator A_LPCSTR() const;

		constexpr A_LPCSTR cstr() const;
		constexpr A_DWORD size() const { return dwLength; }

		constexpr A_BOOL operator==(const String&) const;
		constexpr A_BOOL operator!=(const String&) const;
		constexpr String operator+(const String&) const;
		constexpr A_VOID operator+=(const String&);
	};
}

#endif // !__AURORA_STRING_H__