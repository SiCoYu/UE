#include "MyProject.h"
#include "MyNativeObjectReferencer.h"

FMyNativeObjectReferencer::FMyNativeObjectReferencer()
{

}

void FMyNativeObjectReferencer::init()
{
	
}

void FMyNativeObjectReferencer::dispose()
{
	
}

void FMyNativeObjectReferencer::addObjectReference(UObject* Object)
{
	this->mMyNativeObjectArray.Add(Object);
}

void FMyNativeObjectReferencer::removeObjectReference(UObject* Object)
{
	this->mMyNativeObjectArray.Remove(Object);
}

void FMyNativeObjectReferencer::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AllowEliminatingReferences(false);

	for (auto Object : this->mMyNativeObjectArray)
	{
		Collector.AddReferencedObject(Object);
	}

	Collector.AllowEliminatingReferences(true);
}