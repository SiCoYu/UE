#pragma once

#include "MsgRouteBase.h"
#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

// 线程日志
class ThreadLogMR : public MsgRouteBase
{
public:
	std::string m_logSys;

public:
	ThreadLogMR();
	virtual ~ThreadLogMR();
};

MY_END_NAMESPACE