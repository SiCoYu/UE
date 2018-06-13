#include "MyProject.h"
#include "UtilMath.h"

MY_BEGIN_NAMESPACE(MyNS)

FVector UtilMath::ZeroVec3 = FVector::ZeroVector;
FVector UtilMath::OneVec3 = FVector::OneVector;
FQuat UtilMath::UnitQuat = FQuat::Identity;
float UtilMath::EPSILON = 1e-3f;

FVector UtilMath::Euler(FRotator& rotator) const
{
	return rotator.Euler();
}

FRotator UtilMath::MakeFromEuler(const FVector& Euler)
{
	return FRotator::MakeFromEuler(Euler);
}

FRotator UtilMath::Rotator(const FQuat& quat) const
{
	return quat.Rotator();
}

FQuat UtilMath::MakeQuatFromEuler(const FVector& Euler)
{
	return FQuat::MakeFromEuler(Euler);
}

FVector UtilMath::Euler(const FQuat& quat) const
{
	return quat.Euler();
}

float UtilMath::abs(float value)
{
	return (value < 0) ? -value : value;
}

bool UtilMath::isEqualVec3(FVector& a, FVector& b)
{
	bool isEqual = true;

	if (UtilMath::abs(a.x - b.x) > UtilMath::EPSILON ||
		UtilMath::abs(a.y - b.y) > UtilMath::EPSILON ||
		UtilMath::abs(a.z - b.z) > UtilMath::EPSILON)
	{
		isEqual = false;
	}

	return isEqual;
}

bool UtilMath::isEqualQuat(FQuat& a, FQuat& b)
{
	if (UtilMath::abs(a.X - b.X) > UtilMath::EPSILON ||
		UtilMath::abs(a.Y - b.Y) > UtilMath::EPSILON ||
		UtilMath::abs(a.Z - b.Z) > UtilMath::EPSILON ||
		UtilMath::abs(a.W - b.W) > UtilMath::EPSILON)
	{
		return false;
	}

	return true;
}

MY_END_NAMESPACE