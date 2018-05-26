#include "MyProject.h"
#include "GObject.h"
#include "TypeDef.h"
#include "MyMemoryAlloc.h"
#include "MClassFactory.h"

M_IMPLEMENT_CLASS(GObject, GObjectBase)
M_REGISTER_CLASS(GObject)

// warning C4668 : 'MY_DEBUG' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
//#if MY_DEBUG
#ifdef MY_DEBUG
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