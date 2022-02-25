/*************************************************

Copyright:Lemon Mindy

File:RM_Svr_protocol.h

Author:Mindy

Date:2022-2-23

Description:RM_Svr Development diary By C++

Brief:Contains protocol components and protocol components for RM_Svr

**************************************************/

#ifndef _RM_SVR_PROTOCOL_H_
#define _RM_SVR_PROTOCOL_H_
#include "RM_Svr_include.h"

/// @brief namespace of RM_Svr
namespace Rose_Mindy
{
	///////////////////////////////////////////
	// Underlying data type definitions
	///////////////////////////////////////////
	typedef unsigned char RM_U8;
	typedef unsigned short RM_U16;
	typedef unsigned int RM_U32;
	typedef unsigned long RM_U64;

	typedef signed char RM_S8;
	typedef signed short RM_S16;
	typedef signed int RM_S32;
	typedef signed long long RM_S64;

	typedef char RM_CHAR;
	typedef float RM_FLOAT;
	typedef double RM_DOUBLE;
	typedef void RM_VOID;
	typedef void* RM_HANDLE;
	typedef std::string RM_STRING;

	typedef enum RM_BOOL
	{
		RM_TRUE = 1,
		RM_FALSE = 0
	}RM_BOOL;

	#define RM_SUCCESS	1
	#define RM_FAILURE	0

	///////////////////////////////////////////
	// Basic log definitions
	///////////////////////////////////////////
	typedef enum RM_LOG_LEVEL
	{
		LOG_INFO = 1,
		LOG_ERROR,
		LOG_FATAL,
		LOG_WARN,
	}RM_LOG_LEVEL;

	// Log contents
	typedef struct RM_LOG_PARAMS
	{
		RM_STRING time;
		RM_STRING file;
		RM_STRING line;
		RM_STRING type;
		RM_S64 errorn;
		RM_STRING contain;
	};

	///////////////////////////////////////////
	// Communication Protocol Definition
	///////////////////////////////////////////
	
	// dhcp
	struct DHCPPacketHeader
	{
		RM_U8 op;
		RM_U8 htype;
		RM_U8 hlen;
		RM_U8 hops;

		RM_U32 xid;

		RM_U16 secs;
		RM_U16 flags;

		RM_U32 ciaddr;
		RM_U32 yiaddr;
		RM_U32 siaddr;
		RM_U32 giaddr;
		RM_U8 chaddr[16];

		RM_S8 sname[64];
		RM_S8 file[128];

		RM_U32 magic;

		bool IsValid() const
		{
			//return magic == qToBigEndian(0x63825363U);
		};
	};

	// tftp

	// ftp

	// http

	// rmp
}
#endif // !_RM_SVR_PROTOCOL_H_
