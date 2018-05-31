#include "MyProject.h"
#include "MRay.h"

MY_BEGIN_NAMESPACE(MyNS)

FVector& MRay::getRayOrigin()
{
	return m_rayOrigin;
}

void MRay::setRayOrigin(FVector value)
{
	m_rayOrigin = value;
}

FVector& MRay::getRayDirection()
{
	return m_rayDirection;
}

void MRay::setRayDirection(FVector value)
{
	m_rayDirection = value;
}