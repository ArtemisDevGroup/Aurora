#include <stdio.h>

//------------------------
// TODO:
// All files:
//		Add copyright and author notice to the top of every file.
//		Inline document everything.
// Console.h: Add more functions.
// Interfaces.h: Take a look into if it is needed in the first place.
// 
// Console.cpp: Same as h.
//------------------------

#include <Windows.h>
#include <type_traits>
#include <concepts>

#include <Aurora/Pipe.h>
#include <Aurora/Binary.h>

using namespace Aurora;

template<typename T>
concept NonVoid = !std::is_same<T, void>::value;

template<typename T>
concept IsArithmetic = requires(T a) {
	{ a + a };
	{ a - a };
	{ a * a };
	{ a / a };
};

template<typename T>
concept IsComparable = requires(T a) {
	{ a > a } -> std::convertible_to<bool>;
	{ a >= a } -> std::convertible_to<bool>;
	{ a < a } -> std::convertible_to<bool>;
	{ a <= a } -> std::convertible_to<bool>;
	{ a == a } -> std::convertible_to<bool>;
	{ a != a } -> std::convertible_to<bool>;
};

class IComparable {
public:
	virtual bool operator<(IComparable&) const = 0;
	virtual bool operator<=(IComparable&) const = 0;
	virtual bool operator>(IComparable&) const = 0;
	virtual bool operator>=(IComparable&) const = 0;
	virtual bool operator!=(IComparable&) const = 0;
	virtual bool operator==(IComparable&) const = 0;
};

int main() {

}