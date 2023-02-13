#ifndef __AURORA_DEFINITIONS_H__
#define __AURORA_DEFINITIONS_H__

#ifndef _AURORA_EXCLUDE_SAL
#include <sal.h>
#else

#define _In_
#define _In_opt_
#define _In_reads_(x)
#define _In_reads_bytes_(x)

#define _Out_
#define _Out_opt_
#define _Out_writes_(x)
#define _Out_writes_bytes_(x)

#define _Reserved_

#define _Ret_z_
#define _Ret_maybenull_
#define _Ret_maybenull_z_
#define _Ret_notnull_

#define _Check_return_

#endif // !_AURORA_EXCLUDE_SAL

#define AURORA_EXPORT __declspec(dllexport)
#define AURORA_IMPORT __declspec(dllimport)

#ifdef _AURORA_EXPORT
#define AURORA_API AURORA_EXPORT
#else
#define AURORA_API AURORA_IMPORT
#endif

#ifndef MAX_PATH
// The maximum number of characters in a valid file path.
#define MAX_PATH 260
#endif // !MAX_PATH

#ifndef MAX_NAME
// The maximum number of characters in a name.
#define MAX_NAME 128
#endif // !MAX_NAME

#ifndef MAX_MSG
// The maximum number of characers in a message.
#define MAX_MSG 256
#endif // !MAX_MSG

#ifndef MAX_INVOKE
// The maximum number of invokable objects registered per instance.
#define MAX_INVOKE 64
#endif // !MAX_INVOKE

#define INVALID_INDEX (-1) // An invalid index.

#define A_VOID void

// A void pointer. Generally used as an out pointer of a generic type. Is prefixed as 'lp'.
typedef A_VOID* A_LPVOID;
// A constant void pointer. Generally used as an in pointer of a generic type. Is prefixed as 'lp'.
typedef const A_VOID* A_LPCVOID;

// An ANSI character, prefixed as 'c'.
typedef char A_CHAR;
// An ANSI character pointer, prefixed as 'lp'.
typedef char* A_LPCHAR;
// An ANSI character pointer. Used for string buffers and is prefixed as 'lp'.
typedef char* A_LPSTR;
// A constant ANSI character pointer. Used for strings and is prefixed as 'lp'.
typedef const char* A_LPCSTR;

// A UTF-16LE character, prefixed as 'wc'.
typedef wchar_t A_WCHAR;
// A UTF-16LE character pointer, prefixed as 'lp'.
typedef wchar_t* A_LPWCHAR;
// A UTF-16LE character pointer. Used for wide string buffers and is prefixed as 'lp'.
typedef wchar_t* A_LPWSTR;
// A UTF-16LE character pointer. Used for wide strings and is prefixed as 'lp'.
typedef const wchar_t* A_LPCWSTR;

// A boolean, prefixed as 'b'.
typedef bool A_BOOL;
// A boolean pointer, prefixed as 'lp'.
typedef bool* A_LPBOOL;
// A constant boolean pointer, prefixed as 'lp'.
typedef const bool* A_LPCBOOL;

// An 8-bit signed integer, prefixed as 'n'.
typedef signed __int8 A_I8;
// A 16-bit signed integer, prefixed as 'n'.
typedef signed __int16 A_I16;
// A 32-bit signed integer, prefixed as 'n'.
typedef signed __int32 A_I32;
// A 64-bit signed integer, prefixed as 'n'.
typedef signed __int64 A_I64;

// An 8-bit signed integer pointer, prefixed as 'lp'.
typedef A_I8* A_LPI8;
// A 16-bit signed integer pointer, prefixed as 'lp'.
typedef A_I16* A_LPI16;
// A 32-bit signed integer pointer, prefixed as 'lp'.
typedef A_I32* A_LPI32;
// A 64-bit signed integer pointer, prefixed as 'lp'.
typedef A_I64* A_LPI64;

// A constant 8-bit signed integer pointer, prefixed as 'lp'.
typedef const A_I8* A_LPCI8;
// A constant 16-bit signed integer pointer, prefixed as 'lp'.
typedef const A_I16* A_LPCI16;
// A constant 32-bit signed integer pointer, prefixed as 'lp'.
typedef const A_I32* A_LPCI32;
// A constant 64-bit signed integer pointer, prefixed as 'lp'.
typedef const A_I64* A_LPCI64;

// An 8-bit unsigned integer, prefixed as 'u'.
typedef unsigned __int8 A_U8;
// A 16-bit unsigned integer, prefixed as 'u'.
typedef unsigned __int16 A_U16;
// A 32-bit unsigned integer, prefixed as 'u'.
typedef unsigned __int32 A_U32;
// A 64-bit unsigned integer, prefixed as 'u'.
typedef unsigned __int64 A_U64;

// An 8-bit unsigned integer pointer, prefixed as 'lp'.
typedef A_U8* A_LPU8;
// A 16-bit unsigned integer pointer, prefixed as 'lp'.
typedef A_U16* A_LPU16;
// A 32-bit unsigned integer pointer, prefixed as 'lp'.
typedef A_U32* A_LPU32;
// A 64-bit unsigned integer pointer, prefixed as 'lp'.
typedef A_U64* A_LPU64;

// A constant 8-bit unsigned integer pointer, prefixed as 'lp'.
typedef const A_U8* A_LPCU8;
// A constant 16-bit unsigned integer pointer, prefixed as 'lp'.
typedef const A_U16* A_LPCU16;
// A constant 32-bit unsigned integer pointer, prefixed as 'lp'.
typedef const A_U32* A_LPCU32;
// A constant 64-bit unsigned integer pointer, prefixed as 'lp'.
typedef const A_U64* A_LPCU64;

// An 8-bit unsigned integer, prefixed as 'u'.
typedef unsigned char A_BYTE;
// A 16-bit unsigned integer, prefixed as 'w'.
typedef unsigned short A_WORD;
// A 32-bit unsigned integer, prefixed as 'dw'.
typedef unsigned long A_DWORD;
// A 64-bit unsigned integer, prefixed as 'qw'.
typedef unsigned long long A_QWORD;

// An 8-bit unsigned integer pointer, prefixed as 'lp'.
typedef A_BYTE* A_LPBYTE;
// A 16-bit unsigned integer pointer, prefixed as 'lp'.
typedef A_WORD* A_LPWORD;
// A 32-bit unsigned integer pointer, prefixed as 'lp'.
typedef A_DWORD* A_LPDWORD;
// A 64-bit unsigned integer pointer, prefixed as 'lp'.
typedef A_QWORD* A_LPQWORD;

// A constant 8-bit unsigned integer pointer, prefixed as 'lp'.
typedef const A_BYTE* A_LPCBYTE;
// A constant 16-bit unsigned integer pointer, prefixed as 'lp'.
typedef const A_WORD* A_LPCWORD;
// A constant 32-bit unsigned integer pointer, prefixed as 'lp'.
typedef const A_DWORD* A_LPCDWORD;
// A constant 64-bit unsigned integer pointer, prefixed as 'lp'.
typedef const A_QWORD* A_LPCQWORD;

// A 32-bit floating point, prefixed as 'f'.
typedef float A_FL32;
// A 64-bit floating point, prefixed as 'f'.
typedef double A_FL64;

// A 32-bit floating point pointer, prefixed as 'lp'.
typedef A_FL32* A_LPFL32;
// A 64-bit floating point pointer, prefixed as 'lp'.
typedef A_FL64* A_LPFL64;

// A constant 32-bit floating point pointer, prefixed as 'lp'.
typedef const A_FL32* A_LPCFL32;
// A constant 64-bit floating point pointer, prefixed as 'lp'.
typedef const A_FL64* A_LPCFL64;

#endif // !__AURORA_DEFINITIONS_H__