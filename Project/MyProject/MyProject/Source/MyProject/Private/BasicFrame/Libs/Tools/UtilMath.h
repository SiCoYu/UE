#ifndef __UtilMath_H
#define __UtilMath_H

#include "Math/Vector.h"	// FVector
#include "Math/Quat.h"	// FQuat
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UtilMath
{
public:
	static FVector ZeroVec3;
	static FQuat UnitQuat;
};

MY_END_NAMESPACE

#endif