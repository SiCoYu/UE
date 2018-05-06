#ifndef __NetDispatchList_H
#define __NetDispatchList_H

#include <vector>

class NetDispatchHandle;
class ByteBuffer;

class NetDispatchList
{
protected:
    int mRevMsgCnt;      // 接收到消息的数量
    int mHandleMsgCnt;   // 处理的消息的数量

    std::vector<NetDispatchHandle*> mNetDispList;
    bool mIsStopNetHandle;       // 是否停止网络消息处理

public:
	NetDispatchList();
	~NetDispatchList();

public:
	void init();
	void dispose();

	bool getBStopNetHandle();
	void setBStopNetHandle(bool value);

	void addOneDispatch(NetDispatchHandle* disp);
	void removeOneDispatch(NetDispatchHandle* disp);
	void handleMsg(ByteBuffer* msg);
	void addOneRevMsg();

	void addOneHandleMsg();
	void clearOneRevMsg();
	void clearOneHandleMsg();
};

#endif