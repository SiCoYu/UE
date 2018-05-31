#pragma once

#include "MsgRouteBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SocketClosedMR : public MsgRouteBase
{
public:
	SocketClosedMR();
};

MY_END_NAMESPACE