#include "mod_RM_PerForm.h"

Rose_Mindy::perForm::perForm()
{
    middleware = new Middleware();
}

//int Rose_Mindy::perForm::getPerform(std::string funcName, void* handle, NONSTATICFUNCPTR funcPtr)
//{
//    try
//    {
//        // 获取函数句柄
//        long ptr;
//
//        int ret = middleware->getFunctionHandle(funcName, ptr);
//        if (0 != ret)
//        {
//            return -1;
//        }
//
//        // 调用回调函数
//        //((FUNC)ptr)();
//        return ((RObject*)handle->*funcPtr)();
//    }
//    catch (const std::exception&)
//    {
//        return -1;
//    }
//}
