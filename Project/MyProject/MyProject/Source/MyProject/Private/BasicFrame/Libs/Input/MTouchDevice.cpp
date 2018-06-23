#include "MyProject.h"
#include "MTouchDevice.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MTouchPhase.h"
#include "Ctx.h"
#include "InputMgr.h"

MY_BEGIN_NAMESPACE(MyNS)

MDictionary<int, MTouchDevice*> MTouchDevice::mTouches;

MTouchDevice* MTouchDevice::GetTouch(int id)
{
	MTouchDevice* touch = nullptr;

	if (!MTouchDevice::mTouches.tryGetValue(id, touch))
	{
		touch = MY_NEW MTouchDevice(id);
		MTouchDevice::mTouches.add(id, touch);
	}

	return touch;
}

MTouchDevice::MTouchDevice(int touchIndex)
{
	this->mTouchPhase = MTouchPhase::Null;
	this->mTouchIndex = touchIndex;
}

bool MTouchDevice::_isInBegan()
{
	bool ret = false;

	if (MTouchPhase::Null == this->mTouchPhase)
	{
		ret = (this->mNativeTouchPos->Z == 0.0f);
	}

	return ret;
}

bool MTouchDevice::_isInMoved()
{
	bool ret = false;

	if (MTouchPhase::Null != this->mTouchPhase)
	{
		if (this->mPos != *this->mNativeTouchPos)
		{
			ret = true;
		}
	}

	return ret;
}

bool MTouchDevice::_isInStationary()
{
	bool ret = false;

	if (MTouchPhase::Null != this->mTouchPhase)
	{
		if (this->mPos == *this->mNativeTouchPos)
		{
			ret = true;
		}
	}

	return ret;
}

bool MTouchDevice::_isInEnded()
{
	bool ret = false;

	if (MTouchPhase::Null != this->mTouchPhase)
	{
		ret = (this->mNativeTouchPos->Z == 1.0f);
	}

	return ret;
}

bool MTouchDevice::_isInCanceled()
{
	bool ret = false;

	if (MTouchPhase::Null != this->mTouchPhase)
	{
		ret = (this->mNativeTouchPos->Z == 1.0f);
	}

	return ret;
}

void MTouchDevice::setNativeTouch(const FVector* touchPos, const FKey* nativeTouch, int touchIndex)
{
	this->mNativeTouchPos = touchPos;
	this->mNativeTouch = nativeTouch;
	this->mTouchIndex = touchIndex;
}

void MTouchDevice::onTick(float delta, TickMode tickMode)
{
	if (this->_isInBegan())
	{
		this->mTouchPhase = MTouchPhase::Began;

		this->mTouchBegan = true;
		this->mTouchEnd = false;

		// 按下的时候，设置位置相同
		this->mPos = *this->mNativeTouchPos;
		this->mLastPos = this->mPos;

		this->handleTouchBegan();
	}
	else if (this->_isInMoved())
	{
		this->mTouchPhase = MTouchPhase::Moved;

		this->mTouchBegan = false;
		this->mTouchEnd = false;

		// Up 的时候，先设置之前的位置，然后设置当前位置
		this->mLastPos = this->mPos;
		this->mPos = *this->mNativeTouchPos;

		this->handleTouchMoved();
	}
	else if (this->_isInStationary())
	{
		this->mTouchPhase = MTouchPhase::Stationary;

		this->mTouchBegan = false;
		this->mTouchEnd = false;

		// Press 的时候，先设置之前的位置，然后设置当前位置
		this->mLastPos = this->mPos;
		this->mPos = *this->mNativeTouchPos;

		this->handleTouchStationary();
	}
	else if (this->_isInEnded())
	{
		this->mTouchPhase = MTouchPhase::Ended;

		this->mTouchBegan = false;
		this->mTouchEnd = true;

		this->mLastPos = this->mPos;
		this->mPos = *this->mNativeTouchPos;

		this->handleTouchEnded();
	}
	else if (this->_isInCanceled())
	{
		this->mTouchPhase = MTouchPhase::Canceled;

		this->mTouchBegan = false;
		this->mTouchEnd = true;

		this->mLastPos = this->mPos;
		this->mPos = *this->mNativeTouchPos;

		this->handleTouchCanceled();
	}
}

void MTouchDevice::handleTouchBegan()
{
	GInputMgr->handleTouchBegan(this);
}

void MTouchDevice::handleTouchMoved()
{
	if (this->isPosChanged())
	{
		GInputMgr->handleTouchMoved(this);
	}
}

void MTouchDevice::handleTouchStationary()
{
	GInputMgr->handleTouchStationary(this);
}

void MTouchDevice::handleTouchEnded()
{
	GInputMgr->handleTouchEnded(this);
}

void MTouchDevice::handleTouchCanceled()
{
	GInputMgr->handleTouchCanceled(this);
}

MY_END_NAMESPACE