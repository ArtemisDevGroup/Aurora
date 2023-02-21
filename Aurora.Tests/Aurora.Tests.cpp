#include <stdio.h>

//------------------------
// TODO:
// All files:
//		Add copyright and author notice to the top of every file.
//		Inline document everything.
// Array.h: Global.
// Binary.h: Global.
// Color.h:	Implement HEX.
// Console.h: Add more functions.
// Definitions.h: Global.
// Enumerations.h: Global.
// Events.h: Global.
// Exceptions.h: Global.
// Identification.h: Global.
// Interfaces.h: Take a look into if it is needed in the first place.
// String.h: Fix everything.
// Thread.h: Global.
// Vector.h: Global.
// 
// Color.cpp: Same as h.
// Console.cpp: Same as h.
// Exceptions.cpp: Global.
// Identification.cpp: Global.
// String.cpp: Fix everything.
//------------------------

template<class Enum, typename EnumSize>
struct IEnumFlags {
private:
	EnumSize nValue;

public:
	constexpr IEnumFlags() noexcept : nValue(0) {}
	constexpr IEnumFlags(_In_ EnumSize nValue) noexcept : nValue(nValue) {}
	constexpr IEnumFlags(_In_ Enum nValue) noexcept : nValue((EnumSize)nValue) {}
	constexpr operator Enum() const noexcept { return (Enum)nValue; }
};

enum class MyEnum : int {
	Test1
};

#define DEFINE_FLAGS(EnumClass, EnumSize) struct EnumClass ## Flags : IEnumFlags<EnumClass, EnumSize> { using enum EnumClass; }

DEFINE_FLAGS(MyEnum, int);

int main() {
	
}