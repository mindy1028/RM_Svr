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
	typedef long long unsigned RM_U128;

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
	struct RM_LOG_PARAMS
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

		RM_U64 xid;

		RM_U16 secs;
		RM_U16 flags;

		RM_U64 ciaddr;
		RM_U64 yiaddr;
		RM_U64 siaddr;
		RM_U64 giaddr;
		RM_U8 chaddr[16];

		RM_U8 sname[64];
		RM_U8 file[128];

		RM_U8 options[2048];
	};

	struct DHCPServerOptions
	{
		RM_U8 pbMagicCookie[4];
		RM_U8 pbMessageType[3];
		RM_U8 pbLeaseTime[6];
		RM_U8 pbSubnetMask[6];
		RM_U8 pbServerID[6];
		RM_U8 bEND;
	};
	// tftp

	// ftp

	// http

	// rmp
}
#endif // !_RM_SVR_PROTOCOL_H_
