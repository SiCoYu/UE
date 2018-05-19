#ifndef __MsgRoute_H
#define __MsgRoute_H

#include "MsgRouteBase.h"
#include <string>

class SocketOpenedMR : public MsgRouteBase
{
public:
	SocketOpenedMR();
};

class SocketCloseedMR : public MsgRouteBase
{
public:
	SocketCloseedMR();
};

class LoadedWebResMR : MsgRouteBase
{
    //public ITask m_task;

public:
	LoadedWebResMR();
	virtual void resetDefault() override;
};

// 线程日志
class ThreadLogMR : public MsgRouteBase
{
public:
	std::string m_logSys;

public:
	ThreadLogMR();
	virtual ~ThreadLogMR();
};

#endif