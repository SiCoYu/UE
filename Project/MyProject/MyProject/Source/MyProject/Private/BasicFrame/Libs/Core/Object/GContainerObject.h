#pragma once

#include <string>
#include "MClassInfo.h"
#include "MMutex.h"
#include "MClassMacros.h"

class GContainerObject
{
	M_DECLARE_CLASS(GContainerObject);

public:
	GContainerObject();

public:
	int GetRefCount() const;
	void AddRef();
	void Release();
	bool IsInstanceOf(const MClassInfo& classInfo) const;
	bool IsInstanceOf(const std::string& className) const;
	bool IsA(const MClassInfo& classInfo) const;
	bool IsA(const std::string& classInfoName) const;
	const std::string& GetClassName() const;
	static void DumpRefCountingLeaks();

protected:
	virtual ~GContainerObject();

private:
	volatile int mRefCount;

// warning C4668: 'My_DEBUG' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
#ifdef My_DEBUG
protected:
	static bool mIsInCreate;
	static MMutex mCriticalSection;
#endif
};

inline GContainerObject::GContainerObject() :
	mRefCount(0)
{
	
}

inline void GContainerObject::AddRef()
{
	//Threading::Interlocked::Increment(this->mRefCount);
}

inline void GContainerObject::Release()
{
	//if (0 == Threading::Interlocked::Decrement(this->mRefCount))
	//{
	//	n_delete(this);
	//}
}

inline int GContainerObject::GetRefCount() const
{
	return this->mRefCount;
}

inline bool GContainerObject::IsInstanceOf(const MClassInfo& other) const
{
	return this->GetClassInfo() == &other;
}

inline bool GContainerObject::IsInstanceOf(const std::string& other) const
{
	return this->GetClassInfo()->GetName() == other;
}

inline bool GContainerObject::IsA(const MClassInfo& other) const
{
	return this->GetClassInfo()->IsDerivedFrom(other);
}

inline bool GContainerObject::IsA(const std::string& other) const
{
	return this->GetClassInfo()->IsDerivedFrom(other);
}

inline const std::string& GContainerObject::GetClassName() const
{
	return this->GetClassInfo()->GetName();
}