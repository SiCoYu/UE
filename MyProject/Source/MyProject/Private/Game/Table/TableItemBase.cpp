#include "MyProject.h"
#include "TableItemBase.h"
#include "ByteBuffer.h"

void TableItemBase::parseHeaderByteArray(ByteBuffer* bytes)
{
    if (null == m_itemHeader)
    {
        m_itemHeader = new TableItemHeader();
    }
    m_itemHeader.parseHeaderByteArray(bytes);
}