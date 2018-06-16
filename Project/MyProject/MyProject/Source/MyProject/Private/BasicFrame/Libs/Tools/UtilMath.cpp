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

// 获取单位前向向量
FVector UtilMath::getNormalForwardVector(FTransform& transform)
{
	FVector dir = transform.TransformPosition(UtilMath::ForwardVec3);
	dir.Normalize();
	return dir;
}

/**
* @param curOrient 当前方向
* @param lookAt 观察点方向
* @ret 返回旋转到观察点向量的四元数，这个是两个方向向量的夹角，不是点之间的夹角
*/
FQuat UtilMath::getRotateByLookatPoint(FQuat curOrient, FVector lookAt)
{
	FVector curVec = curOrient * UtilMath::ForwardVec3;
	FQuat retQuat = FQuat::FindBetweenVectors(curVec, lookAt);
	return retQuat;
}

/**
* @param startPoint 开始点
* @param destPoint 目标点
* @ret 返回两个点之间的旋转的四元数，这个是两个点之间的夹角
*/
FQuat UtilMath::getRotateByStartAndEndPoint(FVector startPoint, FVector destPoint)
{
	FQuat retQuat = UtilMath::UnitQuat;

	if (MacroDef::XZ_MODE)
	{
		retQuat = FQuat::FindBetweenVectors(UtilMath::ForwardVec3, destPoint - startPoint);
	}
	else if (MacroDef::XY_MODE)
	{
		retQuat = FQuat::FindBetweenVectors(UtilMath::UpVec3, destPoint - startPoint);
	}

	return retQuat;
}

/**
* @param startOrient 开始方向
* @param destOrient 目标方向
* @ret 返回两个向量之间的旋转的四元数，这个是两个向量之间的夹角
*/
FQuat UtilMath::getRotateByStartAndEndOrient(FVector startOrient, FVector destOrient)
{
	FQuat retQuat = UtilMath::UnitQuat;

	retQuat = FQuat::FindBetweenVectors(startOrient, destOrient);

	return retQuat;
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

FQuat UtilMath::convQuatFromEuler(FVector& euler)
{
	return UtilMath::MakeQuatFromEuler(euler);
}

MY_END_NAMESPACE