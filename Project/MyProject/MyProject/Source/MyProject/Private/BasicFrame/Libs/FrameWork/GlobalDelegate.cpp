#include "MyProject.h"
#include "GlobalDelegate.h"
#include "AddOnceEventDispatch.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

GlobalDelegate::GlobalDelegate()
{
	this->mCoreInitedEventDispatch = MY_NEW AddOnceEventDispatch();
}

void GlobalDelegate::init()
{

}

void GlobalDelegate::dispose()
{

}

MY_END_NAMESPACE