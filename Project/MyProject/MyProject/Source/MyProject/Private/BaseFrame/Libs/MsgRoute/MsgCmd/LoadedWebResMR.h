#pragma once

#include "MsgRouteBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class LoadedWebResMR : MsgRouteBase
{
	//public ITask m_task;

public:
	LoadedWebResMR();
	virtual void resetDefault() override;
};

MY_END_NAMESPACE