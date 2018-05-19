#pragma once

#include "MsgRouteBase.h"
#include <string>

// 线程日志
class ThreadLogMR : public MsgRouteBase
{
public:
	std::string m_logSys;

public:
	ThreadLogMR();
	virtual ~ThreadLogMR();
};