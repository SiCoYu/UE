#pragma once

// UE4 4.22 warning C4996: 'UObjectHeaderDeprecatedWarning': Including UObject.h has been deprecated. Please include Object.h instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
//#include "UObject/UObject.h"	// UObject
#include "UObject/Object.h"	// UObject
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