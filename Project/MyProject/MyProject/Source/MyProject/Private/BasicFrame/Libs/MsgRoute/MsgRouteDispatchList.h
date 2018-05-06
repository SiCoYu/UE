#ifndef __MsgRouteDispatchList_H
#define __MsgRouteDispatchList_H

#include "MList.h"

class MsgRouteDispHandle;
class MsgRouteBase;

class MsgRouteDispatchList
{
protected:
	MList<MsgRouteDispHandle*> mDispList;

public:
	void addOneDispatch(MsgRouteDispHandle* disp);
	void removeOneDispatch(MsgRouteDispHandle* disp);
	void handleMsg(MsgRouteBase* msg);
};

#endif