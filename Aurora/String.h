#ifndef __AURORA_STRING_H__
#define __AURORA_STRING_H__

#include "Definitions.h"
#include "Interfaces.h"
#include "Array.h"

namespace Aurora {
	class AURORA_API String : public IDisposable {
		LPSTR lpString;
		DWORD dwLength;

	public:
		String();
		String(_In_z_ LPCSTR lpString);

		virtual void IDisposable::Clone(_Out_ void* pDestination) const;

		String(const String& cpy);

		virtual void IDisposable::Release();

		~String();

		/// <summary>
		/// Inserts the string at the index provided.
		/// </summary>
		/// <param name="str"></param>
		/// <param name="nIndex"></param>
		void Add(_In_ const String& str, _In_ INT nIndex = -1);

		void Add(_In_ CHAR cElement, _In_ INT nIndex = -1);
		void Add(_In_ SHORT nElement, _In_ INT nIndex = -1);
		void Add(_In_ INT nElement, _In_ INT nIndex = -1);
		void Add(_In_ LONG nElement, _In_ INT nIndex = -1);
		void Add(_In_ LONGLONG nElement, _In_ INT nIndex = -1);

		void Add(_In_ BYTE uElement, _In_ INT nIndex = -1);
		void Add(_In_ USHORT uElement, _In_ INT nIndex = -1);
		void Add(_In_ UINT uElement, _In_ INT nIndex = -1);
		void Add(_In_ ULONG uElement, _In_ INT nIndex = -1);
		void Add(_In_ ULONGLONG uElement, _In_ INT nIndex = -1);

		void Add(_In_ float fElement, _In_ INT nIndex = -1);
		void Add(_In_ double dElement, _In_ INT nIndex = -1);

		void Add(_In_ bool bElement, _In_ INT nIndex = -1);
		void Add(_In_ LPVOID lpPointer, _In_ INT nIndex = -1);
		void Add(_In_z_ LPCSTR lpString, _In_ INT nIndex = -1);

		void Remove(_In_ INT nCount = 1, _In_ INT nIndex = -1);

		INT FindFirst(_In_ const String& str);

		INT FindFirst(_In_ CHAR chElement);
		INT FindFirst(_In_ SHORT nElement);
		INT FindFirst(_In_ INT nElement);
		INT FindFirst(_In_ LONG nElement);
		INT FindFirst(_In_ LONGLONG nElement);

		INT FindFirst(_In_ BYTE uElement);
		INT FindFirst(_In_ USHORT uElement);
		INT FindFirst(_In_ UINT uElement);
		INT FindFirst(_In_ ULONG uElement);
		INT FindFirst(_In_ ULONGLONG uElement);

		INT FindFirst(_In_ float fElement);
		INT FindFirst(_In_ double dElement);

		INT FindFirst(_In_ bool bElement);
		INT FindFirst(_In_ LPVOID lpPointer);
		INT FindFirst(_In_z_ LPCSTR lpString);

		List<INT> Find(_In_ const String& str);

		List<INT> Find(_In_ CHAR chElement);
		List<INT> Find(_In_ SHORT nElement);
		List<INT> Find(_In_ INT nElement);
		List<INT> Find(_In_ LONG nElement);
		List<INT> Find(_In_ LONGLONG nElement);

		List<INT> Find(_In_ BYTE uElement);
		List<INT> Find(_In_ USHORT uElement);
		List<INT> Find(_In_ UINT uElement);
		List<INT> Find(_In_ ULONG uElement);
		List<INT> Find(_In_ ULONGLONG uElement);

		List<INT> Find(_In_ float fElement);
		List<INT> Find(_In_ double dElement);

		List<INT> Find(_In_ bool bElement);
		List<INT> Find(_In_ LPVOID lpPointer);
		List<INT> Find(_In_z_ LPCSTR lpString);
	};

	class AURORA_API WString {
		LPWSTR lpString;
		DWORD dwLength;

	public:
	};
}

#endif // !__AURORA_STRING_H__