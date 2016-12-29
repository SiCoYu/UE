#include "MyProject.h"
#include "RefCount.h"

RefCount::RefCount()
{
	mRefNum = 0;       // 引用计数从 1 改成 0 
}

uint32 RefCount::getRefNum()
{
	return mRefNum;
}
void RefCount::setRefNum(int32 value)
{
	mRefNum = value;
}

void RefCount::reset()
{
	mRefNum = 0;
}

void RefCount::incRef()
{
	++mRefNum;
}

void RefCount::decRef()
{
	--mRefNum;
}

bool RefCount::isNoRef()
{
	return mRefNum == 0;
}

void RefCount::copyFrom(RefCount* rhv)
{
	mRefNum = rhv->getRefNum();
}