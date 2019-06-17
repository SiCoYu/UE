#include "MyProject.h"
#include "TableItemBase.h"
#include "MByteBuffer.h"
#include "TableItemHeader.h"

MY_BEGIN_NAMESPACE(MyNS)

TableItemBase::TableItemBase()
	: mItemHeader(nullptr), mItemBody(nullptr)
{

}

void TableItemBase::parseHeaderByteBuffer(MByteBuffer* bytes)
{
    if (nullptr == mItemHeader)
    {
		this->mItemHeader = MY_NEW TableItemHeader();
    }

	this->mItemHeader->parseHeaderByteBuffer(bytes);
}

MY_END_NAMESPACE