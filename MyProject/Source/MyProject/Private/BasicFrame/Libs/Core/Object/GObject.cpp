#include "MyProject.h"
#include "GObject.h"
#include "TypeDef.h"
#include "MyMemory.h"
#include "MClassFactory.h"

M_IMPLEMENT_ROOT_CLASS(GObject)
M_REGISTER_CLASS(GObject)

#if MY_DEBUG
MMutex GObject::mCriticalSection;
bool GObject::mIsInCreate = false;
#endif

GObject::~GObject()
{
	my_assert(0 == this->mRefCount);
}

void GObject::DumpRefCountingLeaks()
{

}