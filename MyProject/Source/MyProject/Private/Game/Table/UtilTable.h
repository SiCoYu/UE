#ifndef __TableItemBase_H_
#define __TableItemBase_H_

#include "MyProject.h"
#include "string"

class ByteBuffer;

class UtilTable
{
public:
    static uint32 m_prePos;        // 记录之前的位置
    static uint32 m_sCnt;
	static std::string readString(ByteBuffer* bytes);
};

#endif