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

#ifndef _AURORA_EXCLUDE_WINDEFS

#if defined(_M_IX86)
#define _X86_
#elif defined(_M_AMD64)
#define _AMD64_
#else
#error No target architecture!
#endif

#include <minwindef.h>

#endif // !AURORA_EXCLUDE_WINDEFS

#define AURORA_EXPORT __declspec(dllexport)
#define AURORA_IMPORT __declspec(dllimport)

#ifdef _AURORA_EXPORT
#define AURORA_API AURORA_EXPORT
#else
#define AURORA_API AURORA_IMPORT
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif // !MAX_PATH

#ifndef MAX_NAME
#define MAX_NAME 128
#endif // !MAX_NAME

#ifndef MAX_MSG
#define MAX_MSG 256
#endif // !MAX_MSG

#ifndef MAX_INVOKE
#define MAX_INVOKE 64
#endif // !MAX_INVOKE

typedef char A_CHAR;
typedef char* A_LPCHAR;
typedef char* A_LPSTR;
typedef const char* A_LPCSTR;

typedef wchar_t A_WCHAR;
typedef wchar_t* A_LPWCHAR;
typedef wchar_t* A_LPWSTR;
typedef const wchar_t* A_LPCWSTR;

typedef void* A_LPVOID;
typedef const void* A_LPCVOID;

typedef bool A_BOOL;
typedef bool* A_LPBOOL;

typedef signed __int8 A_I8;
typedef signed __int16 A_I16;
typedef signed __int32 A_I32;
typedef signed __int64 A_I64;

typedef unsigned __int8 A_U8;
typedef unsigned __int16 A_U16;
typedef unsigned __int32 A_U32;
typedef unsigned __int64 A_U64;

#endif // !__AURORA_DEFINITIONS_H__