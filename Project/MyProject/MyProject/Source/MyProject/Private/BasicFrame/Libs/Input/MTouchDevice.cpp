#include "MyProject.h"
#include "MTouchDevice.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

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
	this->mTouchIndex = touchIndex;
}

void MTouchDevice::setNativeTouch(FVector* touchPos, FKey* nativeTouch, int touchIndex)
{
	this->mNativeTouchPos = touchPos;
	this->mNativeTouch = nativeTouch;
	this->mTouchIndex = touchIndex;
}

void MTouchDevice::onTick(float delta, TickMode tickMode)
{
	if (this->mNativeTouch.phase == TouchPhase.Began)
	{
		this->mPressTime = RealTime.time;
		this->mTouchBegan = true;
		this->mTouchEnd = false;

		// 按下的时候，设置位置相同
		this->mPos = this->mNativeTouch.position;
		this->mLastPos = this->mPos;

		this->handleTouchBegan();
	}
	else if (this->mNativeTouch.phase == TouchPhase.Moved)
	{
		this->mTouchBegan = false;
		this->mTouchEnd = false;

		// Up 的时候，先设置之前的位置，然后设置当前位置
		this->mLastPos = this->mPos;
		this->mPos = this->mNativeTouch.position;

		this->handleTouchMoved();
	}
	else if (this->mNativeTouch.phase == TouchPhase.Stationary)
	{
		this->mTouchBegan = false;
		this->mTouchEnd = false;

		// Press 的时候，先设置之前的位置，然后设置当前位置
		this->mLastPos = this->mPos;
		this->mPos = this->mNativeTouch.position;

		this->handleTouchStationary();
	}
	else if (this->mNativeTouch.phase == TouchPhase.Ended)
	{
		this->mTouchBegan = false;
		this->mTouchEnd = true;

		this->mLastPos = this->mPos;
		this->mPos = this->mNativeTouch.position;

		this->handleTouchEnded();
	}
	else if (this->mNativeTouch.phase == TouchPhase.Canceled)
	{
		this->mTouchBegan = false;
		this->mTouchEnd = true;

		this->mLastPos = this->mPos;
		this->mPos = UnityEngine.Input.mousePosition;

		this->handleTouchCanceled();
	}
}

void MTouchDevice::handleTouchBegan()
{
	Ctx.msInstance.mInputMgr.handleTouchBegan(this);
}

void MTouchDevice::handleTouchMoved()
{
	if (this->isPosChanged())
	{
		Ctx.msInstance.mInputMgr.handleTouchMoved(this);
	}
}

void handleTouchStationary()
{
	Ctx.msInstance.mInputMgr.handleTouchStationary(this);
}

void MTouchDevice::handleTouchEnded()
{
	Ctx.msInstance.mInputMgr.handleTouchEnded(this);
}

void MTouchDevice::handleTouchCanceled()
{
	Ctx.msInstance.mInputMgr.handleTouchCanceled(this);
}

MY_END_NAMESPACE