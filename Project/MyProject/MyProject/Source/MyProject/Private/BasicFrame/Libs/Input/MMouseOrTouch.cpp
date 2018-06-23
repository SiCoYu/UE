#include "MyProject.h"
#include "MMouseOrTouch.h"

MY_BEGIN_NAMESPACE(MyNS)

MMouseOrTouch::MMouseOrTouch()
{
	this->mSensitivity = 0.1f;
	this->mTouchIndex = 0;
}

int MMouseOrTouch::getTouchIndex()
{
	return this->mTouchIndex;
}

// 获取 X 方向移动的距离
float MMouseOrTouch::getXOffset()
{
	return (this->mPos.X - this->mLastPos.X) * this->mSensitivity;
}

// 获取 X 方向移动的距离
float MMouseOrTouch::getYOffset()
{
	return (this->mPos.Y - this->mLastPos.Y) * this->mSensitivity;
}

bool MMouseOrTouch::isPosChanged()
{
	bool ret = false;

	if (this->mPos.X != this->mLastPos.X ||
		this->mPos.Y != this->mLastPos.Y)
	{
		ret = true;
	}

	return ret;
}

MY_END_NAMESPACE