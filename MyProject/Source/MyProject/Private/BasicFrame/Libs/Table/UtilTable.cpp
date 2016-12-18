#include "MyProject.h"
#include "UtilTable.h"
#include "ByteBuffer.h"
#include "MEncode.h"

uint32 UtilTable::mPrePos = 0;        // 记录之前的位置
uint16 UtilTable::msCnt = 0;

void UtilTable::readString(ByteBuffer* bytes, std::string& tmpStr)
{
	bytes->readUnsignedInt16(msCnt);
	bytes->readMultiByte(tmpStr, msCnt, eUTF8);
}