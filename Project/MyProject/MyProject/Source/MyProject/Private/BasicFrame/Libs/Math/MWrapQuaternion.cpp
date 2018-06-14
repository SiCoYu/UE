#include "MyProject.h"
#include "MRay.h"

MY_BEGIN_NAMESPACE(MyNS)

MWrapQuaternion::MWrapQuaternion()
{
	this->mIsEulerAngleInvalid = true;
	this->setRotation(FQuat(0, 0, 0, 0));
}

MWrapQuaternion::MWrapQuaternion(float x, float y, float z, float w)
{
	this->mIsEulerAngleInvalid = true;
	this->setRotation(FQuat(x, y, z, w));
}

void MWrapQuaternion::clear()
{
	this->mIsEulerAngleInvalid = true;
	this->setRotation(FQuat(0, 0, 0, 1));
}

void MWrapQuaternion::setRotateXYZW(float x, float y, float z, float w)
{
	this->mIsEulerAngleInvalid = true;
	this->mRotate = FQuat(x, y, z, w);
}

float MWrapQuaternion::getX()
{
	return this->mRotate.X;
}

float MWrapQuaternion::getY()
{
	return this->mRotate.Y;
}

float MWrapQuaternion::getZ()
{
	return this->mRotate.Z;
}

float MWrapQuaternion::getW()
{
	return this->mRotate.W;
}

FVector MWrapQuaternion::getRotateEulerAngle()
{
	if (this->mIsEulerAngleInvalid)
	{
		this->mRotateEulerAngle = this->mRotate.Euler();
		this->mIsEulerAngleInvalid = false;
	}

	return this->mRotateEulerAngle;
}

void MWrapQuaternion::setRotateEulerAngle(FVector rotation)
{
	this->mRotateEulerAngle = rotation;
	this->mRotate = FQuat::MakeFromEuler(rotation);
}

FQuat MWrapQuaternion::getRotate()
{
	return this->mRotate;
}

void MWrapQuaternion::setRotation(FQuat rotation)
{
	this->mIsEulerAngleInvalid = true;
	this->mRotate = rotation;
}

MY_END_NAMESPACE