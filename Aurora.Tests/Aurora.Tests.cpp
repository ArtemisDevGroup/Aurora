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

#define DEFINE_ENUM_FLAGS(EnumName, EnumType, ...) \
struct EnumName {\
private:\
	typedef EnumType EnumSize;\
	EnumSize nValue;\
public:\
	enum Enum : EnumSize { __VA_ARGS__ };\
	constexpr EnumName##() noexcept : nValue(0) {}\
	constexpr EnumName##(_In_ EnumSize nValue) noexcept : nValue(nValue) {}\
	constexpr EnumName##(_In_ Enum nValue) noexcept : nValue((EnumSize)nValue) {}\
	constexpr operator Enum() const noexcept { return (Enum)nValue; }\
}

DEFINE_ENUM_FLAGS( TestFlags, int,
	Test1,
	Test2
);

int main() {

}