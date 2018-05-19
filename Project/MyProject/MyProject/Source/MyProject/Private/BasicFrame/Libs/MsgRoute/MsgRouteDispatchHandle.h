#ifndef __MsgRouteDispatchHandle_H
#define __MsgRouteDispatchHandle_H

#include "EventDispatchGroup.h"
#include "EventDispatchDelegate.h"

class MsgRouteBase;

class MsgRouteDispatchHandle
{
protected:
	EventDispatchGroup mEventDispatchGroup;

public:
	MsgRouteDispatchHandle();
	virtual ~MsgRouteDispatchHandle();

	virtual void init();
	virtual void dispose();

	void addRouteHandle(int groupId, EventDispatchDelegate handle);
	void removeRouteHandle(int groupId, EventDispatchDelegate handle);

	virtual void handleMsg(MsgRouteBase* msg);
};

#endif