#ifndef __AURORA_INTERFACES_H__
#define __AURORA_INTERFACES_H__

#include "Definitions.h"

namespace Aurora {
	template<typename ElementType>
	class IIterable {
		ElementType** ppArray;
		A_LPI32 lpArraySize;
		A_LPI32 lpCurrentSize;

	public:
		constexpr IIterable(_In_ ElementType** ppArray, _In_ A_LPI32 lpArraySize, _In_opt_ A_LPI32 lpCurrentSize = nullptr) : ppArray(ppArray), lpArraySize(lpArraySize), lpCurrentSize(lpCurrentSize) {}

		constexpr const A_I32 size() const { return lpCurrentSize ? *lpCurrentSize : *lpArraySize; }

		ElementType* begin() { return *ppArray; }
		constexpr const ElementType* begin() const { return *ppArray; }

		ElementType* end() { return &(*ppArray)[size()]; }
		constexpr const ElementType* end() const { return &(*ppArray)[size()]; }
	};

	class IDisposable {
	public:
		/// <summary>
		/// Clones the disposable data of the class and creates a new instance.
		/// </summary>
		/// <param name="pDestination">- The cloned object destination.</param>
		virtual A_VOID Clone(_Out_ A_LPVOID lpDestination) const = 0;

		virtual A_VOID Release() = 0;
	};

	class AURORA_API Registerable {
	public:
		A_DWORD dwRegisteredCount;
	};

	template<class Enum, typename EnumSize>
	struct EnumFlags {
		EnumSize nValue;

		constexpr EnumFlags() noexcept : nValue(0) {}
		constexpr EnumFlags(_In_ EnumSize nValue) noexcept : nValue(nValue) {}
		constexpr EnumFlags(_In_ Enum nValue) noexcept : nValue((EnumSize)nValue) {}

		constexpr operator Enum() const noexcept { return (Enum)nValue; }
		constexpr operator EnumSize() const noexcept { return nValue; }
	};
}

#endif // !__AURORA_INTERFACES_H__