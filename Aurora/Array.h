#ifndef __AURORA_ARRAY_H__
#define __AURORA_ARRAY_H__

#include <initializer_list>
#include <stdlib.h>

#include "Definitions.h"
#include "Enumerations.h"
#include "Interfaces.h"

namespace Aurora {
	template<typename Type1, typename Type2>
	class Pair {
		Type1 Field1;
		Type2 Field2;

	public:
		Pair() : Field1(), Field2() {}
		Pair(_In_ Type1 First, _In_ Type2 Second) : Field1(First), Field2(Second) {}

		constexpr const Type1& GetFirst() const { return Field1; }
		constexpr Type1& GetFirst() { return Field1; }
		constexpr const Type2& GetSecond() const { return Field2; }
		constexpr Type2& GetSecond() { return Field2; }
	};

	/// <summary>
	/// A class for storing sequences of data.
	/// </summary>
	/// <typeparam name="ElementType">- The type of the elements to store.</typeparam>
	/// <typeparam name="nElementCount">- The number of elements to store.</typeparam>
	template<typename ElementType, A_I32 nElementCount>
	class AURORA_API Array {
	public:
		/// <summary>
		/// The core array storing the values.
		/// </summary>
		ElementType szArray[nElementCount];

		inline operator ElementType* () { return szArray; }
		constexpr operator const ElementType* () const { return szArray; }

		inline ElementType& operator[](A_I32 nIndex) { return szArray[nIndex]; }
		constexpr const ElementType operator[](A_I32 nIndex) const { return szArray[nIndex]; }

		/// <summary>
		/// Gets the size of the array and returns it.
		/// </summary>
		/// <returns>The size of the array.</returns>
		constexpr _Check_return_ const A_I32 size() const { return nElementCount; }

		/// <summary>
		/// Gets the begin iterator.
		/// </summary>
		/// <returns>The begin iterator.</returns>
		inline ElementType* begin() { return szArray; }

		/// <summary>
		/// Gets the begin const iterator.
		/// </summary>
		/// <returns>The begin const iterator.</returns>
		constexpr const ElementType* begin() const { return szArray; }

		/// <summary>
		/// Ges the end iterator.
		/// </summary>
		/// <returns>The end iterator.</returns>
		inline ElementType* end() { return &szArray[nElementCount]; }

		/// <summary>
		/// Gets the end const iterator.
		/// </summary>
		/// <returns>The end const iterator.</returns>
		constexpr const ElementType* end() const { return &szArray[nElementCount]; }

		/// <summary>
		/// A function template for a function used to compare elements in this array and sort them accordingly.
		/// </summary>
		typedef CompareResult(__cdecl* CompareFunction)(const ElementType* pElement1, const ElementType* pElement2);

		/// <summary>
		/// Test
		/// </summary>
		/// <param name="lpfnCompareFunction">
		/// - A pointer to a routine that compares elements against each other and returns their relation to each other. See CompareResult for more information.
		/// </param>
		inline A_VOID Sort(_In_ CompareFunction lpfnCompareFunction) { qsort((void*)szArray, nElementCount, sizeof(ElementType), (_CoreCrtNonSecureSearchSortCompareFunction)lpfnCompareFunction); }
	};

	template<typename ElementType>
	class AURORA_API List : public IIterable<ElementType>, public IDisposable {
		ElementType* pArray;
		A_I32 nCount;
		A_I32 nMaxCount;

		static const A_I32 c_nPageSize = 64;

		static constexpr A_I32 ntob(A_I32 n) { return n * sizeof(ElementType); }
		static constexpr A_I32 bton(A_I32 b) { return b / sizeof(ElementType); }

		static constexpr A_I32 GetRealAllocCount(A_I32 nCount) {
			return bton(c_nPageSize * (ntob(nCount) % c_nPageSize ? (ntob(nCount) / c_nPageSize + 1) : (ntob(nCount) / c_nPageSize)));
		}

		inline A_VOID Allocate(_In_ A_I32 nCount) {
			if (nCount <= nMaxCount) return;

			A_I32 nAllocCount = GetRealAllocCount(nCount);

			if (pArray) {
				ElementType* pOldArray = pArray;
				A_I32 nOldMaxCount = nMaxCount;

				pArray = new ElementType[nAllocCount];
				nMaxCount = nAllocCount;

				for (A_I32 i = 0; i < this->nCount; i++) pArray[i] = pOldArray[i];
			}
			else {
				pArray = new ElementType[nAllocCount];
				nMaxCount = nAllocCount;
				this->nCount = 0;
			}
		}

		inline A_VOID Move(_In_ A_I32 nFrom, _In_ A_I32 nTo) {
			if (nFrom > nTo) {
				for (A_I32 i = 0; i < this->nCount - nFrom; i++) pArray[nTo + i] = pArray[nFrom + i];
			}
			else if (nFrom < nTo) {
				for (A_I32 i = this->nCount - 1; i >= nFrom; i--)
					pArray[nTo - nFrom + i] = pArray[i];
			}
			else /* throw */;
		}

	public:
		inline List() : IIterable<ElementType>(&pArray, &nMaxCount, &nCount), pArray(nullptr), nMaxCount(0), nCount(0) {}

		inline List(_In_ const std::initializer_list<ElementType>& list) : IIterable<ElementType>(&pArray, &nMaxCount, &nCount) {
			Allocate(list.size());

			for (A_I32 i = 0; i < list.size(); i++) pArray[i] = list.begin()[i];

			nCount = list.size();
		}

		template<A_I32 nCount>
		inline List(_In_ const ElementType(&pArray)[nCount]) : IIterable<ElementType>(&this->pArray, &nMaxCount, &this->nCount) {
			Allocate(nCount);

			for (A_I32 i = 0; i < nCount; i++) this->pArray[i] = pArray[i];

			this->nCount = nCount;
		}

		inline List(_In_ const ElementType* pArray, _In_ A_I32 nCount) : IIterable<ElementType>(&this->pArray, &nMaxCount, &this->nCount) {
			Allocate(nCount);

			for (A_I32 i = 0; i < nCount; i++) this->pArray[i] = pArray[i];

			this->nCount = nCount;
		}

		inline virtual A_VOID IDisposable::Clone(_Out_ A_LPVOID lpDestination) const {
			List<ElementType>* pDst = (List<ElementType>*)lpDestination;
			pDst->Allocate(nCount);

			for (A_I32 i = 0; i < nCount; i++) pDst->pArray[i] = pArray[i];

			pDst->nCount = nCount;
		}

		inline List(const List<ElementType>& cpy) : IIterable<ElementType>(&pArray, &nMaxCount, &nCount) { cpy.Clone(this); }

		inline virtual A_VOID IDisposable::Release() {
			if (pArray) {
				delete[] pArray;
				pArray = nullptr;
				nCount = 0;
			}
		}

		inline ~List() { Release(); }

		inline A_VOID Add(_In_ ElementType elem, _In_ A_I32 nIndex = -1) {
			Allocate(nCount + 1);

			if (nIndex == -1) {
				pArray[nCount] = elem;
				nCount++;
			}
			else {
				Move(nIndex, nIndex + 1);
				pArray[nIndex] = elem;
				nCount++;
			}
		}

		inline A_VOID Add(_In_ const std::initializer_list<ElementType>& list, _In_ A_I32 nIndex = -1) {
			Allocate(nCount + list.size());

			if (nIndex == -1) {
				for (A_I32 i = 0; i < list.size(); i++)
					pArray[nCount + i] = list.begin()[i];

				nCount += list.size();
			}
			else {
				Move(nIndex, nIndex + list.size());
				for (A_I32 i = 0; i < list.size(); i++)
					pArray[nIndex + i] = list.begin()[i];

				nCount += list.size();
			}
		}

		inline A_VOID Add(_In_ const ElementType* pArray, _In_ A_I32 nCount, _In_ A_I32 nIndex = -1) {
			Allocate(this->nCount + nCount);

			if (nIndex == -1) {
				for (int i = 0; i < nCount; i++)
					this->pArray[this->nCount + i] = pArray[i];

				this->nCount += nCount;
			}
			else {
				Move(nIndex, nIndex + nCount);
				for (int i = 0; i < nCount; i++)
					this->pArray[nIndex + i] = pArray[i];

				this->nCount += nCount;
			}
		}

		inline A_VOID Remove(_In_ A_I32 nCount = 1, _In_ A_I32 nIndex = -1) {
			if (nIndex == -1) {
				this->nCount -= nCount;
			}
			else {
				Move(nIndex + nCount, nIndex);
				this->nCount -= nCount;
			}
		}

		inline A_VOID Concatenate(_In_ const List<ElementType>& other) {
			Add(other.begin(), other.size(), -1);
		}

		typedef CompareResult(__cdecl* CompareFunction)(const ElementType* pElement1, const ElementType* pElement2);

		inline A_VOID Sort(_In_ CompareFunction lpfnCompareFunction) { qsort((void*)pArray, nCount, sizeof(ElementType), (_CoreCrtNonSecureSearchSortCompareFunction)lpfnCompareFunction); }

		inline operator ElementType* () { return pArray; }
		constexpr operator const ElementType* () const { return pArray; }

		inline ElementType& operator[](A_I32 nIndex) {
			if (nIndex >= nCount) /* throw */;
			return pArray[nIndex];
		}

		constexpr const ElementType operator[](A_I32 nIndex) const {
			if (nIndex >= nCount) /* throw */;
			return pArray[nIndex];
		}
	};

	template<typename ElementType>
	class AURORA_API ArgumentList : public IIterable<ElementType>, public IDisposable {
		ElementType* pArray;
		int nCount;

	public:
		inline ArgumentList() : IIterable<ElementType>(&pArray, &nCount), pArray(nullptr), nCount(0) {}

		inline ArgumentList(_In_ const std::initializer_list<ElementType>& list) : IIterable<ElementType>(&pArray, &nCount) {
			nCount = list.size();
			if (nCount > 0) {
				pArray = new ElementType[nCount];
				for (int i = 0; i < nCount; i++) pArray[i] = list.begin()[i];
			}
		}

		inline virtual A_VOID IDisposable::Clone(_Out_ A_LPVOID lpDestination) const {
			ArgumentList<ElementType>* pDst = (ArgumentList<ElementType>*)lpDestination;

			if (pArray) {
				pDst->pArray = new ElementType[nCount];
				pDst->nCount = nCount;

				for (int i = 0; i < nCount; i++)
					pDst->pArray[i] = pArray[i];
			}
			else memset(lpDestination, 0, sizeof(ArgumentList));
		}

		inline ArgumentList(const ArgumentList<ElementType>& cpy) : IIterable<ElementType>(&pArray, &nCount) { cpy.Clone(this); }

		inline virtual A_VOID IDisposable::Release() {
			if (pArray) {
				delete[] pArray;
				pArray = nullptr;
				nCount = 0;
			}
		}

		inline ~ArgumentList() { Release(); }

		inline operator ElementType* () { return pArray; }
		constexpr operator const ElementType* () const { return pArray; }

		inline ElementType& operator[](A_I32 nIndex) { return pArray[nIndex]; }
		constexpr const ElementType operator[](A_I32 nIndex) const { return pArray[nIndex]; }
	};
}

#endif // !__AURORA_ARRAY_H__