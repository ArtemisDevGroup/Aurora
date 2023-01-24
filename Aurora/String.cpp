#include "String.h"

namespace Aurora {
	String::String() : lpString(nullptr), dwLength(0) {}

	String::String(_In_z_ LPCSTR lpString) {
		dwLength = strlen(lpString);
		this->lpString = new CHAR[dwLength + 1];
		strcpy_s(this->lpString, dwLength + 1, lpString);
	}

	void String::Clone(void* pDestination) const {
		String* pDst = (String*)pDestination;
		pDst->dwLength = dwLength;
		pDst->lpString = new CHAR[dwLength + 1];
		strcpy_s(pDst->lpString, dwLength + 1, lpString);
	}

	String::String(const String& cpy) { cpy.Clone(this); }

	void String::Release() {
		if (lpString) {
			delete[] lpString;
			dwLength = 0;
			lpString = nullptr;
		}
	}

	String::~String() { Release(); }

	void String::Add(_In_ const String& str, _In_ INT nIndex = -1) { Add(str.lpString, nIndex); }



	void String::Add(_In_z_ LPCSTR lpString, _In_ INT nIndex = -1) {
		if (nIndex >= dwLength) /* throw */;

		DWORD dwStrlen = strlen(lpString);
		DWORD dwNewLength = this->dwLength + dwStrlen;
		LPSTR lpOld = this->lpString;
		this->lpString = new CHAR[dwNewLength + 1];

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