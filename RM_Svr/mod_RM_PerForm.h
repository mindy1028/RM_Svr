/*************************************************

Copyright:Lemon Mindy

File:mod_RM_PerForm.h

Author:Mindy

Date:2022-3-8

Description:RM_Svr function execution module

Brief:Contains RM_Svr low-level execution

**************************************************/

#ifndef RM_PERFORM_H
#define RM_PERFORM_H
#include "RM_Svr_globaldef.h"
#include "mod_RM_Registration.h"

namespace Rose_Mindy
{
    class perForm
    {
        perForm();

        //static perForm* _instance;
    public:
        //int getPerform(std::string funcName, void* handle, NONSTATICFUNCPTR funcPtr);
    private:
        Middleware* middleware;
    };
}
#endif // !RM_PERFORM_H
