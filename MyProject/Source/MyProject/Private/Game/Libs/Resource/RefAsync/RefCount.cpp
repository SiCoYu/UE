#include "MyProject.h"
#include "RefCount.h"

RefCount::RefCount()
{
	m_refNum = 0;       // 引用计数从 1 改成 0 
}

uint32 RefCount::getRefNum()
{
	return m_refNum;
}
void RefCount::setRefNum(int32 value)
{
	m_refNum = value;
}

void RefCount::reset()
{
	m_refNum = 0;
}

void RefCount::incRef()
{
	++m_refNum;
}

void RefCount::decRef()
{
	--m_refNum;
}

bool RefCount::bNoRef()
{
	return m_refNum == 0;
}

void RefCount::copyFrom(RefCount rhv)
{
	m_refNum = rhv.getRefNum();
}