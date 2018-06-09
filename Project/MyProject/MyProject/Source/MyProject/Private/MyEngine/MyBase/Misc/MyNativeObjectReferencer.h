#pragma once

#include "CoreMinimal.h"
#include "UObject/GCObject.h"

class FMyNativeObjectReferencer : FGCObject
{
	TArray<UObject*> mMyNativeObjectArray;

public:
	void init();
	void dispose();

	void addObjectReference(UObject* Object);
	void removeObjectReference(UObject* Object);

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
};