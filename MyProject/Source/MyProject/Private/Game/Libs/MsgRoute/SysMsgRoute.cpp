#include "MyProject.h"
#include "SysMsgRoute.h"
#include "MsgRouteBase.h"

SysMsgRoute::SysMsgRoute(std::string name)
	: LockQueue<MsgRouteBase>(name)
{

}