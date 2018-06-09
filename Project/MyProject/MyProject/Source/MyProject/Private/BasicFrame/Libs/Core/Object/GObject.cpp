#include "MyProject.h"
#include "GObject.h"
#include "TypeDef.h"
#include "MyMemoryAlloc.h"
#include "MClassFactory.h"
#include "MDebug.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(GObject, MyAllocatedObject)

// warning C4668 : 'MY_DEBUG' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
//#if MY_DEBUG
#ifdef MY_DEBUG
MMutex GObject::mCriticalSection;
bool GObject::mIsInCreate = false;
#endif

GObject::GObject() :
	mRefCount(0)
{
	this->mIsClientDispose = false;
}

GObject::~GObject()
{
	MY_ASSERT(0 == this->mRefCount);
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
	return this->GetMyClassInfo() == &other;
}

bool GObject::IsInstanceOf(const std::string& other) const
{
	return this->GetMyClassInfo()->GetName() == other;
}

bool GObject::IsA(const MClassInfo& other) const
{
	return this->GetMyClassInfo()->IsDerivedFrom(other);
}

bool GObject::IsA(const std::string& other) const
{
	return this->GetMyClassInfo()->IsDerivedFrom(other);
}

const std::string& GObject::GetMyClassName() const
{
	return this->GetMyClassInfo()->GetName();
}

void GObject::DumpRefCountingLeaks()
{

}

void GObject::setClientDispose(bool isDispose)
{
	this->mIsClientDispose = isDispose;
}

bool GObject::isClientDispose()
{
	return this->mIsClientDispose;
}

MY_END_NAMESPACE