#ifndef __ShareData_H
#define __ShareData_H

#include <string>

class ByteBuffer;

/**
 * @brief 共享内容，主要是数据
 */
class ShareData
{
public:
	std::string mTmpStr;		// 临时字符串缓冲区
    ByteBuffer* mTmpBA;		// 消息缓冲区

public:
	ShareData();
	~ShareData();

public:
	void init();
	void dispose();
};

#endif