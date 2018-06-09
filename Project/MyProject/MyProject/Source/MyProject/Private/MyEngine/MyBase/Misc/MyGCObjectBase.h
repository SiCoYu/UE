#pragma once

#include "UObject/GCObject.h"	// FGCObject
#include "UObject/UObjectGlobals.h"	// FReferenceCollector \ UObject

/**
 * @brief UE4 �ڴ����, http://blog.csdn.net/or_7r_ccl/article/details/53790839 ��UObject���������
 */

class FMyGCObjectBase : public FGCObject
{
public:
	UObject* mSafeObject;
	FMyGCObjectBase();
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
};