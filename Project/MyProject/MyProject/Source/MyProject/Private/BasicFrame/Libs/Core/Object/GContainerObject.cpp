#include "MyProject.h"
#include "GObject.h"
#include "TypeDef.h"
#include "MyMemory.h"
#include "MClassFactory.h"

M_IMPLEMENT_ROOT_CLASS(GContainerObject)
M_REGISTER_CLASS(GContainerObject)

// warning C4668 : 'MY_DEBUG' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
//#if MY_DEBUG
#ifdef MY_DEBUG
MMutex GObject::mCriticalSection;
bool GObject::mIsInCreate = false;
#endif

GContainerObject::~GContainerObject()
{
	my_assert(0 == this->mRefCount);
}

void GContainerObject::DumpRefCountingLeaks()
{

}