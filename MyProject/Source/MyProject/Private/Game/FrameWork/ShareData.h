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
	std::string m_tmpStr;		// 临时字符串缓冲区
    ByteBuffer* m_tmpBA;		// 消息缓冲区

public:
	ShareData();
	~ShareData();
};

#endif