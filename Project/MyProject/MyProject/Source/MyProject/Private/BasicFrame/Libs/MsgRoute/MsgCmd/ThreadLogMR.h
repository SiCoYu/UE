#pragma once

#include "MsgRouteBase.h"
#include <string>

// �߳���־
class ThreadLogMR : public MsgRouteBase
{
public:
	std::string m_logSys;

public:
	ThreadLogMR();
	virtual ~ThreadLogMR();
};