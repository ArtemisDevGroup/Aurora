#ifndef __AURORA_BINARY_H__
#define __AURORA_BINARY_H__

#include "Definitions.h"
#include "String.h"

namespace Aurora {
	template<typename BufferType>
	class Binary {
		BufferType Buffer;

	public:
		static constexpr A_I32 BufferByteCount = sizeof(BufferType);
		static constexpr A_I32 BufferBitCount = sizeof(BufferType) * 8;

		constexpr Binary() : Buffer(0) {}
		constexpr Binary(_In_ BufferType Buffer) : Buffer(Buffer) {}

		constexpr A_BOOL CheckBit(_In_range_(0, BufferBitCount) A_I32 nBit) const { return !!(Buffer & (1 << nBit)); }
		constexpr A_VOID SetBit(_In_range_(0, BufferBitCount) A_I32 nBit) { Buffer = Buffer | (1 << nBit); }
		constexpr A_VOID ResetBit(_In_range_(0, BufferBitCount) A_I32 nBit) { Buffer = Buffer ^ (1 << nBit); }

		constexpr BufferType GetBuffer() const { return Buffer; }
		String GetBinaryString() const {
			A_CHAR szString[BufferBitCount + 1];

			for (A_I32 i = 0; i < BufferBitCount; i++)
				szString[i] = CheckBit(i) ? '1' : '0';
			szString[BufferBitCount] = '\0';

			return String(szString);
		}

		constexpr Binary operator+(_In_ const Binary& right) const { return Binary(Buffer + right.Buffer); }
		constexpr Binary operator-(_In_ const Binary& right) const { return Binary(Buffer - right.Buffer); }
		constexpr Binary operator*(_In_ const Binary& right) const { return Binary(Buffer * right.Buffer); }
		constexpr Binary operator/(_In_ const Binary& right) const { return Binary(Buffer / right.Buffer); }
		constexpr Binary operator%(_In_ const Binary& right) const { return Binary(Buffer % right.Buffer); }

		constexpr Binary operator&(_In_ const Binary& right) const { return Binary(Buffer & right.Buffer); }
		constexpr Binary operator|(_In_ const Binary& right) const { return Binary(Buffer | right.Buffer); }
		constexpr Binary operator^(_In_ const Binary& right) const { return Binary(Buffer ^ right.Buffer); }

		constexpr A_VOID operator+=(_In_ const Binary& right) { Buffer += right.Buffer; }
		constexpr A_VOID operator-=(_In_ const Binary& right) { Buffer -= right.Buffer; }
		constexpr A_VOID operator*=(_In_ const Binary& right) { Buffer *= right.Buffer; }
		constexpr A_VOID operator/=(_In_ const Binary& right) { Buffer /= right.Buffer; }
		constexpr A_VOID operator%=(_In_ const Binary& right) { Buffer %= right.Buffer; }

		constexpr A_VOID operator&=(_In_ const Binary& right) { Buffer &= right.Buffer; }
		constexpr A_VOID operator|=(_In_ const Binary& right) { Buffer |= right.Buffer; }
		constexpr A_VOID operator^=(_In_ const Binary& right) { Buffer ^= right.Buffer; }

		constexpr A_VOID operator~() const { ~Buffer; }
	};
}

#endif // !__AURORA_BINARY_H__