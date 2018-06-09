#pragma once

#include "CoreMinimal.h"
#include "UObject/GCObject.h"	// FGCObject
#include "UObject/UObjectGlobals.h"	// FReferenceCollector \ UObject

class FMyNativeObjectReferencer : FGCObject
{
	TArray<UObject*> mMyNativeObjectArray;

public:
	FMyNativeObjectReferencer();

	void init();
	void dispose();

	void addObjectReference(UObject* Object);
	void removeObjectReference(UObject* Object);

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
};