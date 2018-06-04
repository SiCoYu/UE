#include "MyProject.h"
#include "TickMgr.h"
#include "ITickedObject.h"
#include "TickProcessObject.h"
#include "MClassFactory.h"
#include "IDelayHandleItem.h"
#include "MacroDef.h"
#include "Ctx.h"
#include "LogSys.h"
#include "LogTypeId.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(TickMgr, TickObjectPriorityMgr)

TickMgr::TickMgr()
{

}

TickMgr::~TickMgr()
{

}

void TickMgr::init()
{
	Super::init();
}

void TickMgr::dispose()
{
	Super::dispose();
}

void TickMgr::addTick(ITickedObject* tickObj, float priority)
{
	this->_addObject((IDelayHandleItem*)tickObj, priority);
}

void TickMgr::removeTick(ITickedObject* tickObj)
{
	this->_removeObject((IDelayHandleItem*)tickObj);
}

void TickMgr::advance(float delta, TickMode tickMode)
{
	Super::advance(delta, tickMode);
}

MY_END_NAMESPACE