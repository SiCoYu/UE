#ifndef __TableItemBase_H_
#define __TableItemBase_H_

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
	std::string m_prefab;

	virtual void parseBodyByteArray(ByteBuffer* bytes, uint32 offset);
};

#endif