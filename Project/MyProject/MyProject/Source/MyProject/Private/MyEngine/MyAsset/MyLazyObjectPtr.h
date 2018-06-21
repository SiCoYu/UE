#pragma once

#include "UObject/UObject.h"	// UObject
#include "UObject/LazyObjectPtr.h"	// FLazyObjectPtr
#include "UObject/PersistentObjectPtr.h"		// TPersistentObjectPtr

#include "GObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MyLazyObjectPtr : public GObject
{
	M_DECLARE_CLASS(MySoftObjectPath, GObject)

protected:
	FLazyObjectPtr mNativeLazyObjectPtr;

public:
	MyLazyObjectPtr();
	~MyLazyObjectPtr();

	UObject* getObject() const;
};

MY_END_NAMESPACE