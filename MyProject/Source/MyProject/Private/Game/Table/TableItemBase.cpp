#include "MyProject.h"
#include "TableItemBase.h"
#include "ByteBuffer.h"
#include "TableItemHeader.h"

TableItemBase::TableItemBase()
	: m_itemHeader(nullptr), m_itemBody(nullptr)
{

}

void TableItemBase::parseHeaderByteBuffer(ByteBuffer* bytes)
{
    if (nullptr == m_itemHeader)
    {
        m_itemHeader = new TableItemHeader();
    }
    m_itemHeader->parseHeaderByteBuffer(bytes);
}