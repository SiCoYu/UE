#include "MyProject.h"
#include "UtilTable.h"
#include "ByteBuffer.h"
#include "MEncode.h"

uint32 UtilTable::m_prePos = 0;        // 记录之前的位置
uint16 UtilTable::m_sCnt = 0;

void UtilTable::readString(ByteBuffer* bytes, std::string& tmpStr)
{
	bytes->readUnsignedInt16(m_sCnt);
	bytes->readMultiByte(tmpStr, m_sCnt, eUTF8);
}