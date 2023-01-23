#ifndef __AURORA_INTERFACES_H__
#define __AURORA_INTERFACES_H__

#include "Definitions.h"

namespace Aurora {
	template<typename ElementType>
	class IIterable {
		ElementType** ppArray;
		int* pnArraySize;
		int* pnCurrentSize;

	public:
		constexpr IIterable(_In_ ElementType** ppArray, _In_ int* pnArraySize, _In_opt_ int* pnCurrentSize = nullptr) : ppArray(ppArray), pnArraySize(pnArraySize), pnCurrentSize(pnCurrentSize) {}

		constexpr const int size() const { return pnCurrentSize ? *pnCurrentSize : *pnArraySize; }

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
		virtual void Clone(_Out_ void* pDestination) const = 0;

		virtual void Release() = 0;
	};

	class IRegisterable {
	public:
		DWORD dwRegisteredCount;
	};
}

#endif // !__AURORA_INTERFACES_H__