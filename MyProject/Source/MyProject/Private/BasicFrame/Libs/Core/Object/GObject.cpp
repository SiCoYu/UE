#include "MyProject.h"
#include "GObject.h"
#include "TypeDef.h"
#include "MyMemory.h"
#include "MClassFactory.h"

__ImplementRootClass(GObject);

#if MY_DEBUG
MMutex GObject::criticalSection;
bool GObject::isInCreate = false;
#endif

GObject::~GObject()
{
	my_assert(0 == this->refCount);
}

void GObject::DumpRefCountingLeaks()
{

}