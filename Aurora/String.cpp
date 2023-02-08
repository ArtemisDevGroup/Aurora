#include "String.h"
#include "Binary.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

namespace Aurora {
	String::String() : lpString(nullptr), dwLength(0) {}

	String::String(_In_z_ A_LPCSTR lpString) {
		dwLength = strlen(lpString);
		this->lpString = new A_CHAR[dwLength + 1];
		strcpy_s(this->lpString, dwLength + 1, lpString);
	}

	A_VOID String::Clone(_Out_ A_LPVOID lpDestination) const {
		String* pDst = (String*)lpDestination;

		if (lpString) {
			pDst->dwLength = dwLength;
			pDst->lpString = new A_CHAR[dwLength + 1];
			strcpy_s(pDst->lpString, dwLength + 1, lpString);
		}
		else {
			pDst->dwLength = 0;
			pDst->lpString = nullptr;
		}
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

	A_VOID String::Add(_In_ const String& str, _In_ A_I32 nIndex) { Add(str.lpString, nIndex); }

	A_VOID String::Add(_In_ A_I8 nElement, _In_ A_I32 nIndex, _In_ IntegralRepresentationFlags nFlags) {
		Binary<decltype(nElement)> bin = nElement;
		A_CHAR szString[bin.BufferBitCount + 1];

		if (nFlags == IntegralRepresentationFlags::Binary) {
			for (A_I32 i = 0; i < bin.BufferBitCount; i++)
				szString[i] = bin.CheckBit(i) ? '1' : '0';

			szString[bin.BufferBitCount] = '\0';
		}
		else {
			A_CHAR szFormat[5] = { '%', 'h', 'h', 0, '\0'};

			switch (nFlags) {
			case IntegralRepresentationFlags::Octal:
				szFormat[sizeof(szFormat) - 2] = 'o';
				break;
			case IntegralRepresentationFlags::Decimal:
				szFormat[sizeof(szFormat) - 2] = 'i';
				break;
			case IntegralRepresentationFlags::Hexadecimal:
				szFormat[sizeof(szFormat) - 2] = 'X';
				break;
			default:
				/* throw */
				break;
			}

			sprintf_s(szString, szFormat, nElement);
		}

		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_I16 nElement, _In_ A_I32 nIndex, _In_ IntegralRepresentationFlags nFlags) {
		Binary<decltype(nElement)> bin = nElement;
		A_CHAR szString[bin.BufferBitCount + 1];

		if (nFlags == IntegralRepresentationFlags::Binary) {
			for (A_I32 i = 0; i < bin.BufferBitCount; i++)
				szString[i] = bin.CheckBit(i) ? '1' : '0';

			szString[bin.BufferBitCount] = '\0';
		}
		else {
			A_CHAR szFormat[4] = { '%', 'h', 0, '\0'};

			switch (nFlags) {
			case IntegralRepresentationFlags::Octal:
				szFormat[sizeof(szFormat) - 2] = 'o';
				break;
			case IntegralRepresentationFlags::Decimal:
				szFormat[sizeof(szFormat) - 2] = 'i';
				break;
			case IntegralRepresentationFlags::Hexadecimal:
				szFormat[sizeof(szFormat) - 2] = 'X';
				break;
			default:
				/* throw */
				break;
			}

			sprintf_s(szString, szFormat, nElement);
		}

		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_I32 nElement, _In_ A_I32 nIndex, _In_ IntegralRepresentationFlags nFlags) {
		Binary<decltype(nElement)> bin = nElement;
		A_CHAR szString[bin.BufferBitCount + 1];

		if (nFlags == IntegralRepresentationFlags::Binary) {
			for (A_I32 i = 0; i < bin.BufferBitCount; i++)
				szString[i] = bin.CheckBit(i) ? '1' : '0';

			szString[bin.BufferBitCount] = '\0';
		}
		else {
			A_CHAR szFormat[3] = { '%', 0, '\0' };

			switch (nFlags) {
			case IntegralRepresentationFlags::Octal:
				szFormat[sizeof(szFormat) - 2] = 'o';
				break;
			case IntegralRepresentationFlags::Decimal:
				szFormat[sizeof(szFormat) - 2] = 'i';
				break;
			case IntegralRepresentationFlags::Hexadecimal:
				szFormat[sizeof(szFormat) - 2] = 'X';
				break;
			default:
				/* throw */
				break;
			}

			sprintf_s(szString, szFormat, nElement);
		}

		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_I64 nElement, _In_ A_I32 nIndex, _In_ IntegralRepresentationFlags nFlags) {
		Binary<decltype(nElement)> bin = nElement;
		A_CHAR szString[bin.BufferBitCount + 1];

		if (nFlags == IntegralRepresentationFlags::Binary) {
			for (A_I32 i = 0; i < bin.BufferBitCount; i++)
				szString[i] = bin.CheckBit(i) ? '1' : '0';

			szString[bin.BufferBitCount] = '\0';
		}
		else {
			A_CHAR szFormat[5] = { '%', 'l', 'l', 0, '\0'};

			switch (nFlags) {
			case IntegralRepresentationFlags::Octal:
				szFormat[sizeof(szFormat) - 2] = 'o';
				break;
			case IntegralRepresentationFlags::Decimal:
				szFormat[sizeof(szFormat) - 2] = 'i';
				break;
			case IntegralRepresentationFlags::Hexadecimal:
				szFormat[sizeof(szFormat) - 2] = 'X';
				break;
			default:
				/* throw */
				break;
			}

			sprintf_s(szString, szFormat, nElement);
		}

		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_U8 uElement, _In_ A_I32 nIndex, _In_ IntegralRepresentationFlags nFlags) {
		Binary<decltype(uElement)> bin = uElement;
		A_CHAR szString[bin.BufferBitCount + 1];

		if (nFlags == IntegralRepresentationFlags::Binary) {
			for (A_I32 i = 0; i < bin.BufferBitCount; i++)
				szString[i] = bin.CheckBit(i) ? '1' : '0';

			szString[bin.BufferBitCount] = '\0';
		}
		else {
			A_CHAR szFormat[5] = { '%', 'h', 'h', 0, '\0' };

			switch (nFlags) {
			case IntegralRepresentationFlags::Octal:
				szFormat[sizeof(szFormat) - 2] = 'o';
				break;
			case IntegralRepresentationFlags::Decimal:
				szFormat[sizeof(szFormat) - 2] = 'u';
				break;
			case IntegralRepresentationFlags::Hexadecimal:
				szFormat[sizeof(szFormat) - 2] = 'X';
				break;
			default:
				/* throw */
				break;
			}

			sprintf_s(szString, szFormat, uElement);
		}

		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_U16 uElement, _In_ A_I32 nIndex, _In_ IntegralRepresentationFlags nFlags) {
		Binary<decltype(uElement)> bin = uElement;
		A_CHAR szString[bin.BufferBitCount + 1];

		if (nFlags == IntegralRepresentationFlags::Binary) {
			for (A_I32 i = 0; i < bin.BufferBitCount; i++)
				szString[i] = bin.CheckBit(i) ? '1' : '0';

			szString[bin.BufferBitCount] = '\0';
		}
		else {
			A_CHAR szFormat[4] = { '%', 'h', 0, '\0' };

			switch (nFlags) {
			case IntegralRepresentationFlags::Octal:
				szFormat[sizeof(szFormat) - 2] = 'o';
				break;
			case IntegralRepresentationFlags::Decimal:
				szFormat[sizeof(szFormat) - 2] = 'u';
				break;
			case IntegralRepresentationFlags::Hexadecimal:
				szFormat[sizeof(szFormat) - 2] = 'X';
				break;
			default:
				/* throw */
				break;
			}

			sprintf_s(szString, szFormat, uElement);
		}

		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_U32 uElement, _In_ A_I32 nIndex, _In_ IntegralRepresentationFlags nFlags) {
		Binary<decltype(uElement)> bin = uElement;
		A_CHAR szString[bin.BufferBitCount + 1];

		if (nFlags == IntegralRepresentationFlags::Binary) {
			for (A_I32 i = 0; i < bin.BufferBitCount; i++)
				szString[i] = bin.CheckBit(i) ? '1' : '0';

			szString[bin.BufferBitCount] = '\0';
		}
		else {
			A_CHAR szFormat[3] = { '%', 0, '\0' };

			switch (nFlags) {
			case IntegralRepresentationFlags::Octal:
				szFormat[sizeof(szFormat) - 2] = 'o';
				break;
			case IntegralRepresentationFlags::Decimal:
				szFormat[sizeof(szFormat) - 2] = 'u';
				break;
			case IntegralRepresentationFlags::Hexadecimal:
				szFormat[sizeof(szFormat) - 2] = 'X';
				break;
			default:
				/* throw */
				break;
			}

			sprintf_s(szString, szFormat, uElement);
		}

		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_U64 uElement, _In_ A_I32 nIndex, _In_ IntegralRepresentationFlags nFlags) {
		Binary<decltype(uElement)> bin = uElement;
		A_CHAR szString[bin.BufferBitCount + 1];

		if (nFlags == IntegralRepresentationFlags::Binary) {
			for (A_I32 i = 0; i < bin.BufferBitCount; i++)
				szString[i] = bin.CheckBit(i) ? '1' : '0';

			szString[bin.BufferBitCount] = '\0';
		}
		else {
			A_CHAR szFormat[5] = { '%', 'l', 'l', 0, '\0' };

			switch (nFlags) {
			case IntegralRepresentationFlags::Octal:
				szFormat[sizeof(szFormat) - 2] = 'o';
				break;
			case IntegralRepresentationFlags::Decimal:
				szFormat[sizeof(szFormat) - 2] = 'u';
				break;
			case IntegralRepresentationFlags::Hexadecimal:
				szFormat[sizeof(szFormat) - 2] = 'X';
				break;
			default:
				/* throw */
				break;
			}

			sprintf_s(szString, szFormat, uElement);
		}

		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_FL32 fElement, _In_ A_I32 nIndex) {
		A_CHAR szString[64];
		sprintf_s(szString, "%f", fElement);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_FL64 fElement, _In_ A_I32 nIndex) {
		A_CHAR szString[64];
		sprintf_s(szString, "%f", fElement);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_CHAR cElement, _In_ CharacterRepresentation nCharRep, _In_ A_I32 nIndex) {
		if (nCharRep == CharacterRepresentation::ANSI) {
			A_CHAR szString[2] = { cElement, '\0' };
			Add(szString, nIndex);
		}
	}

	A_VOID String::Add(_In_ A_BOOL bElement, _In_ A_I32 nIndex) {
		A_CHAR szString[64];
		sprintf_s(szString, "%s", bElement ? "true" : "false");
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_ A_LPVOID lpPointer, _In_ A_I32 nIndex) {
		A_CHAR szString[64];
		sprintf_s(szString, "%p", lpPointer);
		Add(szString, nIndex);
	}

	A_VOID String::Add(_In_z_ A_LPCSTR lpString, _In_ A_I32 nIndex) {
		if (nIndex >= dwLength) /* throw */;

		if (this->lpString) {
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
		else {
			dwLength = strlen(lpString);
			this->lpString = new A_CHAR[dwLength + 1];
			strcpy_s(this->lpString, dwLength + 1, lpString);
		}
	}

	A_VOID String::AddFormat(_In_ A_I32 nIndex, _In_z_ _Printf_format_string_ A_LPCSTR lpFormat, ...) {
		A_CHAR szString[MAX_MSG];

		va_list v;
		va_start(v, lpFormat);
		vsprintf_s(szString, lpFormat, v);
		va_end(v);

		Add(szString, nIndex);
	}

	A_VOID String::Remove(_In_ A_I32 nCount, _In_ A_I32 nIndex) {
		if (nIndex + nCount >= dwLength) /* throw */;

		if (nIndex == -1) {
			dwLength -= nCount;
			lpString[dwLength] = '\0';
		}
		else {
			for (A_I32 i = 0; i < dwLength - nIndex - nCount; i++)
				lpString[nIndex + i] = lpString[nIndex + nCount + i];
			dwLength -= nCount;
			lpString[dwLength] = '\0';
		}
	}

	A_I32 String::FindFirst(_In_ const String& str) const {
		return FindFirst(str.GetCString());
	}

	A_I32 String::FindFirst(_In_ A_I8 nElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%hhi", nElement);
		return FindFirst(szString);
	}

	A_I32 String::FindFirst(_In_ A_I16 nElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%hi", nElement);
		return FindFirst(szString);
	}

	A_I32 String::FindFirst(_In_ A_I32 nElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%i", nElement);
		return FindFirst(szString);
	}

	A_I32 String::FindFirst(_In_ A_I64 nElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%lli", nElement);
		return FindFirst(szString);
	}

	A_I32 String::FindFirst(_In_ A_U8 uElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%hhu", uElement);
		return FindFirst(szString);
	}

	A_I32 String::FindFirst(_In_ A_U16 uElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%hu", uElement);
		return FindFirst(szString);
	}

	A_I32 String::FindFirst(_In_ A_U32 uElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%u", uElement);
		return FindFirst(szString);
	}

	A_I32 String::FindFirst(_In_ A_U64 uElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%llu", uElement);
		return FindFirst(szString);
	}

	A_I32 String::FindFirst(_In_ A_FL32 fElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%f", fElement);
		return FindFirst(szString);
	}

	A_I32 String::FindFirst(_In_ A_FL64 fElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%f", fElement);
		return FindFirst(szString);
	}

	A_I32 String::FindFirst(_In_ A_BOOL bElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%s", bElement ? "true" : "false");
		return FindFirst(szString);
	}

	A_I32 String::FindFirst(_In_ A_LPVOID lpPointer) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%p", lpPointer);
		return FindFirst(szString);
	}

	A_I32 String::FindFirst(_In_z_ A_LPCSTR lpString) const {
		A_BOOL bFound = true;

		for (A_I32 i = 0; i < dwLength; i++) {
			bFound = true;

			for (A_I32 j = 0; j < strlen(lpString); j++) {
				if (this->lpString[i + j] != lpString[j]) {
					bFound = false;
					break;
				}
			}

			if (bFound) return i;
		}
	}

	List<A_I32> String::Find(_In_ const String& str) const {
		return Find(str.GetCString());
	}

	List<A_I32> String::Find(_In_ A_I8 nElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%hhi", nElement);
		return Find(szString);
	}

	List<A_I32> String::Find(_In_ A_I16 nElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%hi", nElement);
		return Find(szString);
	}

	List<A_I32> String::Find(_In_ A_I32 nElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%i", nElement);
		return Find(szString);
	}

	List<A_I32> String::Find(_In_ A_I64 nElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%lli", nElement);
		return Find(szString);
	}

	List<A_I32> String::Find(_In_ A_U8 uElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%hhu", uElement);
		return Find(szString);
	}

	List<A_I32> String::Find(_In_ A_U16 uElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%hu", uElement);
		return Find(szString);
	}

	List<A_I32> String::Find(_In_ A_U32 uElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%u", uElement);
		return Find(szString);
	}

	List<A_I32> String::Find(_In_ A_U64 uElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%llu", uElement);
		return Find(szString);
	}

	List<A_I32> String::Find(_In_ A_FL32 fElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%f", fElement);
		return Find(szString);
	}

	List<A_I32> String::Find(_In_ A_FL64 fElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%f", fElement);
		return Find(szString);
	}

	List<A_I32> String::Find(_In_ A_BOOL bElement) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%s", bElement ? "true" : "false");
		return Find(szString);
	}

	List<A_I32> String::Find(_In_ A_LPVOID lpPointer) const {
		A_CHAR szString[64];
		sprintf_s(szString, "%p", lpPointer);
		return Find(szString);
	}

	List<A_I32> String::Find(_In_z_ A_LPCSTR lpString) const {
		List<A_I32> indexList;
		A_BOOL bFound = true;

		for (A_I32 i = 0; i < dwLength; i++) {
			bFound = true;

			for (A_I32 j = 0; j < strlen(lpString); j++) {
				if (this->lpString[i + j] != lpString[j]) {
					bFound = false;
					break;
				}
			}

			if (bFound) indexList.Add(i);
		}

		return indexList;
	}

	constexpr String::operator A_LPCSTR() const { return lpString; }

	constexpr A_LPCSTR String::GetCString() const { return lpString; }
	constexpr A_DWORD String::GetLength() const { return dwLength; }

	A_BOOL String::operator==(const String& operand) const {
		return !strcmp(lpString, operand.lpString);
	}

	A_BOOL String::operator!=(const String& operand) const {
		return !strcmp(lpString, operand.lpString);
	}

	String String::operator+(const String& operand) const {
		String ret;
		this->Clone(&ret);
		ret.Add(operand);
		return ret;
	}

	A_VOID String::operator+=(const String& operand) { this->Add(operand); }
}