#include "MyProject.h"
#include "SysMsgRoute.h"

SysMsgRoute::SysMsgRoute(std::string name)
	: LockQueue<MsgRouteBase>(name)
{

}