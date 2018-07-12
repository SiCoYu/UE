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

	// ��ȡ��λǰ������
	static FVector getNormalForwardVector(FTransform& transform);
	/**
	* @param curOrient ��ǰ����
	* @param lookAt �۲�㷽��
	* @ret ������ת���۲����������Ԫ����������������������ļнǣ����ǵ�֮��ļн�
	*/
	static FQuat getRotateByLookatPoint(FQuat curOrient, FVector lookAt);
	/**
	* @param startPoint ��ʼ��
	* @param destPoint Ŀ���
	* @ret ����������֮�����ת����Ԫ���������������֮��ļн�
	*/
	static FQuat getRotateByStartAndEndPoint(FVector startPoint, FVector destPoint);
	/**
	* @param startOrient ��ʼ����
	* @param destOrient Ŀ�귽��
	* @ret ������������֮�����ת����Ԫ�����������������֮��ļн�
	*/
	static FQuat getRotateByStartAndEndOrient(FVector startOrient, FVector destOrient);
	static FQuat getRotateByOrient(FVector& forward);
	static FQuat convQuatFromEuler(FVector& euler);

	// [a, b]
	static int range(int a, int b);
	static float unitRange();

	// ȡ��
	static float mod(float a, float b);
	// ȡ��
	static int integer(float a);

	// ȡС��
	static float fract(float a);
	// ��ȷ��С�����λ
	static float integerWithFract(float a, int fractNum);
};

MY_END_NAMESPACE

#endif