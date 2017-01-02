#include "MyProject.h"
#include "MClassInfo.h"
#include "GObject.h"
#include "TypeDef.h"
#include "MClassFactory.h"

void MClassInfo::Construct(const char* className, Creator creatorFunc, const MClassInfo* parentClass, SizeT instSize)
{
	my_assert(0 != className);
	my_assert(parentClass != this);

	this->parent = parentClass;
	this->creator = creatorFunc;
	this->instanceSize = instSize;

	this->name = className;
	if (nullptr != className)
	{
		if (!MClassFactory::Instance()->ClassExists(this->name))
		{
			MClassFactory::Instance()->Register(this, this->name);
		}
#if MY_DEBUG
		else
		{
			const MClassInfo* checkRtti = MClassFactory::Instance()->GetClassRtti(this->name);
			my_assert(0 != checkRtti);
			if (checkRtti != this)
			{
				
			}
		}
#endif
	}
}

MClassInfo::MClassInfo(const char* className, Creator creatorFunc, const MClassInfo* parentClass, SizeT instSize)
{
	this->Construct(className, creatorFunc, parentClass, instSize);
}

GObject* MClassInfo::Create() const
{
	if (0 == this->creator)
	{
		return 0;
	}
	else
	{
		return this->creator();
	}
}

bool MClassInfo::IsDerivedFrom(const MClassInfo& other) const
{
	const MClassInfo* cur;
	for (cur = this; cur != 0; cur = cur->GetParent())
	{
		if (cur == &other)
		{
			return true;
		}
	}
	return false;
}

bool MClassInfo::IsDerivedFrom(const std::string& otherClassName) const
{
	const MClassInfo* cur;
	for (cur = this; cur != 0; cur = cur->GetParent())
	{
		if (cur->name == otherClassName)
		{
			return true;
		}
	}
	return false;
}

void* MClassInfo::AllocInstanceMemory()
{
#if MY_OBJECTS_USE_MEMORYPOOL
	//void* ptr = Memory::ObjectPoolAllocator->Alloc(this->instanceSize);
#else
	//void* ptr = Memory::Alloc(Memory::ObjectHeap, this->instanceSize);
#endif
	void* ptr = nullptr;
	return ptr;
}

void MClassInfo::FreeInstanceMemory(void* ptr)
{
#if MY_OBJECTS_USE_MEMORYPOOL
	//Memory::ObjectPoolAllocator->Free(ptr, this->instanceSize);
#else
	//Memory::Free(Memory::ObjectHeap, ptr);
#endif
}