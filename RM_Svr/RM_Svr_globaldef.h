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
// ��Ҫ�������κ�����������ʹ�á�new����delete��(������ģ��)
// �������ǾͿ��Ա�����Щ���䱻ToolBoxDebug����

#include <windows.h>
#include <TCHAR.h>
// ��Щ����û��ASSERT .h�ļ���������һ��ASSERT(��)�궨��
#if defined(ASSERT)
#define assert(e) ASSERT(e)
#else  // defined(ASSERT)
#include <assert.h>
#define ASSERT(e) assert(e)
#endif  // defined(ASSERT)

// C_ASSERT()��������ִ��������ʱ����:���ʹ�С���ֶ�ƫ�������ȵ�(����vc++��WinNT.h)
#if !defined(C_ASSERT)
#define C_ASSERT(e) typedef char __C_ASSERT__[(e)?1:-1]
// ����ʧ�ܵ��´���C2118:���±ꡣ
#endif // !defined(C_ASSERT)

// Ϊ���л����ṩ��֤��
#if !defined(VERIFY)
#if defined(DEBUG) || defined(_DEBUG)
#define VERIFY(e) ASSERT(e)
#else  // defined(DEBUG) || defined(_DEBUG)
#define VERIFY(e) ((void)(e))
#endif  // defined(DEBUG) || defined(_DEBUG)
#endif  // !defined(VERIFY)

// �꣬���ڼ�ȷ�������е�Ԫ������(��Ҫ* *���ú�����ָ��)
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