#include "MyProject.h"
#include "RefCount.h"

MY_BEGIN_NAMESPACE(MyNS)

RefCount::RefCount()
{
	this->mRefNum = 0;       // 引用计数从 1 改成 0 
}

uint32 RefCount::getRefNum()
{
	return this->mRefNum;
}
void RefCount::setRefNum(int32 value)
{
	this->mRefNum = value;
}

void RefCount::reset()
{
	this->mRefNum = 0;
}

void RefCount::incRef()
{
	++this->mRefNum;
}

void RefCount::decRef()
{
	--this->mRefNum;
}

bool RefCount::isNoRef()
{
	return this->mRefNum == 0;
}

void RefCount::copyFrom(RefCount* rhv)
{
	this->mRefNum = rhv->getRefNum();
}

MY_END_NAMESPACE