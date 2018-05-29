#include "MyProject.h"
#include "GObject.h"
#include "TypeDef.h"
#include "MyMemoryAlloc.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(GObject, MyAllocatedObject)

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

GObject::GObject() :
	mRefCount(0)
{

}

void GObject::AddRef()
{
	//Threading::Interlocked::Increment(this->mRefCount);
}

void GObject::Release()
{
	//if (0 == Threading::Interlocked::Decrement(this->mRefCount))
	//{
	//	n_delete(this);
	//}
}

int GObject::GetRefCount() const
{
	return this->mRefCount;
}

bool GObject::IsInstanceOf(const MClassInfo& other) const
{
	return this->GetClassInfo() == &other;
}

bool GObject::IsInstanceOf(const std::string& other) const
{
	return this->GetClassInfo()->GetName() == other;
}

bool GObject::IsA(const MClassInfo& other) const
{
	return this->GetClassInfo()->IsDerivedFrom(other);
}

bool GObject::IsA(const std::string& other) const
{
	return this->GetClassInfo()->IsDerivedFrom(other);
}

const std::string& GObject::GetClassName() const
{
	return this->GetClassInfo()->GetName();
}

void GObject::DumpRefCountingLeaks()
{

}

MY_END_NAMESPACE