#include "MyProject.h"
#include "TestMemory.h"
#include "TestMemoryObject.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

void TestMemory::run()
{
	this->mTestMemoryObject = MY_NEW TestMemoryObject();
}

MY_END_NAMESPACE