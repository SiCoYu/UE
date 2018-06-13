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
	static const FVector ZeroVec3;
	static const FVector OneVec3;
	static const FQuat UnitQuat;

	static const float EPSILON;

public:
	static FVector Euler(FRotator& rotator) const;
	static FRotator MakeFromEuler(const FVector& Euler);
	static FRotator Rotator(const FQuat& quat) const;
	static FQuat MakeQuatFromEuler(const FVector& Euler);
	static FVector Euler(const FQuat& quat) const;

	static float abs(float value);
	static bool isEqualVec3(FVector& a, FVector& b);
	static bool isEqualQuat(FQuat& a, FQuat& b);
};

MY_END_NAMESPACE

#endif