#pragma once

#include "MsgRouteBase.h"
#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

// �߳���־
class ThreadLogMR : public MsgRouteBase
{
public:
	std::string m_logSys;

public:
	ThreadLogMR();
	virtual ~ThreadLogMR();
};

MY_END_NAMESPACE