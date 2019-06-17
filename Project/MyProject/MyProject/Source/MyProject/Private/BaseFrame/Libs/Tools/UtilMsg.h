#ifndef __UtilMsg_H
#define __UtilMsg_H

#include "Platform.h"		// uint32
#include <string>
#include "NullUserCmd.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 处理消息工具
 */
class UtilMsg
{
public:
	// 发送消息， bnet 如果 true 就直接发送到 socket ，否则直接进入输出消息队列
	static void sendMsg(NullUserCmd& msg, bool bnet = true);
	static void checkStr(std::string str);
	// 格式化消息数据到数组形式
	static void formatBytes2Array(char* bytes, uint32 len);
};

MY_END_NAMESPACE

#endif