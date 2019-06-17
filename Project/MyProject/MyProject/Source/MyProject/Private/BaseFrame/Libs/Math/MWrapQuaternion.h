#ifndef __MWrapQuaternion_H
#define __MWrapQuaternion_H

#include "Math/Vector.h"			// FVector
#include "Math/Quat.h"				// FQuat
#include "Math/Rotator.h"			// FRotator
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MWrapQuaternion
{
protected:
	FQuat mRotate;
	FVector mRotateEulerAngle;
	bool mIsEulerAngleInvalid;

public:
	MWrapQuaternion();
	MWrapQuaternion(float x, float y, float z, float w);

	void clear();
	void setRotateXYZW(float x, float y, float z, float w);
	float getX();
	float getY();
	float getZ();
	float getW();
	FVector& getRotateEulerAngle();
	void setRotateEulerAngle(FVector& rotation);
	FQuat& getRotate();
	void setRotation(FQuat& rotation);
};

MY_END_NAMESPACE

#endif