#ifndef __AURORA_DEFINITIONS_H__
#define __AURORA_DEFINITIONS_H__

#if defined(_M_IX86)
#define _X86_
#elif defined(_M_AMD64)
#define _AMD64_
#else
#error No target architecture!
#endif

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
#define MAX_NAME 64
#endif // !MAX_NAME

#ifndef MAX_MSG
#define MAX_MSG 256
#endif // !MAX_MSG

#ifndef MAX_INVOKE
#define MAX_INVOKE 64
#endif // !MAX_INVOKE

#endif // !__AURORA_DEFINITIONS_H__