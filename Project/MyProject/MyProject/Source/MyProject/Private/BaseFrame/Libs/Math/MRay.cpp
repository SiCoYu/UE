#include "MyProject.h"
#include "MRay.h"

MY_BEGIN_NAMESPACE(MyNS)

FVector& MRay::getRayOrigin()
{
	return mRayOrigin;
}

void MRay::setRayOrigin(FVector value)
{
	mRayOrigin = value;
}

FVector& MRay::getRayDirection()
{
	return mRayDirection;
}

void MRay::setRayDirection(FVector value)
{
	mRayDirection = value;
}

MY_END_NAMESPACE