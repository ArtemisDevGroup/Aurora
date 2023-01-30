#include "String.h"

#include <stdio.h>
#include <string.h>

namespace Aurora {
	String::String() : lpString(nullptr), dwLength(0) {}

	String::String(_In_z_ A_LPCSTR lpString) {
		dwLength = strlen(lpString);
		this->lpString = new A_CHAR[dwLength + 1];
		strcpy_s(this->lpString, dwLength + 1, lpString);
	}

	A_VOID String::Clone(_Out_ A_LPVOID lpDestination) const {
		String* pDst = (String*)lpDestination;
		pDst->dwLength = dwLength;
		pDst->lpString = new A_CHAR[dwLength + 1];
		strcpy_s(pDst->lpString, dwLength + 1, lpString);
	}

	String::String(const String& cpy) { cpy.Clone(this); }

	A_VOID String::Release() {
		if (lpString) {
			delete[] lpString;
			dwLength = 0;
			lpString = nullptr;
		}
	}

	String::~String() { Release(); }

	A_VOID String::Add(_In_ const String& str, _In_ A_I32 nIndex = -1) { Add(str.lpString, nIndex); }

	A_VOID String::Add(_In_ A_I8 nElement, _In_ A_I32 nIndex = -1) {
		A_CHAR szString[64];
		sprintf_s(szString, "%hhi", nElement);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_I16 nElement, _In_ A_I32 nIndex = -1) {
		A_CHAR szString[64];
		sprintf_s(szString, "%hi", nElement);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_I32 nElement, _In_ A_I32 nIndex = -1) {
		A_CHAR szString[64];
		sprintf_s(szString, "%i", nElement);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_I64 nElement, _In_ A_I32 nIndex = -1) {
		A_CHAR szString[64];
		sprintf_s(szString, "%lli", nElement);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_U8 uElement, _In_ A_I32 nIndex = -1) {
		A_CHAR szString[64];
		sprintf_s(szString, "%hhu", uElement);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_U16 uElement, _In_ A_I32 nIndex = -1) {
		A_CHAR szString[64];
		sprintf_s(szString, "%hu", uElement);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_U32 uElement, _In_ A_I32 nIndex = -1) {
		A_CHAR szString[64];
		sprintf_s(szString, "%u", uElement);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_U64 uElement, _In_ A_I32 nIndex = -1) {
		A_CHAR szString[64];
		sprintf_s(szString, "%llu", uElement);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_FL32 fElement, _In_ A_I32 nIndex = -1) {
		A_CHAR szString[64];
		sprintf_s(szString, "%f", fElement);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_FL64 fElement, _In_ A_I32 nIndex = -1) {
		A_CHAR szString[64];
		sprintf_s(szString, "%f", fElement);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_BOOL bElement, _In_ A_I32 nIndex = -1) {
		A_CHAR szString[64];
		sprintf_s(szString, "%s", bElement ? "true" : "false");
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_LPVOID lpPointer, _In_ A_I32 nIndex = -1) {
		A_CHAR szString[64];
		sprintf_s(szString, "%p", lpPointer);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_z_ A_LPCSTR lpString, _In_ A_I32 nIndex = -1) {
		if (nIndex >= dwLength) /* throw */;

		A_DWORD dwStrlen = strlen(lpString);
		A_DWORD dwNewLength = this->dwLength + dwStrlen;
		A_LPSTR lpOld = this->lpString;
		this->lpString = new A_CHAR[dwNewLength + 1];

		if (nIndex == -1) {
			strcpy_s(this->lpString, dwNewLength + 1, lpOld);
			strcat_s(this->lpString, dwNewLength + 1, lpString);
		}
		else {
			for (int i = 0; i < nIndex; i++)
				this->lpString[i] = lpOld[i];
			for (int i = 0; i < dwStrlen; i++)
				this->lpString[nIndex + i] = lpString[i];
			for (int i = 0; i < dwNewLength - (nIndex + dwStrlen); i++)
				this->lpString[nIndex + dwStrlen + i] = lpOld[nIndex + i];
			this->lpString[dwNewLength] = '\0';
		}

		delete[] lpOld;
		dwLength = dwNewLength;
	}
}