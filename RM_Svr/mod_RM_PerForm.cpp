#include "mod_RM_PerForm.h"

Rose_Mindy::perForm::perForm()
{
    middleware = new Middleware();
}

//int Rose_Mindy::perForm::getPerform(std::string funcName, void* handle, NONSTATICFUNCPTR funcPtr)
//{
//    try
//    {
//        // ��ȡ�������
//        long ptr;
//
//        int ret = middleware->getFunctionHandle(funcName, ptr);
//        if (0 != ret)
//        {
//            return -1;
//        }
//
//        // ���ûص�����
//        //((FUNC)ptr)();
//        return ((RObject*)handle->*funcPtr)();
//    }
//    catch (const std::exception&)
//    {
//        return -1;
//    }
//}
