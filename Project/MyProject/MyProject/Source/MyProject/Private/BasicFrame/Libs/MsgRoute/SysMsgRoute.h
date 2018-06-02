#ifndef __SysMsgRoute_H
#define __SysMsgRoute_H

#include "MsgRouteBase.h"
#include "MLockQueue.h"
#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 系统消息流程，整个系统的消息分发都走这里，仅限单线程
 */
class SysMsgRoute : MLockQueue<MsgRouteBase>
{
public:
	SysMsgRoute(std::string name);
};

MY_END_NAMESPACE

#endif