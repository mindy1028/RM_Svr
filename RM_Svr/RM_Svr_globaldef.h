/*************************************************

Copyright:Lemon Mindy

File:RM_Svr_protocol.h

Author:Mindy

Date:2022-2-23

Description:RM_Svr Development diary By C++

Brief:Contains RM_Svr toolbox file

**************************************************/

#ifndef _RM_SVR_GLOBALDEF_H_
#define _RM_SVR_GLOBALDEF_H_
// 不要在以下任何内联代码中使用“new”或“delete”(不包括模板)
// 这样我们就可以避免那些分配被ToolBoxDebug跟踪

#include <windows.h>
#include <TCHAR.h>
// 有些环境没有ASSERT .h文件，但是有一个ASSERT(…)宏定义
#if defined(ASSERT)
#define assert(e) ASSERT(e)
#else  // defined(ASSERT)
#include <assert.h>
#define ASSERT(e) assert(e)
#endif  // defined(ASSERT)

// C_ASSERT()可以用来执行许多编译时断言:类型大小，字段偏移量，等等(来自vc++的WinNT.h)
#if !defined(C_ASSERT)
#define C_ASSERT(e) typedef char __C_ASSERT__[(e)?1:-1]
// 断言失败导致错误C2118:负下标。
#endif // !defined(C_ASSERT)

// 为所有环境提供验证宏
#if !defined(VERIFY)
#if defined(DEBUG) || defined(_DEBUG)
#define VERIFY(e) ASSERT(e)
#else  // defined(DEBUG) || defined(_DEBUG)
#define VERIFY(e) ((void)(e))
#endif  // defined(DEBUG) || defined(_DEBUG)
#endif  // !defined(VERIFY)

// 宏，用于简化确定数组中的元素数量(不要* *将该宏用于指针)
#define ARRAY_LENGTH(x) (sizeof(x)/sizeof((x)[0]))

#define OUTPUT(x) printf x; printf(ptsCRLF)
#define OUTPUT_ERROR(x) printf(ptsERRORPrefix, __LINE__); printf x; printf(ptsCRLF);
#define OUTPUT_WARNING(x) ASSERT(!x)
#define DWIP0(dw) (((dw)>> 0) & 0xff)
#define DWIP1(dw) (((dw)>> 8) & 0xff)
#define DWIP2(dw) (((dw)>>16) & 0xff)
#define DWIP3(dw) (((dw)>>24) & 0xff)
#define DWIPtoValue(dw) ((DWIP0(dw)<<24) | (DWIP1(dw)<<16) | (DWIP2(dw)<<8) | DWIP3(dw))
#define DWValuetoIP(dw) ((DWIP0(dw)<<24) | (DWIP1(dw)<<16) | (DWIP2(dw)<<8) | DWIP3(dw))
#endif // !_RM_SVR_GLOBALDEF_H_