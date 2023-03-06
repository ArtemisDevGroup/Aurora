#ifndef __AURORA_MEMORY_H__
#define __AURORA_MEMORY_H__

#include "Definitions.h"
#include "Array.h"
#include "ProcessInfo.h"

#include <type_traits>

namespace Aurora {
	// A concept that restrains the Read functions from returning a void to avoid weird compiler errors.
	template<typename T> concept ReadReturnType = !std::is_same<T, void>::value;

	// A concept that restrains the Write functions from accepting a void as a parameter to avoid weird compiler errors.
	template<typename T> concept WriteDataType = !std::is_same<T, void>::value;

	/// <summary>
	/// A pointer chain of 32-bit pointers.
	/// </summary>
	/// <typeparam name="ReturnType">- The type of data at the end of the pointer.</typeparam>
	template<typename ReturnType = void> class Pointer32 : public ArgumentList<A_ADDR32> { public: using ArgumentList<A_ADDR32>::ArgumentList; };

	/// <summary>
	/// A pointer chain of 64-bit pointers.
	/// </summary>
	/// <typeparam name="ReturnType">- The type of data at the end of the pointer.</typeparam>
	template<typename ReturnType = void> class Pointer64 : public ArgumentList<A_ADDR64> { public: using ArgumentList<A_ADDR64>::ArgumentList; };

	/// <summary>
	/// A pointer chain of 32-bit pointers with a base offset.
	/// </summary>
	/// <typeparam name="ReturnType">- The type of data at the end of the pointer.</typeparam>
	template<typename ReturnType = void>
	class BasePointer32 : public Pointer32<ReturnType> {
		A_DWORD dwBaseOffset;
	public:
		/// <summary>
		/// Constructs a base pointer.
		/// </summary>
		/// <param name="dwBaseOffset">- The offset from the base address.</param>
		/// <param name="list">- The pointer list.</param>
		inline BasePointer32(_In_ A_DWORD dwBaseOffset, _In_ const std::initializer_list<A_ADDR32>& list) : Pointer32<ReturnType>(list), dwBaseOffset(dwBaseOffset) {}

		/// <summary>
		/// Gets the base offset of the pointer.
		/// </summary>
		/// <returns>The base offset.</returns>
		constexpr A_DWORD GetOffset() const noexcept { return dwBaseOffset; }
	};

	/// <summary>
	/// A pointer chain of 64-bit pointers with a base offset.
	/// </summary>
	/// <typeparam name="ReturnType">- The type of data at the end of the pointer.</typeparam>
	template<typename ReturnType = void>
	class BasePointer64 : public Pointer64<ReturnType> {
		A_DWORD dwBaseOffset;
	public:
		/// <summary>
		/// Constructs a base pointer.
		/// </summary>
		/// <param name="dwBaseOffset">- The offset from the base address.</param>
		/// <param name="list">- The pointer list.</param>
		inline BasePointer64(_In_ A_DWORD dwBaseOffset, _In_ const std::initializer_list<A_ADDR64>& list) : Pointer64<ReturnType>(list), dwBaseOffset(dwBaseOffset) {}

		/// <summary>
		/// Gets the base offset of the pointer.
		/// </summary>
		/// <returns>The base offset.</returns>
		constexpr A_DWORD GetOffset() const noexcept { return dwBaseOffset; }
	};

#ifdef _WIN64
	/// <summary>
	/// A pointer chain of 64-bit pointers.
	/// </summary>
	/// <typeparam name="ReturnType">- The type of data at the end of the pointer.</typeparam>
	template<typename ReturnType = void> using Pointer = Pointer64<ReturnType>;

	/// <summary>
	/// A pointer chain of 64-bit pointers with a base offset.
	/// </summary>
	/// <typeparam name="ReturnType">- The type of data at the end of the pointer.</typeparam>
	template<typename ReturnType = void> using BasePointer = BasePointer64<ReturnType>;
#else
	/// <summary>
	/// A pointer chain of 32-bit pointers.
	/// </summary>
	/// <typeparam name="ReturnType">- The type of data at the end of the pointer.</typeparam>
	template<typename ReturnType = void> using Pointer = Pointer32<ReturnType>;

	/// <summary>
	/// A pointer chain of 32-bit pointers with a base offset.
	/// </summary>
	/// <typeparam name="ReturnType">- The type of data at the end of the pointer.</typeparam>
	template<typename ReturnType = void> using BasePointer = BasePointer32<ReturnType>;
#endif // _WIN64

	/// <summary>
	/// Reads memory from an address into a buffer. This function is unsafe and shall not be used unless speed is mandetory.
	/// </summary>
	/// <param name="uAddress">- The address to read memory from.</param>
	/// <param name="lpBuffer">- A pointer to a buffer that receives the read data.</param>
	/// <param name="dwSize">- The number of bytes to read.</param>
	/// <exception cref="ParameterInvalidException"/>
	A_VOID AURORA_API UnsafeRead(
		_In_range_(1, MAXLONGLONG) A_ADDR uAddress,
		_Out_writes_bytes_(dwSize) A_LPVOID lpBuffer,
		_In_ A_DWORD dwSize
	);

	/// <summary>
	/// Reads memory from an address and returns it. This function is unsafe and shall not be used unless speed is mandetory.
	/// </summary>
	/// <typeparam name="ReturnType">- The type to read.</typeparam>
	/// <param name="uAddress">- The address to read memory from.</param>
	/// <returns>The read data.</returns>
	/// <exception cref="ParameterInvalidException"/>
	/// <exception cref="ReadException"/>
	template<ReadReturnType ReturnType>
	inline ReturnType UnsafeRead(_In_ A_ADDR uAddress) {
		AuroraContextStart();

		ReturnType ret = ReturnType();
		UnsafeRead(uAddress, (A_LPVOID)&ret, sizeof(ReturnType));

		AuroraContextEnd();
		return ret;
	}

	/// <summary>
	/// Reads memory from an address and returns it. This function is unsafe and shall not be used unless speed is mandetory.
	/// </summary>
	/// <typeparam name="ReturnType">- The type to read.</typeparam>
	/// <param name="uAddress">- The address to read memory from.</param>
	/// <param name="lpBuffer">- A reference to a buffer to receive the read data.</param>
	/// <exception cref="ParameterInvalidException"/>
	/// <exception cref="ReadException"/>
	template<ReadReturnType ReturnType, A_I32 nSize>
	inline A_VOID UnsafeRead(
		_In_ A_ADDR uAddress,
		_Out_writes_(nSize) ReturnType(&lpBuffer)[nSize]
	) {
		AuroraContextStart();
		UnsafeRead(uAddress, (A_LPVOID)lpBuffer, nSize * sizeof(ReturnType));
		AuroraContextEnd();
	}



	/// <summary>
	/// Reads memory from an address into a buffer.
	/// </summary>
	/// <param name="uAddress">- The address to read memory from.</param>
	/// <param name="lpBuffer">- A pointer to a buffer that receives the read data.</param>
	/// <param name="dwSize">- The number of bytes to read.</param>
	/// <exception cref="ParameterInvalidException"/>
	/// <exception cref="ReadException"/>
	A_VOID AURORA_API Read(
		_In_range_(1, MAXLONGLONG) A_ADDR uAddress,
		_Out_writes_bytes_(dwSize) A_LPVOID lpBuffer,
		_In_ A_DWORD dwSize
	);

	/// <summary>
	/// Reads memory from an address and returns it.
	/// </summary>
	/// <typeparam name="ReturnType">- The type to read.</typeparam>
	/// <param name="uAddress">- The address to read memory from.</param>
	/// <returns>The read data.</returns>
	/// <exception cref="ParameterInvalidException"/>
	/// <exception cref="ReadException"/>
	template<ReadReturnType ReturnType>
	inline ReturnType Read(_In_ A_ADDR uAddress) {
		AuroraContextStart();
		
		ReturnType ret = ReturnType();
		Read(uAddress, (A_LPVOID)&ret, sizeof(ReturnType));

		AuroraContextEnd();
		return ret;
	}

	/// <summary>
	/// Reads memory from an address and returns it.
	/// </summary>
	/// <typeparam name="ReturnType">- The type to read.</typeparam>
	/// <param name="uAddress">- The address to read memory from.</param>
	/// <param name="lpBuffer">- A reference to a buffer to receive the read data.</param>
	/// <exception cref="ParameterInvalidException"/>
	/// <exception cref="ReadException"/>
	template<ReadReturnType ReturnType, A_I32 nSize>
	inline A_VOID Read(
		_In_ A_ADDR uAddress,
		_Out_writes_(nSize) ReturnType(&lpBuffer)[nSize]
	) {
		AuroraContextStart();
		Read(uAddress, (A_LPVOID)lpBuffer, nSize * sizeof(ReturnType));
		AuroraContextEnd();
	}



	/// <summary>
	/// Reads the address at the end of a pointer chain and returns it.
	/// </summary>
	/// <typeparam name="PointerType">- The type of data at the end of the pointer. In this instance, it does not have an effect on the return value.</typeparam>
	/// <param name="uBaseAddress">- The base address of the pointer.</param>
	/// <param name="refPointer">- A reference to the pointer.</param>
	/// <returns>The address at the end of the pointer chain.</returns>
	/// <exception cref="ParameterInvalidException"/>
	/// <exception cref="ReadException"/>
	template<typename PointerType>
	inline A_ADDR ReadPtrAddress(
		_In_ A_ADDR uBaseAddress,
		_In_ const Pointer<PointerType>& refPointer
	) {
		AuroraContextStart();

		for (A_ADDR uOffset : refPointer)
			uBaseAddress = Read<A_ADDR>(uBaseAddress) + uOffset;

		AuroraContextEnd();
		return uBaseAddress;
	}

	/// <summary>
	/// Reads the address at the end of a pointer chain and returns it.
	/// </summary>
	/// <typeparam name="PointerType">- The type of data at the end of the pointer. In this instance, it does not have an effect on the return value.</typeparam>
	/// <param name="lpModuleInfo">- A pointer to the module containing the base address of the pointer.</param>
	/// <param name="refPointer">- A reference to the pointer.</param>
	/// <returns>The address at the end of the pointer chain.</returns>
	/// <exception cref="ParameterInvalidException"/>
	/// <exception cref="ReadException"/>
	template<typename PointerType>
	inline A_ADDR ReadPtrAddress(
		_In_ const ModuleInfo* lpModuleInfo,
		_In_ const BasePointer<PointerType> refPointer
	) {
		AuroraContextStart();

		A_ADDR uAddress = lpModuleInfo->GetModuleBaseAddress() + refPointer.GetOffset();

		for (A_ADDR uOffset : refPointer)
			uAddress = Read<A_ADDR>(uAddress) + uOffset;

		AuroraContextEnd();
		return uAddress;
	}



	template<ReadReturnType ReturnType, typename PointerType>
	inline ReturnType ReadPtr(
		_In_ A_ADDR uBaseAddress,
		_In_ const Pointer<PointerType>& refPointer
	) {
		AuroraContextStart();

		uBaseAddress = ReadPtrAddress<PointerType>(uBaseAddress, refPointer);
		ReturnType retValue = Read<ReturnType>(uBaseAddress);

		AuroraContextEnd();
		return retValue;
	}

	template<ReadReturnType ReturnType>
	inline ReturnType ReadPtr(
		_In_ A_ADDR uBaseAddress,
		_In_ const Pointer<ReturnType>& refPointer
	) {
		AuroraContextStart();

		uBaseAddress = ReadPtrAddress<ReturnType>(uBaseAddress, refPointer);
		ReturnType retValue = Read<ReturnType>(uBaseAddress);

		AuroraContextEnd();
		return retValue;
	}

	template<ReadReturnType ReturnType, typename PointerType>
	inline ReturnType ReadPtr(
		_In_ const ModuleInfo* lpModuleInfo,
		_In_ const BasePointer<PointerType>& refPointer
	) {
		AuroraContextStart();

		A_ADDR uAddress = ReadPtrAddress<PointerType>(lpModuleInfo, refPointer);
		ReturnType retValue = Read<ReturnType>(uAddress);

		AuroraContextEnd();
		return retValue;
	}

	template<ReadReturnType ReturnType>
	inline ReturnType ReadPtr(
		_In_ const ModuleInfo* lpModuleInfo,
		_In_ const BasePointer<ReturnType>& refPointer
	) {
		AuroraContextStart();

		A_ADDR uAddress = ReadPtrAddress<ReturnType>(lpModuleInfo, refPointer);
		ReturnType retValue = Read<ReturnType>(uAddress);

		AuroraContextEnd();
		return retValue;
	}



	A_VOID AURORA_API ReadStringA(
		_In_ A_ADDR uAddress,
		_Out_writes_z_(dwCount) A_LPSTR lpBuffer,
		_In_ A_DWORD dwCount,
		_Out_opt_ A_LPDWORD lpNumberOfCharactersRead = nullptr
	);

	template<A_I32 nCount>
	inline A_VOID ReadStringA(
		_In_ A_ADDR uAddress,
		_Out_writes_z_(nCount) A_LPSTR lpBuffer,
		_Out_opt_ A_LPDWORD lpNumberOfCharactersRead = nullptr
	) {
		AuroraContextStart();
		ReadStringA(uAddress, lpBuffer, nCount, lpNumberOfCharactersRead);
		AuroraContextEnd();
	}



	A_VOID AURORA_API ReadStringW(
		_In_ A_ADDR uAddress,
		_Out_writes_z_(dwCount) A_LPWSTR lpBuffer,
		_In_ A_DWORD dwCount,
		_Out_opt_ A_LPDWORD lpNumberOfCharactersRead = nullptr
	);

	template<A_I32 nCount>
	inline A_VOID ReadStringW(
		_In_ A_ADDR uAddress,
		_Out_writes_z_(nSize) A_LPWSTR lpBuffer,
		_Out_opt_ A_LPDWORD lpNumberOfCharactersRead = nullptr
	) {
		AuroraContextStart();
		ReadStringW(uAddress, lpBuffer, nCount, lpNumberOfCharactersRead);
		AuroraContextEnd();
	}



	/// <summary>
	/// Writes memory to an address from a buffer. This function is unsafe and shall not be used unless speed is mandetory.
	/// </summary>
	/// <param name="uAddress">- The address to write memory to.</param>
	/// <param name="lpBuffer">- A pointer to a buffer that contains the data to write.</param>
	/// <param name="dwSize">- The number of bytes to write.</param>
	/// <exception cref="ParameterInvalidException"/>
	A_VOID AURORA_API UnsafeWrite(
		_In_range_(1, MAXLONGLONG) A_ADDR uAddress,
		_In_reads_bytes_(dwSize) A_LPCVOID lpBuffer,
		_In_ A_DWORD dwSize
	);

	/// <summary>
	/// Writes memory to an address from a buffer. This function is unsafe and shall not be used unless speed is mandetory.
	/// </summary>
	/// <param name="uAddress">- The address to write memory to.</param>
	/// <param name="refData">- The data to write.</param>
	/// <exception cref="ParameterInvalidException"/>
	template<WriteDataType DataType>
	inline A_VOID UnsafeWrite(
		_In_ A_ADDR uAddress,
		_In_ const DataType& refData
	) {
		AuroraContextStart();
		UnsafeWrite(uAddress, (A_LPCVOID)&refData, sizeof(DataType));
		AuroraContextEnd();
	}

	/// <summary>
	/// Writes memory to an address from a buffer. This function is unsafe and shall not be used unless speed is mandetory.
	/// </summary>
	/// <param name="uAddress">- The address to write memory to.</param>
	/// <param name="lpData">- A reference to an array containing the data to write.</param>
	/// <exception cref="ParameterInvalidException"/>
	/// <exception cref="WriteException"/>
	template<WriteDataType DataType, A_I32 nSize>
	inline A_VOID UnsafeWrite(
		_In_ A_ADDR uAddress,
		_In_ const DataType(&lpData)[nSize]
	) {
		AuroraContextStart();
		Write(uAddress, (A_LPCVOID)lpData, nSize * sizeof(DataType));
		AuroraContextEnd();
	}



	/// <summary>
	/// Writes memory to an address from a buffer.
	/// </summary>
	/// <param name="uAddress">- The address to write memory to.</param>
	/// <param name="lpBuffer">- A pointer to a buffer that contains the data to write.</param>
	/// <param name="dwSize">- The number of bytes to write.</param>
	/// <exception cref="ParameterInvalidException"/>
	/// <exception cref="WriteException"/>
	A_VOID AURORA_API Write(
		_In_range_(1, MAXLONGLONG) A_ADDR uAddress,
		_In_reads_bytes_(dwSize) A_LPCVOID lpBuffer,
		_In_ A_DWORD dwSize
	);

	/// <summary>
	/// Writes memory to an address from a buffer.
	/// </summary>
	/// <param name="uAddress">- The address to write memory to.</param>
	/// <param name="refData">- The data to write.</param>
	/// <exception cref="ParameterInvalidException"/>
	/// <exception cref="WriteException"/>
	template<WriteDataType DataType>
	inline A_VOID Write(
		_In_ A_ADDR uAddress,
		_In_ const DataType& refData
	) {
		AuroraContextStart();
		Write(uAddress, (A_LPCVOID)&refData, sizeof(DataType));
		AuroraContextEnd();
	}

	/// <summary>
	/// Writes memory to an address from a buffer.
	/// </summary>
	/// <param name="uAddress">- The address to write memory to.</param>
	/// <param name="lpData">- A reference to an array containing the data to write.</param>
	/// <exception cref="ParameterInvalidException"/>
	/// <exception cref="WriteException"/>
	template<WriteDataType DataType, A_I32 nSize>
	inline A_VOID Write(
		_In_ A_ADDR uAddress,
		_In_ const DataType(&lpData)[nSize]
	) {
		AuroraContextStart();
		Write(uAddress, (A_LPCVOID)lpData, nSize * sizeof(DataType));
		AuroraContextEnd();
	}
}

#endif // !__AURORA_MEMORY_H__