#include "MyProject.h"
#include "IndexItemBase.h"

MY_BEGIN_NAMESPACE(MyNS)

IndexItemBase::IndexItemBase()
{
	this->mIndex = -1;
}

void IndexItemBase::init()
{

}

void IndexItemBase::dispose()
{

}

int IndexItemBase::getIndex()
{
	return this->mIndex;
}

void IndexItemBase::setIndex(int value)
{
	this->mIndex = value;
}

void IndexItemBase::resetIndex()
{
	this->mIndex = -1;
}
	
MY_END_NAMESPACE