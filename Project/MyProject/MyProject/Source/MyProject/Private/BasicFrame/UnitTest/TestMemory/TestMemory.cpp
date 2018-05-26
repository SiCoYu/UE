#include "MyProject.h"
#include "TestMemory.h"
#include "TestMemoryObject.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

void TestMemory::run()
{
	this->mTestMemoryObject = MY_NEW TestMemoryObject();
}