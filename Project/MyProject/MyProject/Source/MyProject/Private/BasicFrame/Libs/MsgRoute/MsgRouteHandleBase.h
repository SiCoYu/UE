#ifndef __MsgRouteHandleBase_H
#define __MsgRouteHandleBase_H

#include "MDictionary.h"
#include "MsgRouteDelegate.h"
#include "MsgRouteBase.h"
#include "EventDispatchDelegate.h"

class AddOnceEventDispatch;

class MsgRouteHandleBase
{
public:
	MDictionary<int, AddOnceEventDispatch*> mId2HandleDic;

public:
	MsgRouteHandleBase();
	// warning C4265: 'MsgRouteHandleBase': class has virtual functions, but destructor is not virtual
	virtual ~MsgRouteHandleBase();

	virtual public void init();
	virtual public void dispose();

	void addMsgRouteHandle(MsgRouteId msgRouteId, EventDispatchDelegate handle);
	void removeMsgRouteHandle(MsgRouteId msgRouteId, EventDispatchDelegate handle);
	virtual void handleMsg(IDispatchObject* dispObj, uint uniqueId);
};

#endif