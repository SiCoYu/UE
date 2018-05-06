#ifndef __MsgRouteDispatchList_H
#define __MsgRouteDispatchList_H

#include "MList.h"

class MsgRouteDispatchHandle;
class MsgRouteBase;

class MsgRouteDispatchList
{
protected:
	MList<MsgRouteDispatchHandle*> mDispList;

public:
	void addOneDispatch(MsgRouteDispatchHandle* disp);
	void removeOneDispatch(MsgRouteDispatchHandle* disp);
	void handleMsg(MsgRouteBase* msg);
};

#endif