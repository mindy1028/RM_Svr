#include "mod_RM_Registration.h"

int Rose_Mindy::Middleware::registration(std::string funcName, long func)
{
    map.insert(make_pair(funcName, func));

    try
    {
        std::map<std::string, long>::iterator it = map.find(funcName);
        if (it->second != func)
            return -1;

        return 0;
    }
    catch (const std::exception&)
    {
        return -1;
    }
}

int Rose_Mindy::Middleware::getFunctionHandle(std::string funcName, long& func)
{
    try
    {
        std::map<std::string, long>::iterator it = map.find(funcName);

        if (it != map.end())
        {
            func = it->second;
            return 0;
        }

        return -1;
    }
    catch (const std::exception&)
    {
        return -1;
    }
}
