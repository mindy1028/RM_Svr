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
        // �ص�����ע��
        int registration(std::string funcName, long func);

        // ȡ���ص�����
        int getFunctionHandle(std::string funcName, long& func);

        // ����ע���
        std::map<std::string, long> getFuncPool()
        {
            return map;
        }

    private:
        // ˽�к���ָ���
        std::map<std::string, long> map;
    };
}
#endif // !RM_REGISTRATION_H