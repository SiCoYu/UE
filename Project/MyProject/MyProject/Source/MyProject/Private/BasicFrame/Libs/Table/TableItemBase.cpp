#include "MyProject.h"
#include "TableItemBase.h"
#include "ByteBuffer.h"
#include "TableItemHeader.h"

TableItemBase::TableItemBase()
	: mItemHeader(nullptr), mItemBody(nullptr)
{

}

void TableItemBase::parseHeaderByteBuffer(ByteBuffer* bytes)
{
    if (nullptr == mItemHeader)
    {
		this->mItemHeader = new TableItemHeader();
    }

	this->mItemHeader->parseHeaderByteBuffer(bytes);
}