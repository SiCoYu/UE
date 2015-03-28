#include "MyProject.h"
#include "TableCard.h"

override public void TableSkillItemBody::parseBodyByteArray(ByteArray bytes, uint offset)
{
    (bytes as ByteArray).position = offset;
    m_name = UtilTable.readString(bytes as ByteArray);
    m_effect = UtilTable.readString(bytes as ByteArray);
    m_desc = UtilTable.readString(bytes as ByteArray);
}