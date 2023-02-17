#ifndef __AURORA_BINARY_H__
#define __AURORA_BINARY_H__

#include "Definitions.h"

namespace Aurora {
	template<typename BufferType>
	class Binary {
		BufferType Buffer;

	public:
		static constexpr A_I32 BufferByteCount = sizeof(BufferType);
		static constexpr A_I32 BufferBitCount = sizeof(BufferType) * 8;

		constexpr Binary() noexcept : Buffer(0) {}
		constexpr Binary(_In_ BufferType Buffer) noexcept : Buffer(Buffer) {}

		constexpr A_BOOL CheckBit(_In_range_(0, BufferBitCount) A_I32 nBit) const noexcept { return !!(Buffer & (1 << nBit)); }
		constexpr A_VOID SetBit(_In_range_(0, BufferBitCount) A_I32 nBit) noexcept { Buffer = Buffer | (1 << nBit); }
		constexpr A_VOID ResetBit(_In_range_(0, BufferBitCount) A_I32 nBit) noexcept { Buffer = Buffer ^ (1 << nBit); }

		constexpr Binary Rotl(A_U32 uShift) const noexcept { return Binary(Buffer << uShift | Buffer >> (BufferBitCount - uShift)); }
		constexpr Binary Rotr(A_U32 uShift) const noexcept { return Binary(Buffer >> uShift | Buffer << (BufferBitCount - uShift)); }

		constexpr BufferType GetBuffer() const noexcept { return Buffer; }

		A_VOID GetBinaryString(_Out_writes_z_(BufferBitCount + 1) A_CHAR(&lpBuffer)[BufferBitCount + 1]) const {
			for (A_I32 i = 0; i < BufferBitCount; i++)
				lpBuffer[i] = CheckBit(i) ? '1' : '0';
			lpBuffer[BufferBitCount] = '\0';
		}

		constexpr Binary operator+(_In_ const Binary& right) const noexcept { return Binary(Buffer + right.Buffer); }
		constexpr Binary operator-(_In_ const Binary& right) const noexcept { return Binary(Buffer - right.Buffer); }
		constexpr Binary operator*(_In_ const Binary& right) const noexcept { return Binary(Buffer * right.Buffer); }
		constexpr Binary operator/(_In_ const Binary& right) const noexcept { return Binary(Buffer / right.Buffer); }
		constexpr Binary operator%(_In_ const Binary& right) const noexcept { return Binary(Buffer % right.Buffer); }

		constexpr Binary operator&(_In_ const Binary& right) const noexcept { return Binary(Buffer & right.Buffer); }
		constexpr Binary operator|(_In_ const Binary& right) const noexcept { return Binary(Buffer | right.Buffer); }
		constexpr Binary operator^(_In_ const Binary& right) const noexcept { return Binary(Buffer ^ right.Buffer); }

		constexpr Binary operator<<(_In_ A_I32 nShiftCount) const noexcept { return Binary(Buffer << nShiftCount); }
		constexpr Binary operator>>(_In_ A_I32 nShiftCount) const noexcept { return Binary(Buffer >> nShiftCount); }

		constexpr A_VOID operator+=(_In_ const Binary& right) noexcept { Buffer += right.Buffer; }
		constexpr A_VOID operator-=(_In_ const Binary& right) noexcept { Buffer -= right.Buffer; }
		constexpr A_VOID operator*=(_In_ const Binary& right) noexcept { Buffer *= right.Buffer; }
		constexpr A_VOID operator/=(_In_ const Binary& right) noexcept { Buffer /= right.Buffer; }
		constexpr A_VOID operator%=(_In_ const Binary& right) noexcept { Buffer %= right.Buffer; }

		constexpr A_VOID operator&=(_In_ const Binary& right) noexcept { Buffer &= right.Buffer; }
		constexpr A_VOID operator|=(_In_ const Binary& right) noexcept { Buffer |= right.Buffer; }
		constexpr A_VOID operator^=(_In_ const Binary& right) noexcept { Buffer ^= right.Buffer; }

		constexpr A_VOID operator~() const noexcept { ~Buffer; }
	};
}

#endif // !__AURORA_BINARY_H__