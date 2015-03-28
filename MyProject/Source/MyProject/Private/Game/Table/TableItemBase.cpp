#include "MyProject.h"
#include "TableItemBase.h"

void TableItemBase::parseHeaderByteArray(ByteArray* bytes)
{
    if (null == m_itemHeader)
    {
        m_itemHeader = new TableItemHeader();
    }
    m_itemHeader.parseHeaderByteArray(bytes);
}