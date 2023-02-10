#ifndef __AURORA_ENUMERATIONS_H__
#define __AURORA_ENUMERATIONS_H__

#include "Definitions.h"

namespace Aurora {
	/// <summary>
	/// <para>Represents a result after the comparison of two values.</para>
	/// <para>This is used as a return value for the compare routine of the collection classes.</para>
	/// <para>See guides or the API reference for usage examples.</para>
	/// </summary>
	struct CompareResult {
	private:
		typedef A_I32 EnumSize;

		EnumSize nValue;

	public:
		enum Enum : EnumSize {
			/// <summary>
			/// Element 1 is less than element 2.
			/// </summary>
			LessThan = -1,

			/// <summary>
			/// Element 1 and element 2 are equal.
			/// </summary>
			Equal = 0,

			/// <summary>
			/// Element 1 is more than element 2.
			/// </summary>
			MoreThan = 1
		};

		constexpr CompareResult() : nValue(0) {}
		constexpr CompareResult(_In_ EnumSize nValue) : nValue(nValue) {}
		constexpr CompareResult(_In_ Enum nValue) : nValue((EnumSize)nValue) {}

		constexpr operator Enum() const { return (Enum)nValue; }
	};

	struct IntegralRepresentationFlags {
	private:
		typedef A_DWORD EnumSize;

		EnumSize nValue;

	public:
		enum Enum : EnumSize {
			Binary = 1 << 0,
			Octal = 1 << 1,
			Decimal = 1 << 2,
			Hexadecimal = 1 << 3,
			All = Binary | Octal | Decimal | Hexadecimal
		};

		constexpr IntegralRepresentationFlags() : nValue(0) {}
		constexpr IntegralRepresentationFlags(_In_ EnumSize nValue) : nValue(nValue) {}
		constexpr IntegralRepresentationFlags(_In_ Enum nValue) : nValue((EnumSize)nValue) {}

		constexpr operator Enum() const { return (Enum)nValue; }
	};

	enum class CharacterRepresentation : A_I32 {
		None = 0,
		ANSI = 1,
		UTF_16LE = 2
	};

	struct ConsoleColorLegacyFlags {
	private:
		typedef A_WORD EnumSize;

		EnumSize nValue;

	public:
		enum Enum : EnumSize {
			Black = 0x0000,

			DarkRed = 0x0004,
			DarkGreen = 0x0002,
			DarkBlue = 0x0001,
			DarkGray = 0x0008,

			DarkCyan = DarkBlue | DarkGreen,
			DarkMagenta = DarkRed | DarkBlue,
			DarkYellow = DarkRed | DarkGreen,

			Gray = DarkRed | DarkGreen | DarkBlue,
			Red = DarkRed | DarkGray,
			Green = DarkGreen | DarkGray,
			Blue = DarkBlue | DarkGray,

			Cyan = DarkCyan | DarkGray,
			Magenta = DarkMagenta | DarkGray,
			Yellow = DarkYellow | DarkGray,
			White = DarkRed | DarkGreen | DarkBlue | DarkGray,
		};

		constexpr ConsoleColorLegacyFlags() : nValue(0) {}
		constexpr ConsoleColorLegacyFlags(_In_ EnumSize nValue) : nValue(nValue) {}
		constexpr ConsoleColorLegacyFlags(_In_ Enum nValue) : nValue((EnumSize)nValue) {}

		constexpr EnumSize GetForegroundLiteral() const { return nValue; }
		constexpr EnumSize GetBackgroundLiteral() const { return nValue << 4; }

		constexpr operator Enum() const { return (Enum)nValue; }
	};
}

#endif // !__AURORA_ENUMERATIONS_H__