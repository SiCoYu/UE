#include "MyProject.h"
#include "GObject.h"
#include "TypeDef.h"

__ImplementRootClass(GObject);

#if MY_DEBUG
MMutex GObject::criticalSection;
bool GObject::isInCreate = false;
#endif

GObject::GObject()
{
    mTypeId = "GObject";
}

std::string GObject::getTypeId()
{
    return mTypeId;
}

GObject::~GObject()
{
	my_assert(0 == this->refCount);
}

void GObject::DumpRefCountingLeaks()
{

}