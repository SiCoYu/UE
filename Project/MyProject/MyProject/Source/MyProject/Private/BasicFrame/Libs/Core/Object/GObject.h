#pragma once

#include <string>
#include "MyAllocatedObject.h"
#include "MMutex.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "BaseClassDef.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GObject : public MyAllocatedObject
{
	M_DECLARE_CLASS(GObject, MyAllocatedObject)

public:
	GObject();

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
	virtual ~GObject();

private:
	volatile int mRefCount;

// warning C4668: 'My_DEBUG' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
#ifdef My_DEBUG
protected:
	static bool mIsInCreate;
	static MMutex mCriticalSection;
#endif
};

MY_END_NAMESPACE