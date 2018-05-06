#ifndef __MsgRouteBase_H
#define __MsgRouteBase_H

enum MsgRouteType
{
	eMRT_BASIC,      // 基本类型
};

enum MsgRouteID
{
	eMRIDSocketOpened,      // socket Opened
	eMRIDSocketClosed,      // socket Opened
	eMRIDLoadedWebRes,      // web 资源加载完成
	eMRIDThreadLog,      // 线程打日志
};

#include "IRecycle.h"

class MsgRouteBase : public IRecycle
{
public:
	MsgRouteType mMsgType;
    MsgRouteID mMsgId;          // 只需要一个 ID 就行了

public:
	MsgRouteBase();
	MsgRouteBase(MsgRouteID id);
	virtual void resetDefault();
};

#endif