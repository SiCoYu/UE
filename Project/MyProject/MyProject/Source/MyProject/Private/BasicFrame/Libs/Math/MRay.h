#ifndef __MRay_H
#define __MRay_H

#include "Core.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MRay
{
protected:
	FVector mRayOrigin; 
	FVector mRayDirection;

public:
	FVector& getRayOrigin();
	void setRayOrigin(FVector value);

	FVector& getRayDirection();
	void setRayDirection(FVector value);
};

MY_END_NAMESPACE

#endif