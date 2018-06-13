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
	MWrapQuaternion(float x, float y, float z, float w)
	{
		this->mIsEulerAngleInvalid = true;
		this->setRotation(FQuat(x, y, z, w));
	}

	void clear()
	{
		this->mIsEulerAngleInvalid = true;
		this->setRotation(FQuat(0, 0, 0, 1));
	}

	void setRotateXYZW(float x, float y, float z, float w)
	{
		this->mIsEulerAngleInvalid = true;
		this->mRotate = FQuat(x, y, z, w);
	}

	float getX()
	{
		return this->mRotate.X;
	}

	float getY()
	{
		return this->mRotate.Y;
	}

	float getZ()
	{
		return this->mRotate.Z;
	}

	float getW()
	{
		return this->mRotate.W;
	}

	FVector getRotateEulerAngle()
	{
		if (this->mIsEulerAngleInvalid)
		{
			this->mRotateEulerAngle = this->mRotate.Euler();
			this->mIsEulerAngleInvalid = false;
		}

		return this->mRotateEulerAngle;
	}

	void setRotateEulerAngle(FVector rotation)
	{
		this->mRotateEulerAngle = rotation;
		this->mRotate = FQuat::MakeFromEuler(rotation);
	}

	FQuat getRotate()
	{
		return this->mRotate;
	}

	void setRotation(FQuat rotation)
	{
		this->mIsEulerAngleInvalid = true;
		this->mRotate = rotation;
	}
};

MY_END_NAMESPACE

#endif