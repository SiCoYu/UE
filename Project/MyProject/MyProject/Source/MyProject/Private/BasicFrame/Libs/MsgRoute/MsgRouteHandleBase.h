#ifndef __MsgRouteHandleBase_H
#define __MsgRouteHandleBase_H

#include "MDcitionary.h"
#include "MsgRouteDelegate.h"
#include "MsgRouteBase.h"
#include "EventDispatchDelegate.h"

class MsgRouteBase;

class MsgRouteHandleBase
{
public:
	MDcitionary<int, MsgRouteDelegate> mId2HandleDic;

public:
	MsgRouteHandleBase();
	// warning C4265: 'MsgRouteHandleBase': class has virtual functions, but destructor is not virtual
	virtual ~MsgRouteHandleBase();

	void addMsgRouteHandle(MsgRouteId msgRouteId, EventDispatchDelegate handle);
	void removeMsgRouteHandle(MsgRouteId msgRouteId, EventDispatchDelegate handle);
	virtual void handleMsg(IDispatchObject dispObj, uint uniqueId);
};

#endif