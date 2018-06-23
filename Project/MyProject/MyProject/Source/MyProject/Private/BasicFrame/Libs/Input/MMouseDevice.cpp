#include "MyProject.h"
#include "MMouseDevice.h"

MY_BEGIN_NAMESPACE(MyNS)

MMouseDevice* MMouseDevice::MouseLeftButton = MY_NEW MMouseDevice(0);
MMouseDevice* MMouseDevice::MouseRightButton = MY_NEW MMouseDevice(1);
MMouseDevice* MMouseDevice::MouseMiddleButton = MY_NEW MMouseDevice(2);

MMouseDevice* MMouseDevice::mMouse[MMouseDeviceType::eMouseTotalButton];

MMouseDevice* MMouseDevice::GetMouse(int button)
{
	if (nullptr == MMouseDevice::mMouse[0])
	{
		MMouseDevice::mMouse[0] = MMouseDevice::MouseLeftButton;
		MMouseDevice::mMouse[1] = MMouseDevice::MouseRightButton;
		MMouseDevice::mMouse[2] = MMouseDevice::MouseMiddleButton;
	}

	return MMouseDevice::mMouse[button];
}

MMouseDevice::MMouseDevice(int button)
{
	this->mTouchIndex = button;
}

void MMouseDevice::onTick(float delta, TickMode tickMode)
{
	if (UnityEngine.Input.GetMouseButtonDown(this->mTouchIndex))
	{
		this->mPressTime = RealTime.time;
		this->mTouchBegan = true;
		this->mTouchEnd = false;

		// 按下的时候，设置位置相同
		this->mPos = UnityEngine.Input.mousePosition;
		this->mLastPos = this->mPos;

		this->handleMouseDown();
	}
	else if (UnityEngine.Input.GetMouseButtonUp(this->mTouchIndex))
	{
		this->mTouchBegan = false;
		this->mTouchEnd = true;

		// Up 的时候，先设置之前的位置，然后设置当前位置
		this->mLastPos = this->mPos;
		this->mPos = UnityEngine.Input.mousePosition;

		this->handleMouseUp();
	}
	else if (UnityEngine.Input.GetMouseButton(this->mTouchIndex))
	{
		this->mTouchBegan = false;
		this->mTouchEnd = false;

		// Press 的时候，先设置之前的位置，然后设置当前位置
		this->mLastPos = this->mPos;
		this->mPos = UnityEngine.Input.mousePosition;

		if (this->isPosChanged())
		{
			this->handleMousePressMove();
		}
		else
		{
			this->handleMousePress();
		}
	}
	else if (this->isPosChanged())     // 位置不相等的时候，就是移动
	{
		this->mTouchBegan = false;
		this->mTouchEnd = false;

		// 鼠标移动
		this->mLastPos = this->mPos;
		this->mPos = UnityEngine.Input.mousePosition;

		this->handleMousePressOrMove();
	}
}

void MMouseDevice::handleMouseDown()
{
	if (!Ctx.msInstance.mInputMgr.mSimulateMouseWithTouches)
	{
		Ctx.msInstance.mInputMgr.handleMouseDown(this);
	}
	else
	{
		Ctx.msInstance.mInputMgr.handleTouchBegan(this);
	}
}

void MMouseDevice::handleMouseUp()
{
	if (!Ctx.msInstance.mInputMgr.mSimulateMouseWithTouches)
	{
		Ctx.msInstance.mInputMgr.handleMouseUp(this);
	}
	else
	{
		Ctx.msInstance.mInputMgr.handleTouchEnded(this);
	}
}

void MMouseDevice::handleMousePress()
{
	if (!Ctx.msInstance.mInputMgr.mSimulateMouseWithTouches)
	{
		Ctx.msInstance.mInputMgr.handleMousePress(this);
	}
	else
	{
		Ctx.msInstance.mInputMgr.handleTouchStationary(this);
	}
}

void MMouseDevice::handleMousePressOrMove()
{
	if (this->isPosChanged())
	{
		Ctx.msInstance.mInputMgr.handleMousePressOrMove(this);
	}
}

void MMouseDevice::handleMousePressMove()
{
	if (this->isPosChanged())
	{
		if (!Ctx.msInstance.mInputMgr.mSimulateMouseWithTouches)
		{
			Ctx.msInstance.mInputMgr.handleMousePressMove(this);
		}
		else
		{
			Ctx.msInstance.mInputMgr.handleTouchMoved(this);
		}
	}
}

MY_END_NAMESPACE