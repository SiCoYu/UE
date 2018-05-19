#pragma once

#include "MsgRouteBase.h"
#include <string>

class LoadedWebResMR : MsgRouteBase
{
	//public ITask m_task;

public:
	LoadedWebResMR();
	virtual void resetDefault() override;
};