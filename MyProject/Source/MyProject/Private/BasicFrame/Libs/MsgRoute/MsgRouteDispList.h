﻿#ifndef __MsgRouteDispList_H
#define __MsgRouteDispList_H

#include "MList.h"

class MsgRouteDispHandle;
class MsgRouteBase;

class MsgRouteDispList
{
protected:
	MList<MsgRouteDispHandle*> mDispList;

public:
	void addOneDisp(MsgRouteDispHandle* disp);
	void removeOneDisp(MsgRouteDispHandle* disp);
	void handleMsg(MsgRouteBase* msg);
};

#endif