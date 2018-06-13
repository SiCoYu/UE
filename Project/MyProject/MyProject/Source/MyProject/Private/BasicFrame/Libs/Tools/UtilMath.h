#ifndef __UtilMath_H
#define __UtilMath_H

#include "Math/Vector.h"	// FVector
#include "Math/Quat.h"		// FQuat
#include "Math/Rotator.h"	// FRotator
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UtilMath
{
public:
	static const FVector ZeroVec3 = FVector::ZeroVector;
	static const FVector OneVec3 = FVector::OneVector;
	static const FVector ForwardVec3 = FVector::ForwardVector;
	static const FVector UpVec3 = FVector::UpVector;

	static const FQuat UnitQuat = FQuat::Identity;
	static const float EPSILON = 1e-3f;

public:
	static FVector Euler(FRotator& rotator);
	static FRotator MakeFromEuler(const FVector& Euler);
	static FRotator Rotator(const FQuat& quat);
	static FQuat MakeQuatFromEuler(const FVector& Euler);
	static FVector Euler(const FQuat& quat);
	static FVector Vector(const FQuat& quat);

	static float abs(float value);
	static bool isEqualVec3(FVector& a, FVector& b);
	static bool isEqualQuat(FQuat& a, FQuat& b);

	static FQuat getRotateByOrient(FVector& forward)
};

MY_END_NAMESPACE

#endif