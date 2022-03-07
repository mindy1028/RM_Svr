#ifndef DEMO_H
#define DEMO_H
#define RM_Application_Layer
#include "RM_Svr_globaldef.h"
#include "RM_Svr_include.h"

class RObject;
namespace Rose_Mindy
{
	class Demo : public RObject
	{
	public:
		int ProcessCtrl() { return 100; }
	};
}
#endif
