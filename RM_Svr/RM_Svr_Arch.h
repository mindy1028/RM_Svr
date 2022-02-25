/*************************************************

Copyright:Lemon Mindy

File:RM_Svr_protocol.h

Author:Mindy

Date:2022-2-23

Description:RM_Svr Development diary By C++

Brief:Contains a description of the RM_Svr architecture

**************************************************/


/*************************************************

The software architecture realizes database API encapsulation, communication(Tcp, Http, Udp)
and other extensible module combinations, of course, including separate log module encapsulation;
All modules can be loaded through the master module(master) selection, and provide external
interface for UI call, the software not only includes the underlying architecture but also
	includes the external support interface to the three - party framework such as Cocox;
From the language point of view, the software provides an interface to support pythonand PHP.
Most importantly, it will fulfill my current dream of creating a highly extensible Web server that supports
dynamic data changesand server - side Bridges for a wide variety of clients.

																		------Created 2022-2-23

**************************************************/