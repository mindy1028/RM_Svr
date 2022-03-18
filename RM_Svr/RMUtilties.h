/*************************************************

Copyright:Lemon Mindy

File:RMUtilties.h

Author:Mindy

Date:2022-3-19

Description:RM_Svr base tools file

Brief:Contains RM_Svr low-level function-tools

**************************************************/
#ifndef RMUTILTIES_H
#define RMUTILTIES_H

#include "RM_Svr_globaldef.h"
namespace Rose_Mindy {
	RM_U128 _get_random()
	{
		std::random_device rd;
		std::default_random_engine generator(rd());
		std::uniform_int_distribution<long long unsigned> distribution(0, 0xFFFFFFFFFFFFFFFF);
		return distribution(generator);
	}
}

#endif // !RMUTILTIES_H
