#ifndef __MRay_H
#define __MRay_H

#include "Core.h"

class MRay
{
protected:
	FVector m_rayOrigin; 
	FVector m_rayDirection;

public:
	FVector& getRayOrigin();
	void setRayOrigin(FVector value);

	FVector& getRayDirection();
	void setRayDirection(FVector value);
};

#endif