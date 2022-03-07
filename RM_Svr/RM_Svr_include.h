/*************************************************

Copyright:Lemon Mindy

File:RM_Svr_protocol.h

Author:Mindy

Date:2022-2-23

Description:RM_Svr Development diary By C++

Brief:Contains RM_Svr header files

**************************************************/
#include <iostream>
#include <cstdio>
#include <xstring>
#include <vector>
#include <tuple>
#include <map>

#ifdef RM_Application_Layer
namespace Rose_Mindy
{
    // 应用层基类
    class RObject
    {
    public:
        RObject() {};
        ~RObject() {};

    public:
        virtual int ProcessCtrl() = 0;
    };
}
#endif // RM_Application_Layer

class RObject;
    // 函数指针
typedef int (RObject::* NONSTATICFUNCPTR)();
