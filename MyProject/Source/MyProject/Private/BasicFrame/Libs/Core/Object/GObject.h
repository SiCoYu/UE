#pragma once

#include <string>
#include "MClassInfo.h"
#include "MMutex.h"
#include "MClassMacros.h"

class GObject
{
	__DeclareClass(GObject);

protected:
	std::string mTypeId;     // 名字

public:
	GObject();

public:
	std::string getTypeId();

	int GetRefCount() const;
	void AddRef();
	void Release();
	bool IsInstanceOf(const MClassInfo& rtti) const;
	bool IsInstanceOf(const std::string& className) const;
	bool IsA(const MClassInfo& rtti) const;
	bool IsA(const std::string& rttiName) const;
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
	return this->GetRtti() == &other;
}

inline bool GObject::IsInstanceOf(const std::string& other) const
{
	return this->GetRtti()->GetName() == other;
}

inline bool GObject::IsA(const MClassInfo& other) const
{
	return this->GetRtti()->IsDerivedFrom(other);
}

inline bool GObject::IsA(const std::string& other) const
{
	return this->GetRtti()->IsDerivedFrom(other);
}

inline const std::string& RefCounted::GetClassName() const
{
	return this->GetRtti()->GetName();
}