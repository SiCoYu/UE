#ifndef __MsgRouteBase_H
#define __MsgRouteBase_H

enum class MsgRouteType
{
	eMRT_BASIC,      // 基本类型
};

enum class MsgRouteId
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
    MsgRouteId mMsgId;          // 只需要一个 Id 就行了

public:
	MsgRouteBase();
	MsgRouteBase(MsgRouteId id);
	virtual void resetDefault();
};

#endif