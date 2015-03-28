#ifndef __UtilTable_H_
#define __UtilTable_H_

#include "MyProject.h"
#include "string"

class ByteBuffer;

class UtilTable
{
public:
    static uint32 m_prePos;        // 记录之前的位置
    static uint16 m_sCnt;
	static std::string m_retStr;
	static std::string readString(ByteBuffer* bytes);
};

#endif