#ifndef __NetDispList_H
#define __NetDispList_H

#include <vector>

class NetDispHandle;
class ByteBuffer;

class NetDispList
{
protected:
    int mRevMsgCnt;      // 接收到消息的数量
    int mHandleMsgCnt;   // 处理的消息的数量

    std::vector<NetDispHandle*> mNetDispList;
    bool mIsStopNetHandle;       // 是否停止网络消息处理

public:
	NetDispList();
	~NetDispList();

public:
	void init();
	void dispose();

	bool getBStopNetHandle();
	void setBStopNetHandle(bool value);

	void addOneDisp(NetDispHandle* disp);
	void removeOneDisp(NetDispHandle* disp);
	void handleMsg(ByteBuffer* msg);
	void addOneRevMsg();

	void addOneHandleMsg();
	void clearOneRevMsg();
	void clearOneHandleMsg();
};

#endif