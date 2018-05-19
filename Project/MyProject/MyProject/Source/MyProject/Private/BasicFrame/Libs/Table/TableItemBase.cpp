#include "MyProject.h"
#include "TableItemBase.h"
#include "MByteBuffer.h"
#include "TableItemHeader.h"

TableItemBase::TableItemBase()
	: mItemHeader(nullptr), mItemBody(nullptr)
{

}

void TableItemBase::parseHeaderByteBuffer(MByteBuffer* bytes)
{
    if (nullptr == mItemHeader)
    {
		this->mItemHeader = new TableItemHeader();
    }

	this->mItemHeader->parseHeaderByteBuffer(bytes);
}