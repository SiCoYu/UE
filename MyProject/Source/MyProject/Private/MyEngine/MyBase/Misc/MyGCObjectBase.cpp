#include "MyProject.h"
#include "MyGCObjectBase.h"

FMyGCObjectBase::FMyGCObjectBase()
{

}

void FMyGCObjectBase::AddReferencedObjects(FReferenceCollector& Collector)
{
	if (nullptr != mSafeObject)
	{
		Collector.AddReferencedObject(mSafeObject);
	}
}