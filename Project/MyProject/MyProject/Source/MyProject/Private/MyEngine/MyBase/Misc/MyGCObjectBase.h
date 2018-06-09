#pragma once

#include "UObject/GCObject.h"	// FGCObject
#include "UObject/UObjectGlobals.h"	// FReferenceCollector \ UObject

/**
 * @brief UE4 内存管理, http://blog.csdn.net/or_7r_ccl/article/details/53790839 非UObject对象的引用
 */

class FMyGCObjectBase : public FGCObject
{
public:
	UObject* mSafeObject;
	FMyGCObjectBase();
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
};