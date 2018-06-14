#include "MyProject.h"
#include "UtilMath.h"
#include "MacroDef.h"

MY_BEGIN_NAMESPACE(MyNS)

// error C2511: 'FVector MyNS::UtilMath::Euler(FRotator &) const': overloaded member function not found in 'MyNS::UtilMath'
FVector UtilMath::ZeroVec3 = FVector::ZeroVector;
FVector UtilMath::OneVec3 = FVector::OneVector;
FVector UtilMath::ForwardVec3 = FVector::ForwardVector;
FVector UtilMath::UpVec3 = FVector::UpVector;
FQuat UtilMath::UnitQuat = FQuat::Identity;
float UtilMath::EPSILON = 1e-3f;

FVector UtilMath::Euler(FRotator& rotator)
{
	return rotator.Euler();
}

FRotator UtilMath::MakeFromEuler(const FVector& Euler)
{
	return FRotator::MakeFromEuler(Euler);
}

FRotator UtilMath::Rotator(const FQuat& quat)
{
	return quat.Rotator();
}

FQuat UtilMath::MakeQuatFromEuler(const FVector& Euler)
{
	return FQuat::MakeFromEuler(Euler);
}

FVector UtilMath::Euler(const FQuat& quat)
{
	return quat.Euler();
}

FVector UtilMath::Vector(const FQuat& quat)
{
	return quat.Vector();
}

float UtilMath::abs(float value)
{
	return (value < 0) ? -value : value;
}

bool UtilMath::isEqualVec3(FVector& a, FVector& b)
{
	bool isEqual = true;

	if (UtilMath::abs(a.X - b.X) > UtilMath::EPSILON ||
		UtilMath::abs(a.Y - b.Y) > UtilMath::EPSILON ||
		UtilMath::abs(a.Z - b.Z) > UtilMath::EPSILON)
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

FQuat UtilMath::getRotateByOrient(FVector& forward)
{
	FQuat retQuat = UtilMath::UnitQuat;

	if (MacroDef::XZ_MODE)
	{
		retQuat = FQuat::FindBetween(UtilMath::ForwardVec3, forward);
	}
	else if (MacroDef::XY_MODE)
	{
		retQuat = FQuat::FindBetween(UtilMath::UpVec3, forward);
	}

	return retQuat;
}

MY_END_NAMESPACE