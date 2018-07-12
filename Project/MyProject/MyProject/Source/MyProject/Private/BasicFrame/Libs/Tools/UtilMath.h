#ifndef __UtilMath_H
#define __UtilMath_H

#include "Math/Vector.h"	// FVector
#include "Math/Quat.h"		// FQuat
#include "Math/Rotator.h"	// FRotator
#include "Math/TransformVectorized.h"	// FTransform
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UtilMath
{
public:
	static /*const*/ FVector ZeroVec3/* = FVector::ZeroVector*/;
	static /*const*/ FVector OneVec3/* = FVector::OneVector*/;
	static /*const*/ FVector ForwardVec3/* = FVector::ForwardVector*/;
	static /*const*/ FVector UpVec3/* = FVector::UpVector*/;

	static /*const*/ FQuat UnitQuat/* = FQuat::Identity*/;
	static /*const*/ float EPSILON/* = 1e-3f*/;
	static int msIntMaxValue;

	static int OneK = 1024;
	static int OneM = 1024 * 1024;

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

	// 获取单位前向向量
	static FVector getNormalForwardVector(FTransform& transform);
	/**
	* @param curOrient 当前方向
	* @param lookAt 观察点方向
	* @ret 返回旋转到观察点向量的四元数，这个是两个方向向量的夹角，不是点之间的夹角
	*/
	static FQuat getRotateByLookatPoint(FQuat curOrient, FVector lookAt);
	/**
	* @param startPoint 开始点
	* @param destPoint 目标点
	* @ret 返回两个点之间的旋转的四元数，这个是两个点之间的夹角
	*/
	static FQuat getRotateByStartAndEndPoint(FVector startPoint, FVector destPoint);
	/**
	* @param startOrient 开始方向
	* @param destOrient 目标方向
	* @ret 返回两个向量之间的旋转的四元数，这个是两个向量之间的夹角
	*/
	static FQuat getRotateByStartAndEndOrient(FVector startOrient, FVector destOrient);
	static FQuat getRotateByOrient(FVector& forward);
	static FQuat convQuatFromEuler(FVector& euler);

	// [a, b]
	static int range(int a, int b);
	static float unitRange();

	// 取余
	static float mod(float a, float b);
	// 取整
	static int integer(float a);

	// 取小数
	static float fract(float a);
	// 精确到小数点后几位
	static float integerWithFract(float a, int fractNum);
};

MY_END_NAMESPACE

#endif