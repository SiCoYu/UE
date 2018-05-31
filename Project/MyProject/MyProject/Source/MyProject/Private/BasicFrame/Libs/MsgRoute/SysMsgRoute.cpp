#include "MyProject.h"
#include "SysMsgRoute.h"

MY_BEGIN_NAMESPACE(MyNS)

SysMsgRoute::SysMsgRoute(std::string name)
	: LockQueue<MsgRouteBase>(name)
{

}

MY_END_NAMESPACE