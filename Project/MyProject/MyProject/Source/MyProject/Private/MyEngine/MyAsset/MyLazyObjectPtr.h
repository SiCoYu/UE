#pragma once

#include "UObject/UObject.h"	// UObject
#include "UObject/LazyObjectPtr.h"	// FLazyObjectPtr
#include "UObject/PersistentObjectPtr.h"		// TPersistentObjectPtr

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

template<class T = UObject>
class MyLazyObjectPtr : public GObject
{
protected:
	TLazyObjectPtr<T> mNativeLazyObjectPtr;

public:
	MyLazyObjectPtr();
	~MyLazyObjectPtr();

	UObject* getObject() const;
};

MY_END_NAMESPACE

#include "MyLazyObjectPtr.h"