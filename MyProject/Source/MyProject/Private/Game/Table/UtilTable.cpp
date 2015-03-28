#include "MyProject.h"
#include "UtilTable.h"
#include "ByteBuffer.h"
#include "MEncode.h"

std::string UtilTable::readString(ByteBuffer* bytes)
{
	bytes->readUnsignedInt16(m_sCnt);
	bytes->readMultiByte(m_retStr, m_sCnt, MEncode::eUTF8);
	return m_retStr;
}