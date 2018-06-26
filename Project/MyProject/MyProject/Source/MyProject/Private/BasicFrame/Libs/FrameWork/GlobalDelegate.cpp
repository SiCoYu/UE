#include "MyProject.h"
#include "GlobalDelegate.h"
#include "PromiseEventDispatch.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

GlobalDelegate::GlobalDelegate()
{
	this->mCoreInitedEventDispatch = MY_NEW PromiseEventDispatch();
}

void GlobalDelegate::init()
{

}

void GlobalDelegate::dispose()
{

}

MY_END_NAMESPACE