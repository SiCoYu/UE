#include "MyProject.h"
#include "TableItemBase.h"
#include "ByteBuffer.h"
#include "TableItemHeader.h"

void TableItemBase::parseHeaderByteArray(ByteBuffer* bytes)
{
    if (nullptr == m_itemHeader)
    {
        m_itemHeader = new TableItemHeader;
    }
    m_itemHeader->parseHeaderByteArray(bytes);
}