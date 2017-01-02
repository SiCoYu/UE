#pragma once

#include <string>
#include "Rtti/MClassInfo.h"
#include "MMutex.h"
#include "Rtti/MClassMacros.h"

class GObject
{
	M_DECLARE_CLASS(GObject);

public:
	GObject();

public:
	std::string getTypeId();

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
	virtual ~GObject();

private:
	volatile int refCount;

#if My_DEBUG
protected:
	static bool isInCreate;
	static MMutex criticalSection;
#endif
};

inline GObject::GObject() :
	refCount(0)
{
	
}

inline void GObject::AddRef()
{
	//Threading::Interlocked::Increment(this->refCount);
}

inline void GObject::Release()
{
	//if (0 == Threading::Interlocked::Decrement(this->refCount))
	//{
	//	n_delete(this);
	//}
}

inline int GObject::GetRefCount() const
{
	return this->refCount;
}

inline bool GObject::IsInstanceOf(const MClassInfo& other) const
{
	return this->GetClassInfo() == &other;
}

inline bool GObject::IsInstanceOf(const std::string& other) const
{
	return this->GetClassInfo()->GetName() == other;
}

inline bool GObject::IsA(const MClassInfo& other) const
{
	return this->GetClassInfo()->IsDerivedFrom(other);
}

inline bool GObject::IsA(const std::string& other) const
{
	return this->GetClassInfo()->IsDerivedFrom(other);
}

inline const std::string& GObject::GetClassName() const
{
	return this->GetClassInfo()->GetName();
}