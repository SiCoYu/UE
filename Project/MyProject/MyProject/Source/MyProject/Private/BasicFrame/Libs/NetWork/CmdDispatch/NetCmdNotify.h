#ifndef __NetCmdNotify_H
#define __NetCmdNotify_H

#include <vector>
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class NetModuleDispatchHandle;
class MByteBuffer;
class CmdDispatchInfo;

class NetCmdNotify : public GObject
{
protected:
    int mRevMsgCnt;      // 接收到消息的数量
    int mHandleMsgCnt;   // 处理的消息的数量

    std::vector<NetModuleDispatchHandle*> mNetDispatchList;
    bool mIsStopNetHandle;       // 是否停止网络消息处理
	CmdDispatchInfo* mCmdDispInfo;

public:
	NetCmdNotify();
	~NetCmdNotify();

public:
	void init();
	void dispose();

	bool getBStopNetHandle();
	void setBStopNetHandle(bool value);

	void addOneNofity(NetModuleDispatchHandle* disp);
	void removeOneNotify(NetModuleDispatchHandle* disp);
	void handleMsg(MByteBuffer* msg);
	void addOneRevMsg();

	void addOneHandleMsg();
	void clearOneRevMsg();
	void clearOneHandleMsg();
};

MY_END_NAMESPACE

#endif