/*************************************************

Copyright:Lemon Mindy

File:mod_RM_Registration.h

Author:Mindy

Date:2022-3-8

Description:RM_Svr underlying registration module

Brief:Contains the underlying registration model for RM_Svr

**************************************************/
#ifndef RM_REGISTRATION_H
#define RM_REGISTRATION_H
#include "RM_Svr_globaldef.h"
namespace Rose_Mindy
{
    class Middleware
    {
    public:
        // 回调函数注册
        int registration(std::string funcName, long func);

        // 取出回调函数
        int getFunctionHandle(std::string funcName, long& func);

        // 返回注册池
        std::map<std::string, long> getFuncPool()
        {
            return map;
        }

    private:
        // 私有函数指针池
        std::map<std::string, long> map;
    };
}
#endif // !RM_REGISTRATION_H