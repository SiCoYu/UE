#include "MyProject.h"
#include "TableBase.h"
#include "ByteBuffer.h"

std::string UtilTable::readString(ByteBuffer* bytes)
{
    m_sCnt = bytes->readUnsignedShort();
    return bytes->readMultiByte(m_sCnt, GkEncode.UTF8);
}