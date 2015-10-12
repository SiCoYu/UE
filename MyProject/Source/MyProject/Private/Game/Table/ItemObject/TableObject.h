#ifndef __TableObject_H_
#define __TableObject_H_

#include <string>
#include "HAL/Platform.h"
#include "TableItemBodyBase.h"

class TableObjectItemBody : TableItemBodyBase
{
public:
    std::string m_name;
    int m_maxNum;
    int m_type;
    int m_color;
	std::string m_objResName;

	virtual void parseBodyByteBuffer(ByteBuffer* bytes, uint32 offset);
};

#endif